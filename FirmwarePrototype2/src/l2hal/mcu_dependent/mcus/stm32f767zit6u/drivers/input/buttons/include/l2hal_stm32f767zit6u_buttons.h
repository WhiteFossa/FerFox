/*
 * l2hal_stm32f767zit6u_buttons.h
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#ifndef L2HAL_MCU_DEPENDENT_MCUS_STM32F767ZIT6U_DRIVERS_INPUT_BUTTONS_INCLUDE_L2HAL_STM32F767ZIT6U_BUTTONS_H_
#define L2HAL_MCU_DEPENDENT_MCUS_STM32F767ZIT6U_DRIVERS_INPUT_BUTTONS_INCLUDE_L2HAL_STM32F767ZIT6U_BUTTONS_H_

#include <l2hal_buttons_defaults.h>
#include <l2hal_errors.h>

/**
 * Default pin initializer for buttons driver. Clocking port in, setting pin as input and enabling pull-up for it.
 * @port port Pins belongs to this port.
 * @port pins Pins to initialize.
 */
void L2HAL_Buttons_DefaultPinInitializer(GPIO_TypeDef* port, uint32_t pins);

#endif /* L2HAL_MCU_DEPENDENT_MCUS_STM32F767ZIT6U_DRIVERS_INPUT_BUTTONS_INCLUDE_L2HAL_STM32F767ZIT6U_BUTTONS_H_ */
