/*
 * l2hal_ly68l6400_private.h
 *
 *  Created on: Sep 29, 2023
 *      Author: fossa
 */

#ifndef L2HAL_DRIVERS_RAM_LY68L6400_INCLUDE_L2HAL_LY68L6400_PRIVATE_H_
#define L2HAL_DRIVERS_RAM_LY68L6400_INCLUDE_L2HAL_LY68L6400_PRIVATE_H_

#include <l2hal_ly68l6400.h>

/**
 * Read no more than this amount of bytes per attempt
 */
#define L2HAL_LY68L6400_MAX_READ_BYTES 32U

/**
 * Chip capacity in bytes
 */
#define L2HAL_LY68L6400_CAPACITY 8388608U

/**
 * Select / deselect chip
 */
void L2HAL_LY68L6400_SelectChip(L2HAL_LY68L6400_ContextStruct *context, bool isSelected);

/**
 * Writes data into chip (NOT INTO CHIP'S MEMORY)
 */
void L2HAL_LY68L6400_WriteData(L2HAL_LY68L6400_ContextStruct *context, uint8_t* data, uint16_t dataSize);

/**
 * Reads data from chip (NOT FROM CHIP'S MEMORY)
 */
void L2HAL_LY68L6400_ReadData(L2HAL_LY68L6400_ContextStruct *context, uint8_t* dataBuffer, uint16_t readSize);

/**
 * Hang till the DMA transfer completed
 */
void L2HAL_LY68L6400_WaitForDataTransferCompletion(L2HAL_LY68L6400_ContextStruct *context);

/**
 * Read up to L2HAL_LY68L6400_MAX_READ_BYTES into buffer
 */
void L2HAL_LY68L6400_MemoryReadInternal(L2HAL_LY68L6400_ContextStruct *context, uint32_t startAddress, uint8_t size, uint8_t* buffer);

/**
 * Write up to L2HAL_LY68L6400_MAX_READ_BYTES from buffer
 */
void L2HAL_LY68L6400_MemoryWriteInternal(L2HAL_LY68L6400_ContextStruct *context, uint32_t startAddress, uint8_t size, uint8_t* buffer);

#endif /* L2HAL_DRIVERS_RAM_LY68L6400_INCLUDE_L2HAL_LY68L6400_PRIVATE_H_ */
