/*
 * memory_addressing.c
 *
 *  Created on: Apr 2, 2024
 *      Author: sanga
 */

//#include "../../Core/Drivers/flash/internal_flash.h"
//#include "internal_flash.h"
//#include "MT25QL.h"
#include "memory_addressing.h"
uint8_t MUX_CS;
uint32_t teemp;
uint8_t FM_CS;
uint8_t SFM_CS;
SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi4;
//uint32_t EXTERNAL_FLASH_BLOCK_ADDRESS;


/*
 * @brief The function is responsible for toggling the value of Chip Select pin
 * @param
 * 			CS_GPIO_PORT - The gpio port number that is to be changed
 * 			CS_GPIO_PIN - The gpio pin number that is to be changed
 * 			CS_STATE - The variable reflecting the state of the pin. may be 0 or 1
 *
 * @ret Return void
 */
void TOGGLE_CS_PIN(uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN, uint8_t *CS_STATE){
	HAL_GPIO_WritePin(CS_GPIO_PORT, *CS_GPIO_PIN, *CS_STATE);
}


/*
 * @brief
 * @param
 * @ret
 *
 */

void MUX_ENABLE(SPI_HandleTypeDef *SPI_MUX, uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN){
	TOGGLE_CS_PIN(SPI_MUX, CS_GPIO_PORT, CS_GPIO_PIN);
}

/*
 * @brief
 * @param
 * @ret
 *
 */
void MUX_DISABLE(SPI_HandleTypeDef *SPI_MUX, uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN){
   TOGGLE_CS_PIN(SPI_MUX, CS_GPIO_PORT, CS_GPIO_PIN);
}

/*
 * @brief
 * @param
 * @ret
 *
 */


void SPI_TRANSMIT(SPI_HandleTypeDef *SPI, uint8_t COMMAND, uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN){
	TOGGLE_CS_PIN(CS_GPIO_PORT, CS_GPIO_PIN, 0);
	HAL_SPI_Transmit(SPI, COMMAND, sizeof(COMMAND), 1000);
	TOGGLE_CS_PIN(CS_GPIO_PORT, CS_GPIO_PIN, 1);
}


/*
 * @brief
 * @param
 * @ret
 *
 */
void SPI_RECEIVE(SPI_HandleTypeDef *SPI, uint8_t COMMAND, uint8_t *DATA, uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN){
TOGGLE_CS_PIN(CS_GPIO_PORT, CS_GPIO_PIN, CS_LOW);
HAL_SPI_Receive(SPI, COMMAND, sizeof(COMMAND), 1000);
TOGGLE_CS_PIN(CS_GPIO_PORT, CS_GPIO_PIN, CS_HIGH);

}

/*
 * @brief
 * @param
 * @ret
 *
 */
void SPI_TRANSMITRECEIVE(SPI_HandleTypeDef *SPI, uint8_t COMMAND, uint8_t *DATA, uint8_t *CS_GPIO_PORT, uint8_t *CS_GPIO_PIN ){
	TOGGLE_CS_PIN(CS_GPIO_PORT, CS_GPIO_PIN, CS_LOW);
	uint8_t sizeOfData = sizeof(COMMAND)+sizeof(DATA);
	HAL_SPI_TransmitReceive(SPI, COMMAND, DATA, sizeOfData, 1000);
	TOGGLE_CS_PIN(CS_GPIO_PORT, CS_GPIO_PIN, CS_HIGH);
}

/*
 * @brief
 * @param
 * @ret
 *
 */
void get_current_address(SPI_HandleTypeDef *SPI, uint8_t choice){ //,
	uint8_t read_buffer[4];
	uint8_t sector = 22;
	uint32_t  INTERNAL_FLASH_SECTOR_ADDRESS; //INTERNAL_FLASH_SECTOR,
	INTERNAL_FLASH_SECTOR_ADDRESS = BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA + choice*10;
	switch(choice){
	case 0 : EXTERNAL_FLASH_BLOCK_ADDRESS = STARTING_BLOCK_EXTERNAL_FLASH_HK_DATA;
				break;
	case 1: EXTERNAL_FLASH_BLOCK_ADDRESS = STARTING_BLOCK_EXTERNAL_FLAG_DATA;
			break;
	case 2: EXTERNAL_FLASH_BLOCK_ADDRESS = STARTING_BLOCK_EXTERNAL_FLASH_SAT_LOG;
			break;
	case 3 : EXTERNAL_FLASH_BLOCK_ADDRESS = STARTING_BLOCK_EXTERNAL_FLASH_RSV ;
			break;
	case 4 : EXTERNAL_FLASH_BLOCK_ADDRESS = STARTING_BLOCK_EXTERNAL_FLASH_COM;
			break;
	case 5 : EXTERNAL_FLASH_BLOCK_ADDRESS = STARTING_BLOCK_EXTERNAL_FLASH_MSN1;
			break;
	case 6 : EXTERNAL_FLASH_BLOCK_ADDRESS = STARTING_BLOCK_EXTERNAL_FLASH_MSN2;
			break;
	case 7 : EXTERNAL_FLASH_BLOCK_ADDRESS = STARTING_BLOCK_EXTERNAL_FLASH_MSN3;
				break;
	case 8 : EXTERNAL_FLASH_BLOCK_ADDRESS = STARTING_BLOCK_EXTERNAL_FLASH_MSN4;
			break;

	default : break;
	}
//	INTERNAL_FLASH_SECTOR_ADDRESS += choice*3;

	READ_FRM_INTERNAL_FLASH(INTERNAL_FLASH_SECTOR_ADDRESS, &read_buffer, 4);
	uint32_t read_buffer1 = read_buffer[0]<<24 | read_buffer[1]<<16 |read_buffer[2]<<8 |read_buffer[3];
	if(read_buffer1 == 0x00000000 || read_buffer1 == 0xffffffff){
//		When the block of the internal flash is empty then write sector address of main flash memory to internal flash memory
		ERASE_INTERNAL_FLASH(INTERNAL_FLASH_SECTOR_ADDRESS);
//		EXTERNAL_FLASH_BLOCK_ADDRESS = INTERNAL_FLASH_SECTOR_ADDRESS;
		WRITE_TO_INTERNAL_FLASH(sector, INTERNAL_FLASH_SECTOR_ADDRESS, EXTERNAL_FLASH_BLOCK_ADDRESS, 1);
	}
	else
	{
		EXTERNAL_FLASH_BLOCK_ADDRESS = read_buffer1;
	}

}

/*
 * @brief This function is responsible for checking data consistency of flash and shared flash memory
 * @param
 * @ret Returns 0 if data is consistent, 1 if MFM has more data than OBC otherwise 2 SFM has more data than MFM i.e. data is inconsistent in FM.
 */
uint8_t CHECK_DATA_CONSISTENCY_FM(uint8_t block_address, uint8_t choice){
	uint32_t read_main_fm_address = 0x00000000, read_shared_fm_address = 0x00000000;
	READ_FRM_INTERNAL_FLASH(block_address, read_main_fm_address, sizeof(read_main_fm_address));
	READ_FRM_INTERNAL_FLASH(block_address, read_shared_fm_address, sizeof(read_shared_fm_address));
	if(read_main_fm_address == read_shared_fm_address){
		return 0;
	}
	else if(read_main_fm_address > read_shared_fm_address){
		return 1;
	}
		return 2;
}

/*
 * @brief The function is used to check consistency for user divided subsectors i.e. hk,com,rsv, and msn addresses
 * @param Zero number of arguments are to be passed
 * @ret Returns nothing
 */
void CHECK_EACH_ADDRESS_CONSISTENCY(){
	uint32_t internal_temp_address = BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA;
	uint32_t FM_address = internal_temp_address, difference=0;
	uint8_t check = -1;
	for(int i = 0 ;i < 10; i++){
		check = CHECK_DATA_CONSISTENCY_FM(FM_address, FM_address +5);
		if(check ==1){
			TRANSFER_DATA_BETWEEN_FM(1,FM_address,difference);
		}
		else if(check == 2){
			TRANSFER_DATA_BETWEEN_FM(0, FM_address+5,difference);
		}
	}


}


/*
 * @brief This function is responsible for transferring data between two flash memories
 * @param Two parameters are to be sent as argument where address indicates the inconsistent memory address
 * 			and choice indicates the direction (may be from FM to SFM or SFM to FM)
 * @ret Returns nothing
 *
 */
void TRANSFER_DATA_BETWEEN_FM(uint8_t choice, uint32_t address, uint32_t difference){
	uint8_t data=0;
	SPI_HandleTypeDef *SPI_TO, *SPI_FROM;
	if(choice ==1 ){
		 SPI_TO = &MFM_SPI_HANDLETYPEDEF;
		 SPI_FROM = &SFM_SPI_HANLETYPEDEF;
	}
	else{
		 SPI_FROM = &MFM_SPI_HANDLETYPEDEF;
		 SPI_TO = &SFM_SPI_HANLETYPEDEF;
	}
	Sector_Erase_4B(SPI_TO, address, 4);
//	To DO: transfer missing data from one fm to another can be done 1 byte a time or multiple bytes at a time
//	Bulk_Read_4B(SPI, &address, data,4);
//	Page_Write_4B();
}



/*
 *
 *
 */

void SAVE_SAT_LOG(){

}



/*
 *
 */

void SAVE_FLAG_STATUS(){

}

/*
 *
 */
void SAVE_COM_DATA(){

}

/*
 *
 */

void SAVE_MSN1_DATA(){

}
/*
 *
 */
void SAVE_MSN2_DATA(){

}

/*
 *
 */
void SAVE_MSN3_DATA(){

}

/*
 *
 */
void SAVE_MSN4_DATA(){

}

/*
 *
 */

void READ_DATA_FROM_FM(){

}

//void SAVE_HK_DATA(){
////	get_current_address(&MFM_SPI_HANDLETYPEDEF,0);
////
////	for(int8_t row = 0; row <18; row+=2){
////		SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, &EXTERNAL_FLASH_BLOCK_ADDRESS,4, (int16_t)(SAT_IMU[row]<<8 | SAT_IMU[row+1]));
////	}
////	SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, &EXTERNAL_FLASH_BLOCK_ADDRESS,4, 0x32);
////	SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, &EXTERNAL_FLASH_BLOCK_ADDRESS,4, 0x32);
////	SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, &EXTERNAL_FLASH_BLOCK_ADDRESS,4, 0x32);
////	SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, &EXTERNAL_FLASH_BLOCK_ADDRESS,4, 0x32);
////	EXTERNAL_FLASH_BLOCK_ADDRESS = 0x00000000;
//}
/*
 *
 */
//void SAVE_DATA(SPI_HandleTypeDef *SPI, uint32_t *address, uint8_t sector_size, int16_t *data){
////	ADDRESSING_MODE(SPI, 1);
//	Sector_Erase_4B(SPI, address, sector_size);
//	Byte_Write_4B(SPI, address, data);
//
//}

/*
 *
*/
void READ_FM_DATA(SPI_HandleTypeDef *SPI, uint32_t address, uint8_t *data,uint16_t size){
//	EXTERNAL_FLASH_BLOCK_ADDRESS = address;
////	Bulk_Read_4B(SPI, address, data, size);
//	Sector_Erase_4B(&hspi3, 0x08020001, 4);//STARTING_BLOCK_EXTERNAL_FLASH_HK_DATA
////	Byte_Write_4B(&hspi3, STARTING_BLOCK_EXTERNAL_FLASH_HK_DATA,0x0000A001);
//	Byte_Write_4B(&hspi3, 0x08020001, 0x07);
//	teemp = Read_Byte_4B(&hspi3, 0x08020001);
}

