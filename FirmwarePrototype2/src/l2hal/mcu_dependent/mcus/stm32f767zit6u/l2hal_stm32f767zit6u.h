/*
 * l2hal_stm32f767zit6u.h
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#ifndef L2HAL_MCU_DEPENDENT_MCUS_STM32F767ZIT6U_L2HAL_STM32F767ZIT6U_H_
#define L2HAL_MCU_DEPENDENT_MCUS_STM32F767ZIT6U_L2HAL_STM32F767ZIT6U_H_


#include <stm32f7xx_hal.h>
#include <l2hal_errors.h>
#include <mcus/stm32f767zit6u/drivers/input/buttons/include/l2hal_stm32f767zit6u_buttons.h>

/**
 * Maximal ports count for given device.
 */
#define L2HAL_MAX_PORTS_COUNT 11

#pragma GCC diagnostic ignored "-Wunused-variable"
/**
 * Indexes to ports, i.e. 0 -> GPIOA, 1 -> GPIOB etc.
 */
static const GPIO_TypeDef* L2HAL_IndexesToPorts[L2HAL_MAX_PORTS_COUNT] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI, GPIOJ, GPIOK };

/**
 * Enable clock for given port
 * @param port Enable clock for given port
 */
void L2HAL_MCU_ClockPortIn(GPIO_TypeDef* port);


#endif /* L2HAL_MCU_DEPENDENT_MCUS_STM32F767ZIT6U_L2HAL_STM32F767ZIT6U_H_ */
