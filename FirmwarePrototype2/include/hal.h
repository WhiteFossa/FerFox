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

/**
 * Init project-specific hardware here
 */
void HAL_IntiHardware(void);


#endif /* INCLUDE_HAL_H_ */
