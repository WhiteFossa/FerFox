/*
 * GlobalVariables.h
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#ifndef INCLUDE_GLOBALVARIABLES_H_
#define INCLUDE_GLOBALVARIABLES_H_

#include <l2hal_systick.h>
#include <l2hal_gc9a01.h>
#include <l2hal_sdcard.h>
#include <l2hal_ly68l6400.h>
#include <l2hal_crc.h>
#include <fmgl.h>
#include <ffconf.h>
#include <ff.h>
#include <stddef.h>
#include <pngle.h>

/**
 * Number of drawing cycles before inverting font.
 */
#define FONT_BLINKING_INTERVAL 1U

/**
 * SysTick driver context.
 */
L2HAL_SysTick_ContextStruct L2HAL_SysTick_Context = { 0 };



/**
 * SPI1 bus handle.
 */
SPI_HandleTypeDef SPI1Handle = { 0 };

/**
 * SPI1 TX DMA handle.
 */
DMA_HandleTypeDef SPI1TxDmaHandle = { 0 };

/**
 * SPI1 RX DMA handle.
 */
DMA_HandleTypeDef SPI1RxDmaHandle = { 0 };



/**
 * SPI2 bus handle.
 */
SPI_HandleTypeDef SPI2Handle = { 0 };

/**
 * SPI2 TX DMA handle.
 */
DMA_HandleTypeDef SPI2TxDmaHandle = { 0 };

/**
 * SPI2 RX DMA handle.
 */
DMA_HandleTypeDef SPI2RxDmaHandle = { 0 };



/**
 * Backlight timer handler
 */
TIM_HandleTypeDef BacklightTimerHandle = { 0 };

/**
 * Display context
 */
L2HAL_GC9A01_ContextStruct DisplayContext;

/**
 * FMGL context.
 */
FMGL_API_DriverContext FmglContext;


/**
 * SD-card context
 */
L2HAL_SDCard_ContextStruct SDCardContext;


/**
 * pSRAM context
 */
L2HAL_LY68L6400_ContextStruct RamContext;

/**
 * CRC calculator context
 */
L2HAL_CRCContextStruct CRC_Context;

/**
 * SD card filesystem pointer
 */
FATFS* SDCardFsPtr = NULL;

/**
 * PNGLE library context
 */
pngle_t* PngleContext = NULL;


#endif /* INCLUDE_GLOBALVARIABLES_H_ */
