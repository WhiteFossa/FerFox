/*
 * global_variables.h
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_

#include <l2hal_systick.h>
#include <l2hal_ly68l6400_qspi.h>
#include <l2hal_crc.h>
#include <l2hal_gc9a01_lfb.h>
#include <ff.h>

/**
 * SysTick driver context.
 */
L2HAL_SysTick_ContextStruct L2HAL_SysTick_Context = { 0 };

/**
 * QSPI bus handle.
 */
QSPI_HandleTypeDef QspiHandle = { 0 };

/**
 * QSPI DMA handle
 */
DMA_HandleTypeDef QspiDmaHandle = { 0 };

/**
 * pSRAM context
 */
L2HAL_LY68L6400_QSPI_ContextStruct RamContext = { 0 };

/**
 * Backlight timer handler
 */
TIM_HandleTypeDef BacklightTimerHandle = { 0 };

/**
 * CRC calculator context
 */
L2HAL_CRCContextStruct CRC_Context;

/**
 * SPI1 bus handle.
 */
SPI_HandleTypeDef Spi1Handle = { 0 };

/**
 * SPI1 TX DMA handle.
 */
DMA_HandleTypeDef Spi1TxDmaHandle = { 0 };

/**
 * SPI1 RX DMA handle.
 */
DMA_HandleTypeDef Spi1RxDmaHandle = { 0 };

/**
 * Display context
 */
L2HAL_GC9A01_LFB_ContextStruct DisplayContext;

/**
 * FMGL context.
 */
FMGL_API_DriverContext FmglContext;

/**
 * SDCARD context
 */
SD_HandleTypeDef SdcardHandle = { 0 };

/**
 * SD card filesystem pointer
 */
FATFS* SdFsPtr = NULL;

#endif /* GLOBAL_VARIABLES_H_ */
