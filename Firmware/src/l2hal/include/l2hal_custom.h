/*
	This file is part of Fossa's STM32 level 2 HAL.

	STM32 level 2 HAL is free software:
	you can redistribute it and/or modify it under the terms of the
	GNU General Public License as published by the Free Software
	Foundation, either version 3 of the License, or (at your option)
	any later version.

	STM32 level 2 HAL is distributed in the hope
	that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A
	PARTICULAR PURPOSE.  See the GNU General Public License for more
	details.

	You should have received a copy of the GNU General Public License
	along with STM32 level 2 HAL.

	If not, see <http://www.gnu.org/licenses/>.

	-------------------------------------------------------------------------

	Created by White Fossa, also known as Artyom Vetrov.

	Feel free to contact: whitefossa@gmail.com

	Repository: https://github.com/WhiteFossa/stm32-l2hal

	If repository above is not available, try my LiveJournal:
	fossa-white.livejournal.com

	or as last measure try to search for #WhiteFossa hashtag.

	-------------------------------------------------------------------------
 */

/**
 * @file
 * @biref File for custom hardware-related stuff.
 */

#ifndef L2HAL_INCLUDE_L2HAL_CUSTOM_H_
#define L2HAL_INCLUDE_L2HAL_CUSTOM_H_

#include <l2hal_mcu.h>
#include <l2hal_errors.h>
#include <l2hal_gc9a01.h>
#include <l2hal_sdcard.h>

extern SPI_HandleTypeDef SPI2Handle;
extern DMA_HandleTypeDef SPI2DmaHandle;
extern L2HAL_GC9A01_ContextStruct DisplayContext;
extern L2HAL_SDCard_ContextStruct SDCardContext;

extern TIM_HandleTypeDef BacklightTimerHandle;

/**
 * Put custom hardware initialization stuff here,
 */
void L2HAL_InitCustomHardware(void);

/**
 * SPI-related stuff
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);
void L2HAL_SetupSPI(void);
void L2HAL_DisplayDmaCompleted(DMA_HandleTypeDef *hdma); /* Called when transmission via Display SPI is completed */

/**
 * PWM timer-related stuff
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim);
void L2HAL_SetupBacklighTimer(void);

#endif /* L2HAL_INCLUDE_L2HAL_CUSTOM_H_ */
