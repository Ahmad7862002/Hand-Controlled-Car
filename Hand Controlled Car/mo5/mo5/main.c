/*
 * mo5.c
 *
 * Created: 28-Nov-21 12:08:26 AM
 * Author : AHMAD
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "uart.h"
#include "util/delay.h"
#include "adc.h"
#include "gpio.h"
#define F_CPU 16000000UL

int main(void)
{   
    ADC_ConfigType  adchelp={
	    AVCC,
	    F_CPU_8
    };
	UART_configurations configs = {
		9600,
    	BITS_5,
	    NO_PARITY,
    	BITS_1
	};
    UART_init(&configs);   
    ADC_init(&adchelp);
    uint8 q0=FALSE,q1= FALSE,q2=FALSE,q3= FALSE,q4=FALSE;
    uint16 val0,val1,val2,val3,val4;

    /* Replace with your application code */
    while (1) 
    {
	
      val0 = ADC_readChannel(ADC0_ID);  
      val1 = ADC_readChannel(ADC1_ID);
      val2 = ADC_readChannel(ADC2_ID);
      val3 = ADC_readChannel(ADC3_ID);
	
   
		//////////////////////////////////////////////////////////////////////



		if ( val0 >145){
			q0 = TRUE;
		}
		else {
		q0 = FALSE;
		}
		
		if ( val1 >420){
			q1= TRUE;
		}
		
		else {
			q1= FALSE;
		}
        
		if ( val2 >110){
			q2= TRUE;
		}
		
		else {
			q2= FALSE;
		}

		if ( val3 >135){
			q3= TRUE;
		}
		
		else {
			q3= FALSE;
		}

		
		
		////////////////////////////////////////////////////
		
		
		if (q0 == TRUE && q1 == FALSE && q2 == FALSE&& q3 == FALSE ){
	        UART_sendByte(17);
		}
		else if (q0 == FALSE && q1 == FALSE && q2 == FALSE&& q3 == TRUE){
	     	UART_sendByte(18);
		}
		else if (q0 == TRUE && q1 == TRUE && q2 == TRUE && q3 == TRUE){
			UART_sendByte(19);
		}
		else if (q0 == FALSE && q1 == FALSE&& q2 == TRUE&& q3 == FALSE){
			UART_sendByte(20);
		}
		else if (q0 == FALSE && q1 == TRUE && q2 == TRUE&& q3 == FALSE ){
			UART_sendByte(21);
		}
		else if(q0 == FALSE && q1 == FALSE && q2 == FALSE&& q3 == FALSE){
			UART_sendByte(22);
		}
		
		





		
    }
}

