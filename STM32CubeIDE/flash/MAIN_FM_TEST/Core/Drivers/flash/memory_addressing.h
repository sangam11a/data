/*
 * memory_addressing.h
 *
 *  Created on: Apr 2, 2024
 *      Author: sanga
 */
#pragma once
#ifndef DRIVERS_FLASH_MEMORY_ADDRESSING_H_
#define DRIVERS_FLASH_MEMORY_ADDRESSING_H_

#include "variables.h"
#include "internal_flash.h"

//#define CS_HIGH 1
//#define CS_LOW 0


enum WHO_SAVES_DATA{
	OBC = 0,
	RSV,
	FLAG,
	SAT_LOG,
	COM,
	MSN1,
	MSN2,
	MSN3,
	MSN4
} who_saves_data;


void TOGGLE_CS_PIN(uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN, uint8_t *CS_STATE);
void MUX_ENABLE(SPI_HandleTypeDef *SPI_MUX, uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN);
void MUX_DISABLE(SPI_HandleTypeDef *SPI_MUX, uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN);
void SPI_TRANSMIT(SPI_HandleTypeDef *SPI,uint8_t COMMAND ,uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN);
void SPI_RECEIVE(SPI_HandleTypeDef *SPI, uint8_t COMMAND , uint8_t *DATA, uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN);
void SPI_TRANSMITRECEIVE(SPI_HandleTypeDef *SPI, uint8_t COMMAND ,uint8_t *DATA, uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN);
void get_current_address(SPI_HandleTypeDef *SPI,uint8_t choice);
uint8_t CHECK_DATA_CONSISTENCY_FM(uint8_t block_address, uint8_t choice);
void CHECK_EACH_ADDRESS_CONSISTENCY();
void TRANSFER_DATA_BETWEEN_FM(uint8_t choice, uint32_t address, uint32_t difference);


void SAVE_SAT_LOG();
void SAVE_FLAG_STATUS();
void SAVE_COM_DATA();
void SAVE_MSN1_DATA();
void SAVE_MSN2_DATA();
void SAVE_MSN3_DATA();
void SAVE_MSN4_DATA();

//void SAVE_DATA(SPI_HandleTypeDef *SPI, uint32_t address, uint8_t sector_size, int16_t *data);
void SAVE_HK_DATA();
//void READ_FM_DATA(SPI_HandleTypeDef *SPI, uint32_t address, uint8_t data,uint16_t size);
void SAVE_DATA(SPI_HandleTypeDef *SPI, uint32_t *address, uint8_t sector_size, int16_t *data);
void READ_FM_DATA(SPI_HandleTypeDef *SPI, uint32_t address, uint8_t *data,uint16_t size);
#endif /* DRIVERS_FLASH_MEMORY_ADDRESSING_H_ */
