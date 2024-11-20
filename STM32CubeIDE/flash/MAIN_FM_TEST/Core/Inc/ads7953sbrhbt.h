/*
 * ads7953sbrhbt.h
 *
 *  Created on: Mar 25, 2024
 *      Author: sanga
 */

#pragma once

#ifndef INC_ADS7953SDBT_H_
#define INC_ADS7953SDBT_H_

//#include "main.h"
#include "variables.h"

extern SPI_HandleTypeDef hspi2;
extern uint8_t adc_data[2];
extern uint8_t adc1_data[2];
extern int i, j;

//command codes definition for ADS7953SDBT analog to digital converter.

/*commands to set the modes of the ADC*/
#define 		MANUAL_MODE  			0b0001101011000000
#define 		AUTO_1_MODE 			0b0010110000001111
#define 		AUTO_2_MODE 			0b0011110000000000
#define 		AUTO_2_MODE2 			0b0011100000000000

/*commands to program the modes of the ADC*/
#define			AUTO_1_PROGRAM			0b1000000000000000			//this makes the ADC to go into programming AUTO-1 mode.
#define 		AUTO_1_SEQUENCE			0b0111111111111111			//this gives the sequence of the channels to be sampled.
#define 		ADC_AUTO_2_PROGRAM			0b1001000111000000	//default - 0b1001000111000000	//change the last channel number for FM. changed in EM for testing purposes.
#define 		ADC1_AUTO_2_PROGRAM			0b1001001011000000

/*command to keep operating in the same selected mode*/
#define			CONTINUE_OPERATION 		0b0000000000000000

/*commands for GPIO program register settings*/
#define 		GPIO_PROGRAM			0b0100001

//need to see the commands for the alarm.(to ask)

typedef enum _operation_modes{
	ADC_SELECT= 1,
	ADC_READ = 2
} operation_modes;

typedef enum _adc_mode_selection{
	MANUAL_MODE_SELECTION= 1,
	AUTO_MODE_1_SELECTION = 2,
	AUTO_MODE_2_SELECTION =3
} adc_mode_selection;

/*functions prototypes for ADC*/
void ADC_MODE_SELECTION(adc_mode_selection adc_mode);

void ADC_Enable();
void ADC1_DMA_CONVERT();
void ADC_Disable();
void ADC_GPIO_Register();
void MANUAL_Select();
void AUTO_2_Select_ADC(operation_modes mode);
void ADC_AUTO_2_Program();
void Continue_Operaion(uint8_t *data);
void ADC_CombineData(uint16_t *adc_channels);
void ADC_Conv_Data(float *adc_conv_buf, uint16_t *adc_buf);
void ADC1_Conv_Data(float *adc_conv_buf, uint16_t *adc_buf);
void ADC_Operate(uint16_t *adc_channels);
void ADC_Temp_Conv(float *adc1_conv_buf, float *temp_buf);
//uint16_t ADC_Receive(uint16_t *data);

#endif /* INC_ADS7953SDBT_H_ */
