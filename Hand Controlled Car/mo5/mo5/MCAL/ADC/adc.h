 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for ADC driver
 *
 * Author: Mokhtar Khaled
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_OF_ADCS		8

#define ADC_MAX_VALUE		1023
#define ADC_REF_VOLTAGE		2.56

#define ADC0_ID			0
#define ADC1_ID			1
#define ADC2_ID			2
#define ADC3_ID			3
#define ADC4_ID			4
#define ADC5_ID			5
#define ADC6_ID			6
#define ADC7_ID			7

/*******************************************************************************
 *                          User Defined Data Types                            *
 *******************************************************************************/

typedef enum{
	AREF, AVCC, INTERNAL = 3
}ADC_ReferenceVolatge;

typedef enum{
	F_CPU_2 = 1, F_CPU_4, F_CPU_8, F_CPU_16, F_CPU_32, F_CPU_64, F_CPU_128
}ADC_Prescaler;

typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                            Function Prototypes                              *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr);
uint16 ADC_readChannel(uint8 ch_num);

#endif /* ADC_H_ */
