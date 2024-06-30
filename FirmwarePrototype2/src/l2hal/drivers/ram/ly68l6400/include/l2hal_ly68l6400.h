/*
 * l2hal_ly68l6400.h
 *
 *  Created on: Sep 29, 2023
 *      Author: fossa
 */

#ifndef L2HAL_DRIVERS_RAM_LY68L6400_INCLUDE_L2HAL_LY68L6400_H_
#define L2HAL_DRIVERS_RAM_LY68L6400_INCLUDE_L2HAL_LY68L6400_H_

#include <l2hal_mcu.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * SPI-attached pSRAM context, SPI connection, pins etc
 */
typedef struct
{
	/**
	 * SPI bus handle
	 */
	SPI_HandleTypeDef* SPIHandle;

	/**
	 * Chip select pin
	 */
	GPIO_TypeDef* ChipSelectPort;
	uint16_t ChipSelectPin;

	/**
	 * If true, then data transfer in progress and we must wait for next one
	 */
	volatile bool IsDataTransferInProgress;
}
L2HAL_LY68L6400_ContextStruct;

/**
 * Init RAM chip, performs reset and checks if chip on bus (via ReadID), causes
 * L2HAL_Error() if not on bus
 */
void L2HAL_LY68L6400_Init
(
	L2HAL_LY68L6400_ContextStruct* context,
	SPI_HandleTypeDef *spiHandle,

	GPIO_TypeDef* chipSelectPort,
	uint16_t chipSelectPin
);

/**
 * Call it from BOTH SPI DMA TX and SPI DMA RX completion interrupts
 * @param context SD-card context
 */
void L2HAL_LY68L6400_MarkDataTransferAsCompleted(L2HAL_LY68L6400_ContextStruct *context);

/**
 * Read data from memory. Size can be up to chip capacity (i.e. 8MBytes), but internally transfers will be split to 32 bytes transactions to avoid
 * max #CE active time violation
 */
void L2HAL_LY68L6400_MemoryRead(L2HAL_LY68L6400_ContextStruct *context, uint32_t startAddress, uint32_t size, uint8_t* buffer);

/**
 * Write data to memory. Size can be up to chip capacity (i.e. 8MBytes), but internally transfers will be split to 32 bytes transactions to avoid
 * max #CE active time violation
 */
void L2HAL_LY68L6400_MemoryWrite(L2HAL_LY68L6400_ContextStruct *context, uint32_t startAddress, uint32_t size, uint8_t* buffer);

#endif /* L2HAL_DRIVERS_RAM_LY68L6400_INCLUDE_L2HAL_LY68L6400_H_ */
