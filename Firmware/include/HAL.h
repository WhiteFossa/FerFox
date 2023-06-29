/*
 * HAL.h
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#ifndef INCLUDE_HAL_H_
#define INCLUDE_HAL_H_

#include <stm32f4xx_hal.h>
#include <stdbool.h>

/***************
 * PORT C pins *
 ***************/

/**
 * LED pin
 */
#define HAL_LED_PIN GPIO_PIN_13
#define HAL_LED_PORT GPIOC

/**
 * Init project-specific hardware here
 */
void HAL_IntiHardware(void);

/**
 * Switch LED on of off
 */
void HAL_SwitchLed(bool isOn);



#endif /* INCLUDE_HAL_H_ */
