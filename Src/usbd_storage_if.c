/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_storage_if.c
  * @version        : v1.0_Cube
  * @brief          : Memory management layer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "usbd_storage_if.h"

/* USER CODE BEGIN INCLUDE */
#include <string.h>
#include "fat.h"
#include "cartridge.h"
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @defgroup USBD_STORAGE
  * @brief Usb mass storage device module
  * @{
  */

/** @defgroup USBD_STORAGE_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Defines
  * @brief Private defines.
  * @{
  */

#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_NBR                  0x930
#define STORAGE_BLK_SIZ                  0x200

/* USER CODE BEGIN PRIVATE_DEFINES */
#define FAT_END_BLK 8
#define ROM_START_BLK 41
#define ROM_END_BLK (ROM_START_BLK+(ROM_MAX_SIZE/STORAGE_BLK_SIZ))
#define RAM_START_BLK 2089
#define RAM_END_BLK (RAM_START_BLK+(RAM_SIZE/STORAGE_BLK_SIZ))
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Variables
  * @brief Private variables.
  * @{
  */

/* USER CODE BEGIN INQUIRY_DATA_FS */
/** USB Mass storage Standard Inquiry Data. */
const int8_t STORAGE_Inquirydata_FS[] = {/* 36 */
  
  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,	
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1'                      /* Version      : 4 Bytes */
}; 
/* USER CODE END INQUIRY_DATA_FS */

/* USER CODE BEGIN PRIVATE_VARIABLES */
int flash_unlocked=0;
int rom_erased=0;
int ram_erased=0;
/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t STORAGE_Init_FS(uint8_t lun);
static int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
static int8_t STORAGE_IsReady_FS(uint8_t lun);
static int8_t STORAGE_IsWriteProtected_FS(uint8_t lun);
static int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_GetMaxLun_FS(void);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_StorageTypeDef USBD_Storage_Interface_fops_FS =
{
  STORAGE_Init_FS,
  STORAGE_GetCapacity_FS,
  STORAGE_IsReady_FS,
  STORAGE_IsWriteProtected_FS,
  STORAGE_Read_FS,
  STORAGE_Write_FS,
  STORAGE_GetMaxLun_FS,
  (int8_t *)STORAGE_Inquirydata_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes over USB FS IP
  * @param  lun:
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Init_FS(uint8_t lun)
{
  /* USER CODE BEGIN 2 */
  return (USBD_OK);
  /* USER CODE END 2 */
}

/**
  * @brief  .
  * @param  lun: .
  * @param  block_num: .
  * @param  block_size: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  /* USER CODE BEGIN 3 */
  *block_num  = STORAGE_BLK_NBR;
  *block_size = STORAGE_BLK_SIZ;
  return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsReady_FS(uint8_t lun)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsWriteProtected_FS(uint8_t lun)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  /* USER CODE BEGIN 6 */

	int addr;

	if (blk_addr<FAT_END_BLK){
		memcpy(buf,fat_bin+blk_addr*STORAGE_BLK_SIZ,blk_len*STORAGE_BLK_SIZ);
	}
	else if (blk_addr>=ROM_START_BLK&&blk_addr<ROM_END_BLK){
		addr=blk_addr-ROM_START_BLK;
		memcpy(buf,cartridge.rom+addr*STORAGE_BLK_SIZ,blk_len*STORAGE_BLK_SIZ);
	}
	else if (blk_addr>=RAM_START_BLK&&blk_addr<RAM_END_BLK){
		addr=blk_addr-RAM_START_BLK;
		memcpy(buf, ((uint8_t *)SRAM_SAVE_ADDR)+addr*STORAGE_BLK_SIZ,blk_len*STORAGE_BLK_SIZ);
	}
	else{
		memset(buf,0,blk_len*STORAGE_BLK_SIZ);
	}
  return (USBD_OK);
  /* USER CODE END 6 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  /* USER CODE BEGIN 7 */

	int addr;

	if (blk_addr<FAT_END_BLK){
		memcpy(fat_bin+blk_addr*STORAGE_BLK_SIZ,buf,blk_len*STORAGE_BLK_SIZ);
	}
	else if (blk_addr>=ROM_START_BLK&&blk_addr<ROM_END_BLK){
		addr=blk_addr-ROM_START_BLK;

		LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
			if (!flash_unlocked){
				HAL_FLASH_Unlock();
				flash_unlocked=1;
			}
			if (!rom_erased){
				erase_rom();
				rom_erased=1;
			}

			for (int i = 0; i < blk_len * STORAGE_BLK_SIZ /4; i++) {
				if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, ROM_SAVE_ADDR+addr*STORAGE_BLK_SIZ+i*4,((uint32_t*) buf)[i]) == HAL_OK)
				{
				} else {
					Error_Handler();
				}
			}

			LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
	}
	else if (blk_addr>=RAM_START_BLK&&blk_addr<RAM_END_BLK){
		addr=blk_addr-RAM_START_BLK;

		LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
		if (!flash_unlocked){
			HAL_FLASH_Unlock();
			flash_unlocked=1;
		}
		if (!ram_erased){
			erase_ram();
			ram_erased=1;
		}

		for (int i = 0; i < blk_len * STORAGE_BLK_SIZ /4; i++) {
			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, SRAM_SAVE_ADDR+addr*STORAGE_BLK_SIZ+i*4,((uint32_t*) buf)[i]) == HAL_OK)
			{
			} else {
				Error_Handler();
			}
		}

		LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
	}

  return (USBD_OK);
  /* USER CODE END 7 */
}

/**
  * @brief  .
  * @param  None
  * @retval .
  */
int8_t STORAGE_GetMaxLun_FS(void)
{
  /* USER CODE BEGIN 8 */
  return (STORAGE_LUN_NBR - 1);
  /* USER CODE END 8 */
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
