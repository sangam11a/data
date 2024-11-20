/*
 * internal_flash.h
 *
 *  Created on: Apr 1, 2024
 *      Author: sanga
 */

#pragma
#ifndef INC_INTERNAL_FLASH_H_
#define INC_INTERNAL_FLASH_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"

#include "stm32f4xx_hal_flash.h"

#define FLASH_USER_START_ADDR   0x8000000   // Adjust this based on the start address of the flash sector you want to use
#define DATA_SIZE               32
#define START_ADD 0x80000000
#define FLASHWORD		8

extern const uint32_t ADDRESS_LOC_SECTOR;
extern uint32_t flashAddress;

static uint32_t GetSector(uint32_t Address);
HAL_StatusTypeDef WRITE_TO_INTERNAL_FLASH(uint32_t sector,uint32_t write_address, uint32_t *DATA, uint8_t data_len) ;
void READ_FRM_INTERNAL_FLASH(uint32_t address, uint8_t *read_buff, uint32_t len);
void ERASE_DATA_INTERNAL_FLASH(uint32_t );

#endif /* INC_INTERNAL_FLASH_H_ */
