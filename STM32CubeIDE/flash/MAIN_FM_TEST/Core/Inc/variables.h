/*
 * variables.h
 *
 *  Created on: Mar 26, 2024
 *      Author: sanga
 */


#pragma once

#include "string.h"
#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "math.h"
//#include "../../Core/Drivers/flash/MT25QL.h"
//#include "../../Core/Drivers/flash/memory_addressing.h"
//#include "../../Core/Drivers/flash/internal_flash.h"

#ifndef INC_VARIABLES_H_
#define INC_VARIABLES_H_


/*
 * Starting ADC definition code
 */

//ADC
#define ADC_CS_GPIO_PORT GPIOD
#define ADC_CS_GPIO_PIN GPIO_PIN_9
#define ADC_SCK_GPIO_PORT GPIOB
#define ADC_SCK_GPIO_PIN GPIO_PIN_13
#define ADC_MISO_GPIO_PORT GPIOB
#define ADC_MISO_GPIO_PIN GPIO_PIN_14
#define ADC_MOSI_GPIO_PORT GPIOB
#define ADC_MOSI_GPIO_PIN GPIO_PIN_15

//ADC
#define E_ADC hspi2
#define E_ADC_0_DATA_LEN 16
#define I_ADC1 hadc1
#define I_ADC1_DATA_LEN 7
#define ADC_LOOP_MAX 200
#define OBC_DEBUG huart7

/*
 * Ending ADC definition code
 */



uint8_t E_ADC0_RAW[E_ADC_0_DATA_LEN];
float EXT_ADC_0[E_ADC_0_DATA_LEN];
float EXT_ADC_0_TEMP[E_ADC_0_DATA_LEN];

/*
 * Starting IMU or MPU6500 definition code
 */

SPI_HandleTypeDef hspi5;
SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi4;

//UART_HandleTypeDef huart6;
UART_HandleTypeDef huart4;
//UART_HandleTypeDef huart1;
UART_HandleTypeDef huart7;

#define IMU_STREAM hspi5
#define IMU_CS_GPIO_PORT GPIOH
#define IMU_CS_GPIO_PIN GPIO_PIN_10
#define MAG_CS_GPIO_PORT GPIOF
#define MAG_CS_GPIO_PIN GPIO_PIN_12
#define DEBUG_STREAM huart4


uint8_t check;
uint8_t accelPitch, accelRoll;


/*
 *
 *
 */
#define MAIN_FM hspi3
#define SMSN_FM hspi4

/*
 *
 *
 */



/*
 *
 * Ending IMU definition code
 */

/*
 * structure definition for collecting data of satellite health
 */

	typedef struct __attribute__((__packed__)) _SAT_HEALTH_Typedef{
		uint8_t HEAD;
		uint8_t TIM_DAYS;
		uint8_t TIM_HOURS;
		uint8_t TIM_MINS;
		uint8_t TIM_SECONDS;
		uint8_t ANTENNA_DEPLOYMENT_STATUS;
		uint8_t OPERATION_MODE;
		uint8_t MSN1_STATUS;
		uint8_t MSN2_STATUS;
		uint8_t MSN3_STATUS;
		uint8_t KILL_SWITCH_STATUS;

//		battery health statuss
		int16_t BATT_VOLT;
		int16_t BATT_TEMPERATURE;
		int16_t BATT_CURRENT;
//		solar panel and other power source current status
		int16_t SOLAR_PANEL1_CURRENT;
		int16_t SOLAR_PANEL2_CURRENT;
		int16_t SOLAR_PANEL3_CURRENT;
		int16_t SOLAR_PANEL4_CURRENT;
		int16_t RAW_CURRENT;
		uint16_t _3V3_1_CURRENT;
		uint16_t _3V3_2_CURRENT;
		uint16_t _5V_CURRENT;
		uint16_t UNREG1_CURRENT;
		uint16_t UNREG2_CURRENT;

//		solar panel voltage status
		int16_t SOLAR_PANEL1_VOLT;
		int16_t SOLAR_PANEL2_VOLT;
		int16_t SOLAR_PANEL3_VOLT;
		int16_t SOLAR_PANLE4_VOLT;
		int16_t RAW_VOLT;

//		temperatures
		int16_t Y_TEMP;
		int16_t Z_TEMP;
		int16_t Y1_TEMP;
		int16_t Z1_TEMP;
		int16_t BPB_TEMP;
		int16_t OBC_TEMP;
		int16_t COM_TEMP;

//		IMU DATA
		int16_t ACCEL_X;
		int16_t ACCEL_Y;
		int16_t ACCEL_Z;

		int16_t GYRO_X;
		int16_t GYRO_Y;
		int16_t GYRO_Z;

		int16_t MAG_X;
		int16_t MAG_Y;
		int16_t MAG_Z;

//		OTHERS
		uint16_t OBC_ABNL_RST;
		uint16_t RST_TIME; //Time passed after last OBC reset
		uint16_t CHK_SUM; //This checksum is for data consistency

	} SAT_HEALTH_TYPEDEF;
	SAT_HEALTH_TYPEDEF sat_health;
/*
 * end of satellite health
 */



	/*
	 *
	 */
//	typedef struct MPU6500 {
//		struct RawData {
//			int16_t ax, ay, az, gx, gy, gz;
//		} rawData;
//
//		struct SensorData {
//			float aScaleFactor, gScaleFactor;
//			float ax, ay, az, gx, gy, gz;
//		} sensorData;
//
//		struct GyroCal {
//			float x, y, z;
//		} gyroCal;
//
//		struct Attitude {
//			float tau, dt;
//			float r, p, y;
//		} attitude;
//
//		struct Settings {
//			uint8_t aFullScaleRange, gFullScaleRange;
//			GPIO_TypeDef *CS_PORT;
//			uint8_t CS_PIN;
//		} settings;
//	} MPU6500_t;

//	extern MPU6500_t MPU6500;
	/*
	 *
	 */

/*
 * VARIABLES RELATED TO EXTERNAL ADC
 */
	extern volatile uint16_t I_ADC1_RAW[I_ADC1_DATA_LEN][ADC_LOOP_MAX];
	extern volatile uint16_t I_ADC1_RAW[I_ADC1_DATA_LEN][ADC_LOOP_MAX];
	extern int averageRaw[I_ADC1_DATA_LEN];
	extern float I_ADC1_Data[I_ADC1_DATA_LEN];

/*
 *
 */

	/*
	 * Definition of extern variables for MUX, FM, SFM
	 */
	extern uint8_t MUX_CS;
	extern uint8_t FM_CS;
	extern uint8_t SFM_CS;

	SPI_HandleTypeDef hspi2;
	SPI_HandleTypeDef hspi3;
	extern SPI_HandleTypeDef hspi4;
	volatile uint32_t EXTERNAL_FLASH_BLOCK_ADDRESS;
	//extern uint32_t
	/*
	 *
	 */

	#define SPI_MUX_EN_GPIO_PORT GPIOG
	#define SPI_MUX_EN_GPIO_PIN GPIO_PIN_6
	#define SPI_MFM_CS_GPIO_PORT GPIOI
	#define SPI_MFM_CS_GPIO_PIN GPIO_PIN_7
	#define SPI_SFM_CS_GPIO_PORT GPIOI
	#define SPI_SFM_CS_GPIO_PIN GPIO_PIN_6
	#define MFM_SPI_HANDLETYPEDEF hspi3
	#define SFM_SPI_HANLETYPEDEF hspi4

	#define CS_LOW 0
	#define CS_HIGH 1
	/*
	 * Defining a constant starting address block
	 */
	#define PAGE_GAP 256
	#define BLOCKS_PER_SECTOR 65535
	#define GAP_BETWEEN_TWO_BLOCKS 4
	#define SECTOR_ADDRESS_GAP 2046/6
	#define BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA 0x0800C000
	#define BLOCK_ADDRESS_INTERNAL_FLASH_RSV 0x0800C00A
	#define BLOCK_ADDRESS_INTERNAL_FLASH_COM 0x0800C01E
	#define BLOCK_ADDRESS_INTERNAL_FLASH_MSN1 0x0800C028
	#define BLOCK_ADDRESS_INTERNAL_FLASH_MSN2 0x0800C03C
	#define BLOCK_ADDRESS_INTERNAL_FLASH_MSN3 0x0800C046
	#define BLOCK_ADDRESS_INTERNAL_FLASH_MSN4 0x0800C050
	#define BLOCK_ADDRESS_INTERNAL_SAT_LOG 0x0800C064
	#define BLOCK_ADDRESS_INTERNAL_FLAG_DATA 0x0800C06e

	/*
	 *
	 */

	#define STARTING_BLOCK_EXTERNAL_FLASH_HK_DATA BLOCKS_PER_SECTOR*2
	#define STARTING_BLOCK_EXTERNAL_FLAG_DATA BLOCKS_PER_SECTOR*401
	#define STARTING_BLOCK_EXTERNAL_FLASH_SAT_LOG BLOCKS_PER_SECTOR*412
	#define STARTING_BLOCK_EXTERNAL_FLASH_RSV BLOCKS_PER_SECTOR*725
	#define STARTING_BLOCK_EXTERNAL_FLASH_COM BLOCKS_PER_SECTOR*735
	#define STARTING_BLOCK_EXTERNAL_FLASH_MSN1 BLOCKS_PER_SECTOR*831
	#define STARTING_BLOCK_EXTERNAL_FLASH_MSN2 BLOCKS_PER_SECTOR*991
	#define STARTING_BLOCK_EXTERNAL_FLASH_MSN3 BLOCKS_PER_SECTOR*1601
	#define STARTING_BLOCK_EXTERNAL_FLASH_MSN4 BLOCKS_PER_SECTOR*1801



	#define ENDING_BLOCK_EXTERNAL_FLASH_HK_DATA BLOCKS_PER_SECTOR*400
	#define ENDING_BLOCK_EXTERNAL_FLAG_DATA BLOCKS_PER_SECTOR*411
	#define ENDING_BLOCK_EXTERNAL_FLASH_SAT_LOG BLOCKS_PER_SECTOR*724
	#define ENDING_BLOCK_EXTERNAL_FLASH_RSV BLOCKS_PER_SECTOR*734
	#define ENDING_BLOCK_EXTERNAL_FLASH_COM BLOCKS_PER_SECTOR*830
	#define ENDING_BLOCK_EXTERNAL_FLASH_MSN1 BLOCKS_PER_SECTOR*990
	#define ENDING_BLOCK_EXTERNAL_FLASH_MSN2 BLOCKS_PER_SECTOR*1600
	#define ENDING_BLOCK_EXTERNAL_FLASH_MSN3 BLOCKS_PER_SECTOR*1800
	#define ENDING_BLOCK_EXTERNAL_FLASH_MSN4 BLOCKS_PER_SECTOR*2043

	//MPU definations
	uint8_t SAT_IMU[18];
	extern uint16_t SFM[20];
	extern uint16_t FM[20];
#endif /* INC_VARIABLES_H_ */
