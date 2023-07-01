/*
 * l2hal_stm32f401ccu6.h
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#ifndef L2HAL_MCU_DEPENDENT_MCUS_STM32F401CCU6_L2HAL_STM32F401CCU6_H_
#define L2HAL_MCU_DEPENDENT_MCUS_STM32F401CCU6_L2HAL_STM32F401CCU6_H_


#include <stm32f4xx_hal.h>
#include <l2hal_errors.h>
#include <mcus/stm32f401ccu6/drivers/input/buttons/include/l2hal_stm32f401ccu6_buttons.h>

/**
 * Maximal ports count for given device.
 */
#define L2HAL_MAX_PORTS_COUNT 6

#pragma GCC diagnostic ignored "-Wunused-variable"
/**
 * Indexes to ports, i.e. 0 -> GPIOA, 1 -> GPIOB etc.
 */
static const GPIO_TypeDef* L2HAL_IndexesToPorts[L2HAL_MAX_PORTS_COUNT] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH };

/**
 * Enable clock for given port
 * @param port Enable clock for given port
 */
void L2HAL_MCU_ClockPortIn(GPIO_TypeDef* port);


#endif /* L2HAL_MCU_DEPENDENT_MCUS_STM32F401CCU6_L2HAL_STM32F401CCU6_H_ */
