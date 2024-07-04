/*
 * hal.h
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#ifndef INCLUDE_HAL_H_
#define INCLUDE_HAL_H_

#include <l2hal_mcu.h>
#include <stdbool.h>
#include <l2hal.h>

extern TIM_HandleTypeDef BacklightTimerHandle;

/**
 * QSPI
 */

#define HAL_QSPI_PORT1 GPIOB
#define HAL_QSPI_PORT2 GPIOF

/**********************
 *  pSRAM - LY68L6400 *
 *
 *  QSPI
 *  PF5 - #CS (active 0)
 *  PF6 - SIO3
 *  PF7 - SIO2
 *  PF8 - SIO0
 *  PF9 - SIO1
 *  PF10 - CLK
 *
 **********************/

#define HAL_PSRAM_CS_PIN GPIO_PIN_6
#define HAL_PSRAM_CS_PORT GPIOB

#define HAL_PSRAM_SIO0_PIN GPIO_PIN_8
#define HAL_PSRAM_SIO0_PORT GPIOF

#define HAL_PSRAM_SIO1_PIN GPIO_PIN_9
#define HAL_PSRAM_SIO1_PORT GPIOF

#define HAL_PSRAM_SIO2_PIN GPIO_PIN_7
#define HAL_PSRAM_SIO2_PORT GPIOF

#define HAL_PSRAM_SIO3_PIN GPIO_PIN_6
#define HAL_PSRAM_SIO3_PORT GPIOF

#define HAL_PSRAM_CLK_PIN GPIO_PIN_10
#define HAL_PSRAM_CLK_PORT GPIOF

/**********************
 * Display backlight
 **********************/

/**
 * Use this timer for backlight control
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER TIM9

/**
 * Call this for clocking backlight timer in
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER_CLOCK_IN __HAL_RCC_TIM9_CLK_ENABLE

/**
 * Display backlight timer frequency
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER_FREQ 16000000

/**
 * Display backlight timer period. PWM Frequency is HAL_DISPLAY_BACKLIGHT_TIMER_FREQ / HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD,
 * in our case 16000000 / 500 = 32 kHz
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD 500

/**
 * Generage backlight PWM on this channel
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER_CHANNEL TIM_CHANNEL_2

/**
 * Backlight connected to this port (keep synchronized with timer and channel)
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER_PORT GPIOA

/**
 * Backlight connected to this pin (keep synchronized with timer and channel)
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER_PIN GPIO_PIN_3

/**
 * Alternative function for backlight pin  (keep synchronized with timer)
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER_PIN_AF GPIO_AF3_TIM9

/**********************
 * DISPLAY - GC9A01 *
 *
 *  SPI 1
 *  PA1 - RESET (Active 0)
 *  PA2 - D/C (1 - data, 0 - command)
 *  PA4 - CS (Active 0)
 *
 **********************/

#define HAL_DISPLAY_RESET_PIN GPIO_PIN_1
#define HAL_DISPLAY_RESET_PORT GPIOA

#define HAL_DISPLAY_DC_PIN GPIO_PIN_2
#define HAL_DISPLAY_DC_PORT GPIOA

#define HAL_DISPLAY_CS_PIN GPIO_PIN_4
#define HAL_DISPLAY_CS_PORT GPIOA



/**
 * Set backlight level [0-HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD]
 */
void HAL_SetBacklightLevel(uint16_t level);


/**
 * Init project-specific hardware here
 */
void HAL_IntiHardware(void);


#endif /* INCLUDE_HAL_H_ */
