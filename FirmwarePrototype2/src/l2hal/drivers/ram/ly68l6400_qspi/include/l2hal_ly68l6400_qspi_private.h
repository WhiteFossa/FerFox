/*
 * l2hal_ly68l6400_qspi_private.h
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#ifndef L2HAL_DRIVERS_RAM_LY68L6400_QSPI_INCLUDE_L2HAL_LY68L6400_QSPI_PRIVATE_H_
#define L2HAL_DRIVERS_RAM_LY68L6400_QSPI_INCLUDE_L2HAL_LY68L6400_QSPI_PRIVATE_H_

#include <l2hal_ly68l6400_qspi.h>

/**
 * Read/write no more than this amount of bytes per transaction
 */
#define L2HAL_LY68L6400_QSPI_READ_MAX_TRANSACTION_SIZE 64U
#define L2HAL_LY68L6400_QSPI_WRITE_MAX_TRANSACTION_SIZE 64U

/**
 * Chip capacity in bytes
 */
#define L2HAL_LY68L6400_QSPI_CAPACITY 8388608U

/**
 * Chip capacity in terms of address size - 1
 */
#define L2HAL_LY68L6400_QSPI_ADDRESS_SIZE 22 // 23 bits addressing

/**
 * QSPI prescaler
 */
#define L2HAL_LY68L6400_QSPI_PRESCALER 1U

/**
 * Init soft-SPI (classic) mode for chip initialization
 */
void L2HAL_LY68L6400_QSPI_SoftSpi_Init(L2HAL_LY68L6400_QSPI_ContextStruct *context);

/**
 * Select / deselect chip
 */
void L2HAL_LY68L6400_QSPI_SoftSpi_SelectChip(L2HAL_LY68L6400_QSPI_ContextStruct *context, bool isSelected);

/**
 * Set clock line state
 */
void L2HAL_LY68L6400_QSPI_SoftSpi_SetClockState(L2HAL_LY68L6400_QSPI_ContextStruct *context, bool isHigh);

/**
 * Set MOSI line state
 */
void L2HAL_LY68L6400_QSPI_SoftSpi_SetMosiState(L2HAL_LY68L6400_QSPI_ContextStruct *context, bool isHigh);

/**
 * Read MISO line state
 */
GPIO_PinState L2HAL_LY68L6400_QSPI_SoftSpi_ReadMisoState(L2HAL_LY68L6400_QSPI_ContextStruct *context);

/**
 * Sends toSend to device and receives a byte from device. ! DOES NOT MANAGE CS !
 */
uint8_t L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(L2HAL_LY68L6400_QSPI_ContextStruct *context, uint8_t toSend);

/**
 * Init QSPI peripherial
 */
void L2HAL_LY68L6400_QSPI_InitQspi(L2HAL_LY68L6400_QSPI_ContextStruct *context);

/**
 * Bring chip back to SPI mode
 */
void L2HAL_LY68L6400_QSPI_ExitQspiMode(L2HAL_LY68L6400_QSPI_ContextStruct *context);

/**
 * Read up to L2HAL_LY68L6400_QSPI_MAX_READ_BYTES into buffer
 */
void L2HAL_LY68L6400_QSPI_MemoryReadInternal(L2HAL_LY68L6400_QSPI_ContextStruct *context, uint32_t startAddress, uint8_t size, uint8_t* buffer);

/**
 * Write up to L2HAL_LY68L6400_MAX_READ_BYTES from buffer
 */
void L2HAL_LY68L6400_QSPI_MemoryWriteInternal(L2HAL_LY68L6400_QSPI_ContextStruct *context, uint32_t startAddress, uint8_t size, uint8_t* buffer);

#endif /* L2HAL_DRIVERS_RAM_LY68L6400_QSPI_INCLUDE_L2HAL_LY68L6400_QSPI_PRIVATE_H_ */
