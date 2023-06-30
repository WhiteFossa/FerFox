/*
 * l2hal_gc9a01.h
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#ifndef L2HAL_DRIVERS_DISPLAY_GC9A01_INCLUDE_L2HAL_GC9A01_H_
#define L2HAL_DRIVERS_DISPLAY_GC9A01_INCLUDE_L2HAL_GC9A01_H_


#include <stm32f4xx_hal.h>
#include <stdbool.h>
#include <fmgl.h>

enum L2HAL_GC9A01_Orientation
{
	ROTATION_0,
	ROTATION_90,
	ROTATION_180,
	ROTATION_270
};


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
	 * Reset pin
	 */
	GPIO_TypeDef* ResetPort;
	uint16_t ResetPin;

	/**
	 * Data / command pin
	 */
	GPIO_TypeDef* DataCommandPort;
	uint16_t DataCommandPin;

	/**
	 * Chip select pin
	 */
	GPIO_TypeDef* ChipSelectPort;
	uint16_t ChipSelectPin;

	/**
	 * Backlight pin
	 */
	GPIO_TypeDef* BacklightPort;
	uint16_t BacklightPin;

	/* Current drawing color */
	FMGL_API_ColorStruct ActiveColor;
}
L2HAL_GC9A01_ContextStruct;


/**
 * Initialize GC9A01-based display
 */
L2HAL_GC9A01_ContextStruct L2HAL_GC9A01_Init
(
	SPI_HandleTypeDef *spiHandle,

	GPIO_TypeDef* resetPort,
	uint16_t resetPin,

	GPIO_TypeDef* dataCommandPort,
	uint16_t dataCommandPin,

	GPIO_TypeDef* chipSelectPort,
	uint16_t chipSelectPin,

	GPIO_TypeDef* backlightPort,
	uint16_t backlightPin,

	enum L2HAL_GC9A01_Orientation orientation
);


/**
 * Switch backlight On or Off
 */
void L2HAL_GC9A01_SwitchBacklight(L2HAL_GC9A01_ContextStruct *context, bool isOn);

/**
 * Set columns range for subsequent memory writes
 */
void L2HAL_GC9A01_SetColumnsRange(L2HAL_GC9A01_ContextStruct *context, uint16_t colStart, uint16_t colEnd);

/**
 * Set rows range for subsequent memory writes
 */
void L2HAL_GC9A01_SetRowsRange(L2HAL_GC9A01_ContextStruct *context, uint16_t rowStart, uint16_t rowEnd);

/**
 * Get display width
 */
uint16_t L2HAL_GC9A01_GetWidth(void);

/**
 * Get display height
 */
uint16_t L2HAL_GC9A01_GetHeight(void);

/**
 * Fill display with active color
 */
void L2HAL_GC9A01_ClearDisplay(L2HAL_GC9A01_ContextStruct *context);

/**
 * Draw pixel
 */
void L2HAL_GC9A01_DrawPixel(L2HAL_GC9A01_ContextStruct* context, uint16_t x, uint16_t y);

/**
 * Get pixel color
 */
FMGL_API_ColorStruct L2HAL_GC9A01_GetPixel(L2HAL_GC9A01_ContextStruct* context, uint16_t x, uint16_t y);

/**
 * Set color what will be used for drawing.
 */
void L2HAL_GC9A01_SetActiveColor(L2HAL_GC9A01_ContextStruct* context, FMGL_API_ColorStruct color);

/**
 * Push framebuffer to display
 */
void L2HAL_GC9A01_PushFramebuffer(L2HAL_GC9A01_ContextStruct* context);

#endif /* L2HAL_DRIVERS_DISPLAY_GC9A01_INCLUDE_L2HAL_GC9A01_H_ */
