/*
 * l2hal_sdcard.h
 *
 *  Created on: Jul 15, 2023
 *      Author: fossa
 *
 * Inspired by https://github.com/afiskon/stm32-sdcard
 */

#ifndef L2HAL_DRIVERS_SDCARD_INCLUDE_L2HAL_SDCARD_H_
#define L2HAL_DRIVERS_SDCARD_INCLUDE_L2HAL_SDCARD_H_

#include <stdbool.h>
#include <l2hal_mcu.h>

/**
 * Display context, SPI connection and various stuff is stored here
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
}
L2HAL_SDCard_ContextStruct;

/**
 * Initialize SD-card
 */
void L2HAL_SDCard_Init
(
	L2HAL_SDCard_ContextStruct* context,
	SPI_HandleTypeDef *spiHandle,

	GPIO_TypeDef* chipSelectPort,
	uint16_t chipSelectPin
);


#endif /* L2HAL_DRIVERS_SDCARD_INCLUDE_L2HAL_SDCARD_H_ */
