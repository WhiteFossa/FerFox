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
#include <l2hal_gc9a01_lfb.h>

extern DMA_HandleTypeDef QspiDmaHandle;
extern SPI_HandleTypeDef Spi1Handle;
extern DMA_HandleTypeDef Spi1TxDmaHandle;
extern DMA_HandleTypeDef Spi1RxDmaHandle;
extern L2HAL_GC9A01_LFB_ContextStruct DisplayContext;
extern SD_HandleTypeDef SdcardHandle;
extern DMA_HandleTypeDef JpegInDmaHandle;
extern DMA_HandleTypeDef JpegOutDmaHandle;

/**
 * Put custom hardware initialization stuff here,
 */
void L2HAL_InitCustomHardware(void);

/**
 * QSPI init and de-init
 */
volatile void HAL_QSPI_MspInit(QSPI_HandleTypeDef *hqspi);
volatile void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef *hqspi);

/**
 * PWM timer-related stuff
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim);
void L2HAL_SetupBacklighTimer(void);

/**
 * CRC calculator init and de-init
 */
volatile void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc);
volatile void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc);

/**
 * SPI init and de-init
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);
void L2HAL_SetupSPI(void);

/**
 * Display
 */
void L2HAL_DisplayDmaCompleted(DMA_HandleTypeDef *hdma); /* Called when transmission via Display SPI is completed */

/**
 * SDMMC init and de-init
 */
void HAL_SD_MspInit(SD_HandleTypeDef *hsd);
void HAL_SD_MspDeInit(SD_HandleTypeDef *hsd);
void L2HAL_SetupSdcard(void);

/**
 * JPEG coded init and de-init
 */
void HAL_JPEG_MspInit(JPEG_HandleTypeDef *hjpeg);
void HAL_JPEG_MspDeInit(JPEG_HandleTypeDef *hjpeg);

#endif /* L2HAL_INCLUDE_L2HAL_CUSTOM_H_ */
