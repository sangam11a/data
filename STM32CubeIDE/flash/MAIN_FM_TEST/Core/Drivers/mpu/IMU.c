///*
// * IMU.c
// *
// *  Created on: Sep 8, 2023
// *      Author: User
// */
//#include "IMU.h"
//
////#include "MT2"
////#include "mem_addr.h"
////#include "USER_FUNCTIONS.h"
//
///*
// * Definitioon of structure of MPU6500_t
// */
//MPU6500_t MPU6500;
//
//uint32_t Read_buffer[10];
//
////Magnetometer Functions
//typedef struct LIS3MDL {
//
//	struct Mag {
//		uint16_t mx, my, mz;
//	} mag;
//
//} lis3mdl;
//
//
//
//const uint8_t READWRITE_CMD = 0x80;
//
//// MPU6500 registers
//const uint8_t ACCEL_OUT = 0x3B;
//const uint8_t GYRO_OUT = 0x43;
//const uint8_t TEMP_OUT = 0x41;
//
//const uint8_t EXT_SENS_DATA_00 = 0x49;
//
//const uint8_t GYRO_CONFIG = 0x1B;
//const uint8_t ACCEL_CONFIG = 0x1C;
//const uint8_t ACCEL_CONFIG2 = 0x1D;
//
//const uint8_t ACCEL_FS_SEL_2G = 0x00;
//const uint8_t ACCEL_FS_SEL_4G = 0x08;
//const uint8_t ACCEL_FS_SEL_8G = 0x10;
//const uint8_t ACCEL_FS_SEL_16G = 0x18;
//
//const uint8_t GYRO_FS_SEL_250DPS = 0x00;
//const uint8_t GYRO_FS_SEL_500DPS = 0x08;
//const uint8_t GYRO_FS_SEL_1000DPS = 0x10;
//const uint8_t GYRO_FS_SEL_2000DPS = 0x18;
//
//const uint8_t CONFIG = 0x1A;
//
//#define WHO_AM_I_6500_ANS 0x70
//#define WHO_AM_I          0x75
//#define USER_CTRL         0x6A
//#define PWR_MGMT_1        0x6B
//
//#define READWRITE         0x80
//#define SPI_TIMOUT_MS     1000
//
//static uint8_t _buffer[14];
//uint8_t _buffer1;
//uint8_t _buffer2;
//
///**
// * @brief  Read data from Specific Register address of LIS3MDL
// * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
// *               the configuration information for SPI module.
// * @param  add Register address from which data is to be read
// */
//uint8_t LIS3MDL_ReadReg(SPI_HandleTypeDef *hspi, uint8_t add) {
//	uint8_t val;
//	add |= 0x80;  // set the MSB to indicate a read operation
//	HAL_GPIO_WritePin(MAG_CS_GPIO_PORT, MAG_CS_GPIO_PIN, GPIO_PIN_RESET);
//	HAL_SPI_Transmit(hspi, &add, 1, 100);
//	HAL_SPI_Receive(hspi, &val, 1, 100);
//	HAL_GPIO_WritePin(MAG_CS_GPIO_PORT, MAG_CS_GPIO_PIN, GPIO_PIN_SET);
//	return val;
//}
//
///**
// * @brief  Write on Specific Register address of LIS3MDL
// * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
// *               the configuration information for SPI module.
// * @param  add Register address where certain value is to be written
// */
//void LIS3MDL_WriteReg(SPI_HandleTypeDef *hspi, uint8_t add, uint8_t val) {
//	add &= 0x7F;  // clear the MSB to indicate a write operation
//	HAL_GPIO_WritePin(MAG_CS_GPIO_PORT, MAG_CS_GPIO_PIN, GPIO_PIN_RESET);
//	HAL_SPI_Transmit(hspi, &add, 1, 100);
//	HAL_SPI_Transmit(hspi, &val, 1, 100);
//	HAL_GPIO_WritePin(MAG_CS_GPIO_PORT, MAG_CS_GPIO_PIN, GPIO_PIN_SET);
//
//}
//
///**
// * @brief  Initialize LIS3MDL to work in 16-bit, 1.25Hz ODR, ±4 Gauss and Continuous conversion Mode
// * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
// *               the configuration information for SPI module.
// * @param  ctrl2 Control Register Value to choose LIS3MDL sensor Scale
// */
//void LIS3MDL_Init(SPI_HandleTypeDef *hspi, uint8_t ctrl2) {
//	uint8_t ctrl1 = 0x74; // set the magnetic resolution to 16-bit, 20 Hz ODR, UHP mode in X-Y axis
//	LIS3MDL_WriteReg(hspi, LIS3MDL_CTRL_REG1, ctrl1);
//
//	/* Change the full-scale range to ±4 Gauss */
//
//	//value to set the full-scale range
//	LIS3MDL_WriteReg(hspi, LIS3MDL_CTRL_REG2, ctrl2);
//
//	/* Change the control register 3 to continuous conversion mode */
//
//	uint8_t ctrl3 = 0x00; // value to set the continuous conversion mode
//	LIS3MDL_WriteReg(hspi, LIS3MDL_CTRL_REG3, ctrl3);
//
//	uint8_t ctrl4 = 0x0C; // value to set the UHP mode on Z-axis
//	LIS3MDL_WriteReg(hspi, LIS3MDL_CTRL_REG4, ctrl4);
//}
//
////MPU6500 Functions
//
//uint8_t MPU_begin(SPI_HandleTypeDef *SPIx, MPU6500_t *pMPU6500) {
//	// Initialize variables
//	uint8_t addr, val;
////	 Confirm device
////	osDelay(100);
//	whoAmI();
//	readRegisters(WHO_AM_I, 1, &check);
//	if (check == WHO_AM_I_6500_ANS) {
////	 Startup / reset the sensor
//		addr = PWR_MGMT_1;
//		val = 0x00;
//		writeRegister(addr, val);
//
//		// Disable I2C (SPI only)
//		addr = USER_CTRL;
//		val = 0x10;
//		writeRegister(addr, val);
//
//		// Configure DLPF value()
//		val = 0x11;
//		MPU6500_SetDLPFBandwidth(DLPF_BANDWIDTH_20HZ);
//
//		// Set the full scale ranges
//		MPU_writeAccFullScaleRange(pMPU6500,
//				pMPU6500->settings.aFullScaleRange);
//		MPU_writeGyroFullScaleRange(pMPU6500,
//				pMPU6500->settings.gFullScaleRange);
//		return 1;
//	} else {
//		return 0;
//	}
//}
//
//void MPU_CS(uint8_t state) {
//	HAL_GPIO_WritePin(IMU_CS_GPIO_PORT, IMU_CS_GPIO_PIN, state);
//}
//
//uint8_t SPIx_WriteRead(uint8_t Byte) {
//	uint8_t receivedbyte = 0;
//	if (HAL_SPI_TransmitReceive(&IMU_STREAM, (uint8_t*) &Byte,
//			(uint8_t*) &receivedbyte, 1, 0x1000) != HAL_OK) {
//		return -1;
//	} else {
//	}
//	return receivedbyte;
//}
//
//void MPU_SPI_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite) {
//	MPU_CS(CS_SEL);
//	SPIx_WriteRead(WriteAddr);
//	while (NumByteToWrite >= 0x01) {
//		SPIx_WriteRead(*pBuffer);
//		NumByteToWrite--;
//		pBuffer++;
//	}
//	MPU_CS(CS_DES);
//}
//
//void MPU_SPI_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead) {
//	MPU_CS(CS_SEL);
//	uint8_t data = ReadAddr | READWRITE_CMD;
//	HAL_SPI_Transmit(&IMU_STREAM, &data, 1, 100);
//	HAL_SPI_Receive(&IMU_STREAM, pBuffer, NumByteToRead, 100);
//	MPU_CS(CS_DES);
//}
//
///* writes a byte to MPU6500 register given a register address and data */
//void writeRegister(uint8_t subAddress, uint8_t data) {
//	MPU_SPI_Write(&data, subAddress, 1);
////	osDelay(10);
//	HAL_Delay(10)
//;}
//
///* reads registers from MPU6500 given a starting register address, number of bytes, and a pointer to store data */
//void readRegisters(uint8_t subAddress, uint8_t count, uint8_t *dest) {
//	MPU_SPI_Read(dest, subAddress, count);
//}
//
///* gets the MPU6500 WHO_AM_I register value, expected to be 0x71 */
//uint8_t whoAmI() {
//	// read the WHO AM I register
//	readRegisters(WHO_AM_I, 1, &_buffer1);
//
//	// return the register value
//	return _buffer1;
//}
//
///* sets the DLPF bandwidth to values other than default */
//void MPU6500_SetDLPFBandwidth(DLPFBandwidth bandwidth) {
//	writeRegister(ACCEL_CONFIG2, bandwidth);
//	writeRegister(CONFIG, bandwidth);
//}
//
///// @brief Set the accelerometer full scale range
///// @param SPIx Pointer to SPI structure config
///// @param pMPU6500 Pointer to master MPU6500 struct
///// @param aScale Set 0 for ±2g, 1 for ±4g, 2 for ±8g, and 3 for ±16g
//void MPU_writeAccFullScaleRange(MPU6500_t *pMPU6500, uint8_t aScale) {
//	// Variable init
//	uint8_t addr = ACCEL_CONFIG;
//	uint8_t val;
//
//	// Set the value
//	switch (aScale) {
//	case AFSR_2G:
//		pMPU6500->sensorData.aScaleFactor = 16384.0;
//		val = 0x00;
//		writeRegister(addr, val);
//		break;
//	case AFSR_4G:
//		pMPU6500->sensorData.aScaleFactor = 8192.0;
//		val = 0x08;
//		writeRegister(addr, val);
//		break;
//	case AFSR_8G:
//		pMPU6500->sensorData.aScaleFactor = 4096.0;
//		val = 0x10;
//		writeRegister(addr, val);
//		break;
//	case AFSR_16G:
//		pMPU6500->sensorData.aScaleFactor = 2048.0;
//		val = 0x18;
//		writeRegister(addr, val);
//		break;
//	default:
//		pMPU6500->sensorData.aScaleFactor = 8192.0;
//		val = 0x08;
//		writeRegister(addr, val);
//		break;
//	}
//}
//
///// @brief Set the gyroscope full scale range
///// @param SPIx Pointer to SPI structure config
///// @param pMPU6500 Pointer to master MPU6500 struct
///// @param gScale Set 0 for ±250°/s, 1 for ±500°/s, 2 for ±1000°/s, and 3 for ±2000°/s
//void MPU_writeGyroFullScaleRange(MPU6500_t *pMPU6500, uint8_t gScale) {
//	// Variable init
//	uint8_t addr = GYRO_CONFIG;
//	uint8_t val;
//
//	// Set the value
//	switch (gScale) {
//	case GFSR_250DPS:
//		pMPU6500->sensorData.gScaleFactor = 131.0;
//		val = 0x00;
//		writeRegister(addr, val);
//		break;
//	case GFSR_500DPS:
//		pMPU6500->sensorData.gScaleFactor = 65.5;
//		val = 0x08;
//		writeRegister(addr, val);
//		break;
//	case GFSR_1000DPS:
//		pMPU6500->sensorData.gScaleFactor = 32.8;
//		val = 0x10;
//		writeRegister(addr, val);
//		break;
//	case GFSR_2000DPS:
//		pMPU6500->sensorData.gScaleFactor = 16.4;
//		val = 0x18;
//		writeRegister(addr, val);
//		break;
//	default:
//		pMPU6500->sensorData.gScaleFactor = 65.5;
//		val = 0x08;
//		writeRegister(addr, val);
//		break;
//	}
//}
//
//uint8_t MPU6500_ReadReg(SPI_HandleTypeDef *hspi, uint8_t add) {
//	uint8_t val;
//	add |= 0x80;  // set the MSB to indicate a read operation
//	MPU_CS(CS_SEL);
//	HAL_SPI_Transmit(hspi, &add, 1, 100);
//	HAL_SPI_Receive(hspi, &val, 1, 100);
//	MPU_CS(CS_DES);
//	return val;
//}
//
///* read the data, each argument should point to a array for x, y, and x */
//void MPU6500_GetData(MPU6500_t *pMPU6500) {
//	// grab the data from the MPU6500
//	readRegisters(ACCEL_OUT, 14, _buffer);
//
//	// combine into 16 bit values
//	pMPU6500->rawData.ax = (((int16_t) _buffer[0]) << 8) | _buffer[1];
//	pMPU6500->rawData.ay = (((int16_t) _buffer[2]) << 8) | _buffer[3];
//	pMPU6500->rawData.az = (((int16_t) _buffer[4]) << 8) | _buffer[5];
//
//	pMPU6500->rawData.gx = (((int16_t) _buffer[8]) << 8) | _buffer[9];
//	pMPU6500->rawData.gy = (((int16_t) _buffer[10]) << 8) | _buffer[11];
//	pMPU6500->rawData.gz = (((int16_t) _buffer[12]) << 8) | _buffer[13];
//}
//
///// @brief Find offsets for each axis of gyroscope
///// @param SPIx Pointer to SPI structure config
///// @param pMPU6500 Pointer to master MPU6500 struct
///// @param numCalPoints Number of data points to average
//void MPU_calibrateGyro(MPU6500_t *pMPU6500, uint16_t numCalPoints) {
//	// Init
//	int32_t x = 0;
//	int32_t y = 0;
//	int32_t z = 0;
//
//	// Zero guard
//	if (numCalPoints == 0) {
//		numCalPoints = 1;
//	}
//
//	// Save specified number of points
//	for (uint16_t ii = 0; ii < numCalPoints; ii++) {
//		MPU6500_GetData(pMPU6500);
//
//		x += pMPU6500->rawData.gx;
//		y += pMPU6500->rawData.gy;
//		z += pMPU6500->rawData.gz;
////		osDelay(3);
//		HAL_Delay(3);
//	}
//
//	// Average the saved data points to find the gyroscope offset
//	pMPU6500->gyroCal.x = (float) x / (float) numCalPoints;
//	pMPU6500->gyroCal.y = (float) y / (float) numCalPoints;
//	pMPU6500->gyroCal.z = (float) z / (float) numCalPoints;
//}
//
///// @brief Calculate the real world sensor values
///// @param SPIx Pointer to SPI structure config
///// @param pMPU6500 Pointer to master MPU6500 struct
//void MPU_readProcessedData(MPU6500_t *pMPU6500) {
//	// Get raw values from the IMU
//	MPU6500_GetData(pMPU6500);
//
//	// Convert accelerometer values to g's
//	pMPU6500->sensorData.ax = pMPU6500->rawData.ax
//			/ pMPU6500->sensorData.aScaleFactor;
//	pMPU6500->sensorData.ay = pMPU6500->rawData.ay
//			/ pMPU6500->sensorData.aScaleFactor;
//	pMPU6500->sensorData.az = pMPU6500->rawData.az
//			/ pMPU6500->sensorData.aScaleFactor;
//
//	// Compensate for gyro offset
//	pMPU6500->sensorData.gx = pMPU6500->rawData.gx - pMPU6500->gyroCal.x;
//	pMPU6500->sensorData.gy = pMPU6500->rawData.gy - pMPU6500->gyroCal.y;
//	pMPU6500->sensorData.gz = pMPU6500->rawData.gz - pMPU6500->gyroCal.z;
//
//	// Convert gyro values to deg/s
//	pMPU6500->sensorData.gx /= pMPU6500->sensorData.gScaleFactor;
//	pMPU6500->sensorData.gy /= pMPU6500->sensorData.gScaleFactor;
//	pMPU6500->sensorData.gz /= pMPU6500->sensorData.gScaleFactor;
//}
//
///// @brief Calculate the attitude of the sensor in degrees using a complementary filter
///// @param SPIx Pointer to SPI structure config
///// @param pMPU6500 Pointer to master MPU6500 struct
//void MPU_calcAttitude(MPU6500_t *pMPU6500) {
//	// Read processed data
//	MPU_readProcessedData(pMPU6500);
//
//	// Complementary filter
//	accelPitch = atan2(pMPU6500->sensorData.ay,
//			pMPU6500->sensorData.az) * RAD2DEG;
//	accelRoll = atan2(pMPU6500->sensorData.ax,
//			pMPU6500->sensorData.az) * RAD2DEG;
//
//	pMPU6500->attitude.r = pMPU6500->attitude.tau
//			* (pMPU6500->attitude.r
//					+ pMPU6500->sensorData.gy * pMPU6500->attitude.dt)
//			+ (1 - pMPU6500->attitude.tau) * accelRoll;
//	pMPU6500->attitude.p = pMPU6500->attitude.tau
//			* (pMPU6500->attitude.p
//					- pMPU6500->sensorData.gx * pMPU6500->attitude.dt)
//			+ (1 - pMPU6500->attitude.tau) * accelPitch;
////	pMPU6500->attitude.y += (pMPU6500->sensorData.gz * pMPU6500->attitude.dt);
//
//	float magx = LIS3MDL_ReadData(&IMU_STREAM, LIS3MDL_OUTX_L);
//	float magy = LIS3MDL_ReadData(&IMU_STREAM, LIS3MDL_OUTY_L);
//	float magz = LIS3MDL_ReadData(&IMU_STREAM, LIS3MDL_OUTZ_L);
//
//	float rollRad = pMPU6500->attitude.r / 180 * 3.14159265359;
//	float pitchRad = pMPU6500->attitude.p / 180 * 3.14159265359;
//
//	float Xm = magx * cos(pitchRad) - magy * sin(rollRad) * sin(pitchRad)
//			+ magz * cos(rollRad) * sin(pitchRad);
//
//	float Ym = magy * cos(rollRad) + magz * sin(rollRad);
//
//	pMPU6500->attitude.y = atan2(Ym, Xm) * RAD2DEG;
//
//}
//
//void IMU_Setup() {
//
////	LIS3MDL_Init(&IMU_STREAM, 0x60); // ±16 Gauss full scale, 20Hz ODR, Continuous conversion mode
//	HAL_Delay(100);
//	uint8_t serialBuf[20];
//	if (MPU_begin(&IMU_STREAM, &MPU6500) != true) {
//		sprintf((char*) serialBuf, "ERROR!\r\n");
//		HAL_UART_Transmit(&DEBUG_STREAM, serialBuf, strlen((char*) serialBuf),
//				100);
//	} else {
////		myprintf("MPU6500 Initialization Complete");
//		//	 Calibrate the IMU
////		myprintf("Calibrating sensors.\r\n");
//		MPU_calibrateGyro(&MPU6500, 1000);
//		HAL_Delay(100);
////		myprintf("Calibration  Complete");
//	}
//
//}
//
//void IMU_Data() {
//
//	//Gyro, Accel and Mag register data
//
//	SAT_IMU[0] = MPU6500_ReadReg(&IMU_STREAM, ACCEL_XOUT_H);
//	SAT_IMU[1] = MPU6500_ReadReg(&IMU_STREAM, ACCEL_XOUT_L);
//	SAT_IMU[2] = MPU6500_ReadReg(&IMU_STREAM, ACCEL_YOUT_H);
//	SAT_IMU[3] = MPU6500_ReadReg(&IMU_STREAM, ACCEL_YOUT_L);
//	SAT_IMU[4] = MPU6500_ReadReg(&IMU_STREAM, ACCEL_ZOUT_H);
//	SAT_IMU[5] = MPU6500_ReadReg(&IMU_STREAM, ACCEL_ZOUT_L);
//
//	SAT_IMU[6] = MPU6500_ReadReg(&IMU_STREAM, GYRO_XOUT_H);
//	SAT_IMU[7] = MPU6500_ReadReg(&IMU_STREAM, GYRO_XOUT_L);
//	SAT_IMU[8] = MPU6500_ReadReg(&IMU_STREAM, GYRO_YOUT_H);
//	SAT_IMU[9] = MPU6500_ReadReg(&IMU_STREAM, GYRO_YOUT_L);
//	SAT_IMU[10] = MPU6500_ReadReg(&IMU_STREAM, GYRO_ZOUT_H);
//	SAT_IMU[11] = MPU6500_ReadReg(&IMU_STREAM, GYRO_ZOUT_L);
//
//	SAT_IMU[13] = LIS3MDL_ReadReg(&IMU_STREAM, LIS3MDL_OUTX_L);
//	SAT_IMU[12] = LIS3MDL_ReadReg(&IMU_STREAM, LIS3MDL_OUTX_H);
//	SAT_IMU[14] = LIS3MDL_ReadReg(&IMU_STREAM, LIS3MDL_OUTY_L);
//	SAT_IMU[15] = LIS3MDL_ReadReg(&IMU_STREAM, LIS3MDL_OUTY_H);
//	SAT_IMU[16] = LIS3MDL_ReadReg(&IMU_STREAM, LIS3MDL_OUTZ_L);
//	SAT_IMU[17] = LIS3MDL_ReadReg(&IMU_STREAM, LIS3MDL_OUTZ_H);
//	Sector_Erase_4B(&MFM_SPI_HANDLETYPEDEF, BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA, 32);
//	uint8_t row,temp_i=0 ;
//	uint16_t data23;
//	for( row = 0; row <18; row+=1){
//		data23 =((uint16_t)SAT_IMU[row]<<8 | (uint16_t)SAT_IMU[row+1]);
//
//		SFM[temp_i] = data23;
////			SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA + temp_i,4, &data23);
//		Byte_Write_4B(&MFM_SPI_HANDLETYPEDEF, BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA+temp_i, SAT_IMU[row]);
//		temp_i++;
////			row++;
//			HAL_Delay(100);
//	}
//		SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA + temp_i,4, 0x32);
//		temp_i++;
//		SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA + temp_i,4, 0x32);
//		temp_i++;
//		SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA + temp_i,4, 0x32);
//		temp_i++;
//		SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA + temp_i,4, 0x32);
//	uint32_t Rx_data;
//	row = 0 ;
//	do{
//		FM[row] = Read_Byte_4B(&MFM_SPI_HANDLETYPEDEF, BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA+row);
//		row++;
//		if(FM[row] == 0x32){
//			row = 0;
//			break;
//		}
//	}while(row>0 & row<20);
//	get_current_address(&MFM_SPI_HANDLETYPEDEF, 0);
//}
//
//
///*
// *
// */
//void HK_IMU() {
//	IMU_Setup();
//	IMU_Data();
////	SAVE_HK_DATA();
////	READ_FM_DATA(&MFM_SPI_HANDLETYPEDEF, STARTING_BLOCK_EXTERNAL_FLASH_HK_DATA, Read_buffer,4);
//
//}
///*
// *
// */
//
//void SAVE_HK_DATA(){
//	uint32_t temp_internal_memory;
//	get_current_address(&MFM_SPI_HANDLETYPEDEF, 0);
//	READ_FRM_INTERNAL_FLASH(BLOCK_ADDRESS_INTERNAL_FLASH_HK_DATA, &temp_internal_memory, 1);
//	for(int8_t row = 0; row <18; row+=2){
//		SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, temp_internal_memory,4, (uint16_t)(SAT_IMU[row]<<8 | SAT_IMU[row+1]));
//	}
//	SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, temp_internal_memory,4, 0x32);
//	SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, temp_internal_memory,4, 0x32);
//	SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, temp_internal_memory,4, 0x32);
//	SAVE_DATA(&MFM_SPI_HANDLETYPEDEF, temp_internal_memory,4, 0x32);
//	for(int8_t row = 0 ; row < 18;row+=1){
////		 SFM[i] = Read_Byte_4B(&hspi4, temp_internal_memory+i);
////		 HAL_Delay(200);
//		  FM[row] = Read_Byte_4B(&hspi3, temp_internal_memory+row);
//	}
//}
///*
// *
// */
//void SAVE_DATA(SPI_HandleTypeDef *SPI, uint32_t address, uint8_t sector_size, uint16_t *data){
////	Sector_Erase_4B(SPI, address, sector_size);
////	HAL_UART_Transmit()
//	Byte_Write_4B(SPI, address, data);
//
//}
//
//
//
