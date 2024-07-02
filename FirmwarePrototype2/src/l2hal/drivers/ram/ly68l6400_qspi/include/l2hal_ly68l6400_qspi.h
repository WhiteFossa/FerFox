/*
 * l2hal_ly68l6400_qpi.h
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#ifndef L2HAL_DRIVERS_RAM_LY68L6400_QSPI_INCLUDE_L2HAL_LY68L6400_QSPI_H_
#define L2HAL_DRIVERS_RAM_LY68L6400_QSPI_INCLUDE_L2HAL_LY68L6400_QSPI_H_

#include <l2hal_mcu.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * QSPI-attached pSRAM context, QSPI connection, pins etc
 */
typedef struct
{
	/**
	 * QSPIhandle
	 */
	QSPI_HandleTypeDef* QSPIHandle;

	/**
	 * Chip select
	 */
	GPIO_TypeDef* ChipSelectPort;
	uint16_t ChipSelectPin;

	/**
	 * Clock
	 */
	GPIO_TypeDef* ClockPort;
	uint16_t ClockPin;

	/**
	 * MOSI
	 */
	GPIO_TypeDef* MosiPort;
	uint16_t MosiPin;

	/**
	 * MISO
	 */
	GPIO_TypeDef* MisoPort;
	uint16_t MisoPin;
}
L2HAL_LY68L6400_QSPI_ContextStruct;

/**
 * Init RAM chip, performs reset and checks if chip on bus (via ReadID), causes
 * L2HAL_Error() if not on bus
 */
void L2HAL_LY68L6400_QSPI_Init
(
	L2HAL_LY68L6400_QSPI_ContextStruct* context,

	QSPI_HandleTypeDef *qspiHandle,

	GPIO_TypeDef* chipSelectPort,
	uint16_t chipSelectPin,

	GPIO_TypeDef* clockPort,
	uint16_t clockPin,

	GPIO_TypeDef* mosiPort,
	uint16_t mosiPin,

	GPIO_TypeDef* misoPort,
	uint16_t misoPin
);



#endif /* L2HAL_DRIVERS_RAM_LY68L6400_QSPI_INCLUDE_L2HAL_LY68L6400_QSPI_H_ */
