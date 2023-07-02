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
#include <fmgl.h>

/**
 * Number of drawing cycles before inverting font.
 */
#define FONT_BLINKING_INTERVAL 1U

/**
 * Sprite movement speed.
 */
#define SPRITE_SPEED_X 15
#define SPRITE_SPEED_Y 20

/**
 * SysTick driver context.
 */
L2HAL_SysTick_ContextStruct L2HAL_SysTick_Context = { 0 };

/**
 * SPI1 bus handle.
 */
SPI_HandleTypeDef SPI1Handle = { 0 };

/**
 * SPI1 DMA handle.
 */
DMA_HandleTypeDef SPI1DmaHandle = { 0 };

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
FMGL_API_DriverContext fmglContext;

/**
 * Normal font (white on black).
 */
FMGL_API_FontSettings normalFont;


/**
 * Inverted font (black on white).
 */
FMGL_API_FontSettings invertedFont;

/**
 * Current font (for text blinking).
 */
FMGL_API_FontSettings* currentFont;

/**
 * Sprite to draw.
 */
FMGL_API_XBMImage sprite;

/**
 * Draws background text with given font.
 * @param fontSettings Pointer to font settings.
 */
void DrawBackgroundText(FMGL_API_FontSettings* fontSettings);


#endif /* INCLUDE_GLOBALVARIABLES_H_ */
