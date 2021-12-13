 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: UART Driver
 *
 * Author: Mokhtar Khaled
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define UART_SEND_POOLING 	 TRUE
#define UART_RECEIVE_POOLING FALSE

#define UART_EXTRA_CONFIGS	 TRUE

/*******************************************************************************
 *                          USER DEFINED DATA TYPES                            *
 *******************************************************************************/

typedef enum{
	BITS_5, BITS_6, BITS_7, BITS_8
}UART_CharacterSize;

typedef enum{
	NO_PARITY, PARITY_EVEN = 2, PARITY_ODD = 3
}UART_Parity;

typedef enum{
	BITS_1, BITS_2
}UART_StopBits;

typedef struct{
	uint32 baudRate;
	UART_CharacterSize characterSize;
	UART_Parity parity;
	UART_StopBits stopBits;
}UART_configurations;

/*******************************************************************************
 *                             FUNCTION PROTOTYPES                             *
 *******************************************************************************/

#if UART_EXTRA_CONFIGS
void UART_init(const UART_configurations* config);
#else
void UART_init(uint32 baudRate);
#endif
void UART_sendByte(uint8 a_byte);
uint8 UART_getRecUartBuffer(void);
#if UART_RECEIVE_POOLING
uint8 UART_receiveByte(void);
void UART_receiveString(uint8* string, uint8 delimeter);
#else
void UART_recSetCallBack(void (*a_ptr)(void));
#endif
#if UART_SEND_POOLING
void UART_sendString(const uint8* string);
#endif

#endif /* UART_H_ */
