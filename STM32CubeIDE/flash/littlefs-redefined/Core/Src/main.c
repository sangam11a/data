/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdarg.h"
#include "lfs_util.h"
#include "lfs.h"
#include "MT25Q.h"
#include "nor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define sector_size 32
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void myprintf(const char *fmt, ...);
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;

SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi4;

UART_HandleTypeDef huart7;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
//uint8_t tx[]={'S','A','N','G','A','M'};
uint8_t hk_counter=0;
uint16_t tim_val = 0;
uint16_t address = 0x00;
uint8_t status_reg=0;
uint8_t READ_FLAG=0;
int tx[70];

uint8_t DEBUG_DATA_RX_FLAG = 0;
// variables used by the filesystem
typedef struct{
	uint32_t secCount;
	uint32_t bootCount;
}app_count_t;
	lfs_file_t File;
		char Text[20];
		app_count_t Counter = {0};
		lfs_t Lfs;
		nor_t Nor;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void read_file_from_littlefs(lfs_t *lfs, const char *filename) {
    lfs_file_t file;
    HAL_UART_Transmit(&huart7, filename,sizeof(filename),1000);
    // Open the file for reading
    int err = lfs_file_open(lfs, &file, filename, LFS_O_RDONLY);
    if (err < 0) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    // Get the file size
    lfs_soff_t file_size = lfs_file_size(lfs, &file);
    if (file_size < 0) {
        printf("Failed to get file size for: %s\n", filename);
        lfs_file_close(lfs, &file);
        return;
    }

    // Allocate a buffer to hold the file data
    float *buffer = malloc(file_size);
    if (buffer == NULL) {
        printf("Failed to allocate buffer for reading file: %s\n", filename);
        lfs_file_close(lfs, &file);
        return;
    }

    // Read the file content into the buffer
    lfs_ssize_t bytes_read = lfs_file_read(lfs, &file, buffer, file_size);
    if (bytes_read < 0) {
        printf("Failed to read file: %s\n", filename);
    } else {
    	char x;
        // Successfully read the file, print its content (if it's text data)
        HAL_UART_Transmit(&huart7, buffer, (int)bytes_read,1000);
        for(int i=0;i<(int) bytes_read;){
//        	printf(buffer[i]);
        	x=buffer[i];
        	i++;
        }


        printf("File Content (%s):\n%.*s\n", filename, (int)bytes_read, buffer);
    }

    // Clean up
    free(buffer);
    lfs_file_close(lfs, &file);
}

volatile uint8_t DmaEnd = 0;

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
	DmaEnd = 1;
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
	DmaEnd = 1;
}

void nor_delay_us(uint32_t us){
//	if (us >= __HAL_TIM_GET_AUTORELOAD(&htim2)){
//		us = __HAL_TIM_GET_AUTORELOAD(&htim2) - 1;
//	}
//	__HAL_TIM_SET_COUNTER(&htim2, 0);
//	HAL_TIM_Base_Start(&htim2);
//	while (__HAL_TIM_GET_COUNTER(&htim2) < us);
//	HAL_TIM_Base_Stop(&htim2);
	HAL_Delay(1000);
}

void nor_cs_assert(){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
}

void nor_cs_deassert(){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
}

void nor_spi_tx(uint8_t *pData, uint32_t Size){
//	HAL_SPI_Transmit(&hspi3, pData, Size, 100);
	DmaEnd = 0;
	HAL_SPI_Transmit(&hspi3, pData, Size, 1000);
//	while (DmaEnd == 0);
}

void nor_spi_rx(uint8_t *pData, uint32_t Size){
//	HAL_SPI_Receive(&hspi3, pData, Size, 100);
	DmaEnd = 0;
	HAL_SPI_Receive(&hspi3, pData, Size, 1000);
//	DmaEnd =0;
//	while (DmaEnd == 0);
}

void __init_nor(){
	Nor.config.CsAssert = nor_cs_assert;
	Nor.config.CsDeassert = nor_cs_deassert;
	Nor.config.DelayUs = nor_delay_us;
	Nor.config.SpiRxFxn = nor_spi_rx;
	Nor.config.SpiTxFxn = nor_spi_tx;

	if (NOR_Init(&Nor) != NOR_OK){ //NOR_Init
		Error_Handler();
	}
}

/** Start LittleFs **/

int _fs_read(const struct lfs_config *c, lfs_block_t block,
            lfs_off_t off, void *buffer, lfs_size_t size){

	if (NOR_ReadSector(&Nor, (uint8_t*)buffer, block, off, size) == NOR_OK){
		return 0;
	}

	return LFS_ERR_IO;
}

int _fs_write(const struct lfs_config *c, lfs_block_t block,
        lfs_off_t off, const void *buffer, lfs_size_t size){

	if (NOR_WriteSector(&Nor, (uint8_t*)buffer, block, off, size) == NOR_OK){
		return 0;
	}

	return LFS_ERR_IO;
}

int _fs_erase(const struct lfs_config *c, lfs_block_t block){
	if (NOR_EraseSector(&Nor, block) == NOR_OK){
		return 0;
	}

	return LFS_ERR_IO;
}

int _fs_sync(const struct lfs_config *c){
	return 0;
}

// Function to list all files and directories in the filesystem
void list_files(lfs_t *lfs) {
    lfs_dir_t dir;
    struct lfs_info info;

    // Open the root directory
    int err = lfs_dir_open(lfs, &dir, "/");
    if (err) {
        printf("Failed to open directory\n");
        return;
    }

    // Loop through all files in the directory
    while (true) {
        err = lfs_dir_read(lfs, &dir, &info);
        if (err < 0) {
            printf("Failed to read directory\n");
            break;
        }

        // If no more files, break
        if (err == 0) {
            break;
        }
        uint8_t dir[100];
        // Print the type and name of the file
        if (info.type == LFS_TYPE_REG) {
            sprintf(dir,"File: %s\n\0", info.name);
            HAL_UART_Transmit(&huart7, dir, strlen(dir),1000);
        } else if (info.type == LFS_TYPE_DIR) {
        	sprintf(dir,"Directory: %s\n\0", info.name);

            HAL_UART_Transmit(&huart7, dir, strlen(dir),1000);
        }
    }

    // Close the directory
    lfs_dir_close(lfs, &dir);
}

void __init_littefs(){
	// because of static qualifier, this variable
	// will have a dedicated address
	static struct lfs_config LfsConfig = {0};
		int Error;

		LfsConfig.read_size = 256;
		LfsConfig.prog_size = 256;
		LfsConfig.block_size = Nor.info.u16SectorSize;
		LfsConfig.block_count =  16384;//Nor.info.u32SectorCount;
		LfsConfig.cache_size = Nor.info.u16PageSize;
		LfsConfig.lookahead_size = 256;//Nor.info.u32SectorCount/8;
		LfsConfig.block_cycles = 15000;

		LfsConfig.read = _fs_read;
		LfsConfig.prog = _fs_write;
		LfsConfig.erase = _fs_erase;
		LfsConfig.sync = _fs_sync;

		Error = lfs_mount(&Lfs, &LfsConfig);
		if (Error != LFS_ERR_OK){
			lfs_format(&Lfs, &LfsConfig);
			Error = lfs_mount(&Lfs, &LfsConfig);
			if (Error != LFS_ERR_OK){
				Error_Handler();
			}
		}

}


#define PATH_MAX_LEN 256

// Recursive function to list files and directories with full paths
void list_files_with_size(lfs_t *lfs, const char *path) {
    lfs_dir_t dir;
    struct lfs_info info;

    // Open the directory at the given path
    int err = lfs_dir_open(lfs, &dir, path);
    if (err) {
        printf("Failed to open directory: %s\n", path);
        return;
    }

    // Loop through all files in the directory
    while (true) {
        err = lfs_dir_read(lfs, &dir, &info);
        if (err < 0) {
            printf("Failed to read directory: %s\n", path);
            break;
        }

        // If no more files, break
        if (err == 0) {
            break;
        }

        // Build the full path for the current file/directory
        char full_path[PATH_MAX_LEN];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, info.name);
        char pa[500];
        // Check if the entry is a file or directory
        if (info.type == LFS_TYPE_REG) {
            sprintf(pa,"File: %s, Size: %ld bytes\n", full_path, info.size);
            HAL_UART_Transmit(&huart7, pa, strlen(pa),1000);
        } else if (info.type == LFS_TYPE_DIR && strcmp(info.name, ".") != 0 && strcmp(info.name, "..") != 0) {
            sprintf(pa,"Directory: %s\n", full_path);
            HAL_UART_Transmit(&huart7, pa, strlen(pa),1000);
            // Recursively list the contents of the directory
            list_files_with_size(lfs, full_path);
        }
    }

    // Close the directory
    lfs_dir_close(lfs, &dir);
}
void __init_storage(){
	__init_nor();
	__init_littefs();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // Check which version of the timer triggered this callback and toggle LED
  if (htim == &htim6 )
  {
//    HAL_UART_Transmit(&huart7, "\nCounter is : ", sizeof("\nCounter is : "), 100);
    tim_val++;
//    char uart_buf[20] ;
//    sprintf(uart_buf, "%u us\0\r\n", tim_val);
//    HAL_UART_Transmit(&huart7, uart_buf, sizeof(uart_buf), 100);

  }
  if(htim == &htim7){
	  hk_counter++;
	  if(hk_counter%30 == 0){ char uart_buf[20] ;
		  sprintf(uart_buf, "%u us\0\r\n", tim_val);

		      HAL_UART_Transmit(&huart7, uart_buf, sizeof(uart_buf), 100);
		  HAL_UART_Transmit(&huart7,"\n-----------------------------Got this triggered-\----------n", sizeof("\n-----------------------------Got this triggered-\----------n"), 100);
		  hk_counter=0;
		  tim_val = 0 ;
	  }

  }
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	  char uart_buf[50];
	  int uart_buf_len;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI3_Init();
  MX_UART7_Init();
  MX_USB_DEVICE_Init();
  MX_SPI4_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_DMA_Init();
  MX_TIM6_Init();
  MX_ADC3_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);

  HAL_Delay(500);

 HAL_UART_Transmit(&huart7,"********************S2S OBC is starting ************\n", sizeof("********************S2S OBC is starting ************\n"),1000);

 __init_storage();
 list_files(&Lfs);
//  char path[200];
// char txt[]="sangam is writing it manually";
//
//	__init_littefs();
 list_files_with_size(&Lfs, "/");
// 		  lfs_file_open(&Lfs, &File, "flags.txt", LFS_O_RDWR  | LFS_O_CREAT  |LFS_O_APPEND);// |LFS_O_APPEND
// 		  lfs_file_write(&Lfs, &File, &txt, sizeof(txt));
// 		  lfs_file_close(&Lfs, &File);
// read_file_from_littlefs(&Lfs, "satHealth.txt");
////  read_file_from_littlefs(&Lfs, "sat_health.txt");
// read_file_from_littlefs(&Lfs, "flags.txt");

 list_files_with_size(&Lfs, "/");
 uint8_t count=0;uint16_t timer_val;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
