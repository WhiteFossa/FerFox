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


/**********************
 *  DISPLAY - GC9A01  *
 *
 *  PA5 - SCK (SCL)
 *  PA7 - MOSI (SDA)
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

#define HAL_DISPLAY_BACKLIGHT_PIN GPIO_PIN_3
#define HAL_DISPLAY_BACKLIGHT_PORT GPIOB


/**
 * Init project-specific hardware here
 */
void HAL_IntiHardware(void);

/**
 * Switch LED on of off
 */
void HAL_SwitchLed(bool isOn);



#endif /* INCLUDE_HAL_H_ */
