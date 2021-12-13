 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: ADC driver
 *
 * Author: Mokhtar Khaled
 *
 *******************************************************************************/

#include "adc.h"
#include "registers.h"	/* File containing all registers needed */
#include "common_macros.h"  /* File containing macros like SET_BIT */

/*******************************************************************************
• Description
		-Adjust the reference voltage
		-Enable ADC
		-Adjust the prescaler value
• Inputs:
		- Config_Ptr: This is a pointer to structure containing the reference
					  voltage (AREF, AVCC or INTERNAL)
					  It also contains prescaler value (F_CPU_2, F_CPU_4, F_CPU_8,....)
• Return: None
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr){
	/* Insert reference voltage wanted in ADMUX register */
	ADMUX = (ADMUX & FIRST_SIX_BITS) | (((Config_Ptr -> ref_volt) & FIRST_TWO_BITS) << 6);
	/* Enable ADC */
	SET_BIT(ADCSRA, ADEN);
	/* Insert Prescaler value in ADCSRA register */
	ADCSRA = (ADCSRA & LAST_FIVE_BITS) | ((Config_Ptr -> prescaler) & FIRST_THREE_BITS);
}

/*******************************************************************************
• Description
		-Insert the ADC channel number (from 0 -> 7)
		-Start conversion
		-Wait until conversion is finished (pooling technique)
• Inputs:
		- ch_num: Which ADC needed to be start converting
• Return:
		- returnValue: The analog converted to digital output (0 -> 1023)
 *******************************************************************************/

uint16 ADC_readChannel(uint8 ch_num){
	uint16 returnValue = 0;
	if(ch_num >= NUM_OF_ADCS){
		/* Return FFFF if the ch_num is not correct */
		returnValue = 0xFFFF;
	}
	else{
		/* Insert the ch_num in ADMUX register */
		ADMUX = (ADMUX & LAST_THREE_BITS) | (ch_num & FIRST_THREE_BITS);
		/* Start Conversion */
		SET_BIT(ADCSRA, ADSC);
		/* Wait until flag is raised (pooling) */
		while(BIT_IS_CLEAR(ADCSRA, ADIF));
		/* Clear flag */
		SET_BIT(ADCSRA, ADIF);
		returnValue = ADC;
	}
	return returnValue;
}
