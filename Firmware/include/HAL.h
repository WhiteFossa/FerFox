/*
 * HAL.h
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#ifndef INCLUDE_HAL_H_
#define INCLUDE_HAL_H_

#include <l2hal_mcu.h>
#include <stdbool.h>
#include <l2hal.h>
#include <Interrupts.h>

/***************
 * PORT C pins *
 ***************/

/**
 * LED pin
 */
#define HAL_LED_PIN GPIO_PIN_13
#define HAL_LED_PORT GPIOC


/**
 * Backlight
 */

/**
 * Use this timer for backlight control
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER TIM2

/**
 * Call this for clocking backlight timer in
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER_CLOCK_IN __HAL_RCC_TIM2_CLK_ENABLE

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
#define HAL_DISPLAY_BACKLIGHT_TIMER_PORT GPIOB

/**
 * Backlight connected to this pin (keep synchronized with timer and channel)
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER_PIN GPIO_PIN_3

/**
 * Alternative function for backlight pin  (keep synchronized with timer)
 */
#define HAL_DISPLAY_BACKLIGHT_TIMER_PIN_AF GPIO_AF1_TIM2


/**********************
 * DISPLAY - GC9A01 *
 *
 *  SPI 2:
 *  PB13 - SCK (SCL)
 *  PB15 - MOSI (SDA)
 *
 *  PB0 - RESET (Active 0)
 *  PB1 - D/C (1 - data, 0 - command)
 *  PB2 - CS (Active 0)
 *  PB3 - Backlight (Active 1)
 *
 **********************/

#define HAL_DISPLAY_RESET_PIN GPIO_PIN_0
#define HAL_DISPLAY_RESET_PORT GPIOB

#define HAL_DISPLAY_DC_PIN GPIO_PIN_1
#define HAL_DISPLAY_DC_PORT GPIOB

#define HAL_DISPLAY_CS_PIN GPIO_PIN_2
#define HAL_DISPLAY_CS_PORT GPIOB


/**********************
 *  SD CARD *
 *
 *  SPI 2:
 *  PB13 - SCK (SCL)
 *  PB15 - MOSI (SDA)
 *
 *  PB4 - CS (Active 0)
 *
 **********************/

#define HAL_SDCARD_CS_PIN GPIO_PIN_4
#define HAL_SDCARD_CS_PORT GPIOB

/**
 * Init project-specific hardware here
 */
void HAL_IntiHardware(void);

/**
 * Switch LED on of off
 */
void HAL_SwitchLed(bool isOn);

/**
 * Set backlight level [0-HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD]
 */
void HAL_SetBacklightLevel(uint16_t level);


#endif /* INCLUDE_HAL_H_ */
