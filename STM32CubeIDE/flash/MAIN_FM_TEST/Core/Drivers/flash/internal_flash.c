/*
 * internal_flash.c
 *
 *  Created on: Apr 1, 2024
 *      Author: sanga
 */

#include "stdint.h"

#include "internal_flash.h"
            // Adjust this based on the size of data you want to write

uint32_t flashAddress = FLASH_USER_START_ADDR;

const uint32_t ADDRESS_LOC_SECTOR = 22;
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;

  /* BANK 1 */
  if((Address >= 0x08000000) && (Address < 0x08020000))
  {
    sector = FLASH_SECTOR_0;
  }

  else if((Address >= 0x08040000) && (Address < 0x08080000))
  {
    sector = FLASH_SECTOR_1;
  }


  else if((Address >= 0x08080000) && (Address < 0x080C0000))
  {
    sector = FLASH_SECTOR_2;
  }
  else if((Address >= 0x080C0000) && (Address < 0x080F0000))
  {
    sector = FLASH_SECTOR_3;
  }

  else if((Address >= 0x08010000) && (Address < 0x08020000))
  {
    sector = FLASH_SECTOR_4;
  }


  /* BANK 2 */
  if((Address >= 0x08020000) && (Address < 0x08040000))
  {
    sector = FLASH_SECTOR_5;
  }

  else if((Address >= 0x08040000) && (Address < 0x08060000))
  {
    sector = FLASH_SECTOR_6;
  }

  else if((Address >= 0x08060000) && (Address < 0x08080000))
  {
    sector = FLASH_SECTOR_7;
  }

  else if((Address >= 0x08080000) && (Address < 0x080A0000))
  {
    sector = FLASH_SECTOR_8;
  }

  else if((Address >= 0x080A0000) && (Address < 0x080C0000))
  {
    sector = FLASH_SECTOR_9;
  }

  else if((Address >= 0x080C0000) && (Address < 0x080E0000))
  {
    sector = FLASH_SECTOR_10;
  }

  else if((Address >= 0x080E0000) && (Address < 0x08100000))
  {
    sector = FLASH_SECTOR_11;
  }



  return sector;
}



uint8_t bytes_temp[4];





HAL_StatusTypeDef WRITE_TO_INTERNAL_FLASH(uint32_t sector,uint32_t write_address, uint32_t *DATA, uint8_t data_len) {
HAL_StatusTypeDef OPER_STAT;
uint8_t buff[data_len];
for (int i = 0; i < data_len; i++) {
	buff[i] = *DATA++;
}

HAL_FLASH_Unlock();

for (int i = 0; i < data_len; i++) {
	OPER_STAT = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, write_address,(uint8_t) buff[i]);
	HAL_Delay(10);
	if (OPER_STAT != HAL_OK) {
		HAL_FLASH_Lock();
		HAL_Delay(10);
		return OPER_STAT;
	}
	write_address++;
}
HAL_FLASH_Lock();
return OPER_STAT;
}

/*
* @brief Reads data from given address of the internal flash
*
* @param	Address		Address from where data is to be read
* 			Read_Buffer	pointer to the location where address is to be written
* 			len			no of bytes to be read
* @retval	none
*
*/
void READ_FRM_INTERNAL_FLASH(uint32_t address, uint8_t *read_buff, uint32_t len) {

	for (int i = 0; i < len; i++) {
		*(read_buff + i) = *(uint8_t*) address;
		address++;
	}

}

/*
 *
 */

void ERASE_INTERNAL_FLASH(uint32_t SECTOR_NUMBER){
HAL_FLASH_Unlock();
FLASH_Erase_Sector(SECTOR_NUMBER, FLASH_SECTOR_1);
// FLASH_VOLTAGE_RANGE_3 = 0x0000002U i.e. erase flash by 32 bits ffrom the current sector number or block.  default value in stm32xxhal.h

FLASH_Erase_Sector(SECTOR_NUMBER, FLASH_SECTOR_2);

FLASH_Erase_Sector(SECTOR_NUMBER, FLASH_SECTOR_3);

FLASH_Erase_Sector(SECTOR_NUMBER, FLASH_SECTOR_4);
HAL_FLASH_Lock();
}
