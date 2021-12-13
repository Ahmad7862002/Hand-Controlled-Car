 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: UART driver for AVR
 *
 * Author: Mokhtar Khaled
 *
 *******************************************************************************/
#include "uart.h"
#include "common_macros.h"	/* File which contains common macros like SET_BIT */
#include <avr/interrupt.h>	/* For ISR */
#define F_CPU 16000000UL
#if !UART_SEND_POOLING
static volatile uint8 g_byteToBeSent;
static volatile uint8 g_sentFlag = FALSE;

ISR(USART_UDRE_vect){
	if(g_sentFlag){
		UDR = g_byteToBeSent;
		g_sentFlag = FALSE;
	}
}
#endif

#if !UART_RECEIVE_POOLING
static volatile void (*g_ptr)(void) = NULL;
ISR(USART_RXC_vect){
	if(NULL != g_ptr && BIT_IS_CLEAR(UCSRA, FE) && BIT_IS_CLEAR(UCSRA, PE)){
		(*g_ptr)();
	}
}
#endif

#if UART_EXTRA_CONFIGS
/*******************************************************************************
• Description
       	 -The Functions initialises UART peripheral by the wanted configurations
• Inputs:
		 -configs: Pointer to structure which contains all the configurations
		  wanted (baudRate, characterSize, parity and stopBits)
• Return: None
 *******************************************************************************/
void UART_init(const UART_configurations* config){
	uint16 ubrrValue;
	SET_BIT(UCSRA, U2X);
	UCSRB |= (1 << RXEN) | (1 << TXEN);
#if !UART_RECEIVE_POOLING
	SET_BIT(UCSRB, RXCIE);
#endif
#if !UART_SEND_POOLING
	SET_BIT(UCSRB, UDRIE);
#endif
	CLEAR_BIT(UCSRB, UCSZ2);
	UCSRB |= ((((config -> characterSize) & 0x04) >> 3) << UCSZ2);
	SET_BIT(UCSRC, URSEL);
	UCSRC = (UCSRC & 0xCF) | (((config -> parity) & FIRST_TWO_BITS) << UPM0);
	CLEAR_BIT(UCSRC, USBS);
	UCSRC |= ((config -> stopBits) << USBS);
	UCSRC = (UCSRC & 0xF9) | (((config -> characterSize) & FIRST_TWO_BITS) << 1);
	ubrrValue = (F_CPU/(8.0 * (config -> baudRate))) - 1;
	UBRRL = (uint8)ubrrValue;
	UBRRH = ubrrValue >> 8;
}
#else
/*******************************************************************************
• Description
       	 -The Functions initialises UART peripheral by the wanted Baud Rate
• Inputs:
		 -baudRate: The desired bits wanted per second of the UART
• Return: None
 *******************************************************************************/
void UART_init(uint32 baudRate){
	uint16 ubrrValue;
	SET_BIT(UCSRA, U2X);
	UCSRB |= (1 << RXEN) | (1 << TXEN);
#if !UART_RECEIVE_POOLING
	SET_BIT(UCSRB, RXCIE);
#endif
#if !UART_SEND_POOLING
	SET_BIT(UCSRB, UDRIE);
#endif
	SET_BIT(UCSRC, URSEL);
	UCSRC |= (1 << UCSZ0) | (1 << UCSZ1);
	ubrrValue = (F_CPU/(8.0 * baudRate)) - 1;
	UBRRL = (uint8)(ubrrValue);
	UBRRH = ubrrValue >> 8;
}
#endif

/*******************************************************************************
• Description
       	 -If the function work with pooling, the code will stop until the UDR register
       	  is free then, the wanted byte will be inserted in the UDR register to start
       	  sending the byte
       	 -If the sending process works with interrupts, a global variable will store
       	  the wanted byte and when the UDR register is free, an interrupt will occur
       	  to send the wanted data. Note that if this function was called several times
       	  without knowing that the previous bit is sent, the global variable would be
       	  overwritten each time the function is called. Making the sending process to
       	  work with interrupts is not recommended.
• Inputs:
		 -a_byte: The byte required to be sent
• Return: None
 *******************************************************************************/
void UART_sendByte(uint8 a_byte){
#if UART_SEND_POOLING
	while(BIT_IS_CLEAR(UCSRA, UDRE));
	UDR = a_byte;
#else
	g_byteToBeSent = a_byte;
	g_sentFlag = TRUE;
#endif
}

/*******************************************************************************
• Description
       	 -The function returns the data stored in the UDR buffer if the RXC flag
       	  is set. Otherwise, it will send 0xFF
• Inputs: None
• Return:
		 UDR register value if RXC flag is set or 0xFF if not
 *******************************************************************************/
uint8 UART_getRecUartBuffer(void){
	if(BIT_IS_SET(UCSRA, RXC)){
		return UDR;
	}
	else{
		return 0xFF;
	}
}

#if UART_RECEIVE_POOLING
/*******************************************************************************
• Description
       	 -This function receives byte using busy pooling
• Inputs: None
• Return:
		 UDR register value if RXC flag is set or 0xFF if not
 *******************************************************************************/
uint8 UART_receiveByte(void){
	while(BIT_IS_CLEAR(UCSRA, RXC));
	if(BIT_IS_CLEAR(UCSRA, FE) && BIT_IS_CLEAR(UCSRA, PE)){
		return UDR;
	}
	else{
		return 0xFF;
	}
}
#else
/*******************************************************************************
• Description
       	 -This function takes a pointer to function as input to call this function
       	  when data is received and interrupt is occurred
• Inputs: (*a_ptr): The pointer to function which is called when interrupt occurs
• Return: None
 *******************************************************************************/
void UART_recSetCallBack(void (*a_ptr)(void)){
	g_ptr = a_ptr;
}
#endif

#if UART_SEND_POOLING
/*******************************************************************************
• Description
       	 -This function sends a C string. Note that this function only works if
       	  sending process works with pooling
• Inputs: (*string): The pointer to string which will be sent
• Return: None
 *******************************************************************************/
void UART_sendString(const uint8* string){
	while(*string != '\0'){
		UART_sendByte(*string);
		string++;
	}
}
#endif

#if UART_RECEIVE_POOLING
/*******************************************************************************
• Description
       	 -This function receives a string where the function must receive
       	  a delimeter to know what the end of the string would. Note that this
       	  function only works if receiving process works with pooling
• Inputs:
		-(*string): Pointer to string where the received bytes will be
		 	 	 	stored in that string
		-delimeter: The special character which will determine the end of the string
• Return: None
 *******************************************************************************/
void UART_receiveString(uint8* string, uint8 delimeter){
	uint8 rec;
	do{
		rec = UART_receiveByte();
		*string = rec;
		string++;
	}while(rec != delimeter);
	*string = '\0';
}
#endif
