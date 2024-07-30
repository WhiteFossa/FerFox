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

#include <l2hal_custom.h>
#include <hal.h>

void L2HAL_InitCustomHardware(void)
{
	L2HAL_SetupSPI();

	L2HAL_SetupBacklighTimer();

	L2HAL_SetupSdcard();
}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef *hqspi)
{
	/* Enable the QuadSPI memory interface clock */
	__HAL_RCC_QSPI_CLK_ENABLE();

	/* Enable QSPI DMA clock */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* Reset the QuadSPI memory interface */
	__HAL_RCC_QSPI_FORCE_RESET();
	__HAL_RCC_QSPI_RELEASE_RESET();

	/* Enable QSPI port clocks */
	L2HAL_MCU_ClockPortIn(HAL_QSPI_PORT1);
	L2HAL_MCU_ClockPortIn(HAL_QSPI_PORT2);

	GPIO_InitTypeDef GPIO_InitStruct;

	/* QSPI CS GPIO pin configuration  */
	GPIO_InitStruct.Pin = HAL_PSRAM_CS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
	HAL_GPIO_Init(HAL_PSRAM_CS_PORT, &GPIO_InitStruct);

	/* QSPI CLK GPIO pin configuration  */
	GPIO_InitStruct.Pin = HAL_PSRAM_CLK_PIN;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(HAL_PSRAM_CLK_PORT, &GPIO_InitStruct);

	/* QSPI D0 GPIO pin configuration  */
	GPIO_InitStruct.Pin = HAL_PSRAM_SIO0_PIN;
	GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
	HAL_GPIO_Init(HAL_PSRAM_SIO0_PORT, &GPIO_InitStruct);

	/* QSPI D1 GPIO pin configuration  */
	GPIO_InitStruct.Pin = HAL_PSRAM_SIO1_PIN;
	GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
	HAL_GPIO_Init(HAL_PSRAM_SIO1_PORT, &GPIO_InitStruct);

	/* QSPI D2 GPIO pin configuration  */
	GPIO_InitStruct.Pin = HAL_PSRAM_SIO2_PIN;
	GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(HAL_PSRAM_SIO2_PORT, &GPIO_InitStruct);

	/* QSPI D3 GPIO pin configuration  */
	GPIO_InitStruct.Pin = HAL_PSRAM_SIO3_PIN;
	GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(HAL_PSRAM_SIO3_PORT, &GPIO_InitStruct);

	/* Setting up DMA */
	QspiDmaHandle.Instance = DMA2_Stream7;
	QspiDmaHandle.Init.Channel = DMA_CHANNEL_3;
	QspiDmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
	QspiDmaHandle.Init.MemInc = DMA_MINC_ENABLE;
	QspiDmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	QspiDmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	QspiDmaHandle.Init.Mode = DMA_NORMAL;
	QspiDmaHandle.Init.Priority = DMA_PRIORITY_LOW;
	QspiDmaHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	QspiDmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	QspiDmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;
	QspiDmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;

	__HAL_LINKDMA(hqspi, hdma, QspiDmaHandle);
	HAL_DMA_Init(&QspiDmaHandle);

	/* NVIC configuration for QSPI interrupt */
	HAL_NVIC_SetPriority(QUADSPI_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(QUADSPI_IRQn);

	/* NVIC configuration for DMA interrupt */
	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef *hqspi)
{
	/* Disable QSPI and QSPI DMA interrupts */
	HAL_NVIC_DisableIRQ(DMA2_Stream7_IRQn);
	HAL_NVIC_DisableIRQ(QUADSPI_IRQn);

	QspiDmaHandle.Instance = DMA2_Stream7;
	HAL_DMA_DeInit(&QspiDmaHandle);

	/* De-Configure QSPI pins */
	HAL_GPIO_DeInit(HAL_PSRAM_CS_PORT, HAL_PSRAM_CS_PIN);
	HAL_GPIO_DeInit(HAL_PSRAM_CLK_PORT, HAL_PSRAM_CLK_PIN);
	HAL_GPIO_DeInit(HAL_PSRAM_SIO0_PORT, HAL_PSRAM_SIO0_PIN);
	HAL_GPIO_DeInit(HAL_PSRAM_SIO1_PORT, HAL_PSRAM_SIO1_PIN);
	HAL_GPIO_DeInit(HAL_PSRAM_SIO2_PORT, HAL_PSRAM_SIO2_PIN);
	HAL_GPIO_DeInit(HAL_PSRAM_SIO3_PORT, HAL_PSRAM_SIO3_PIN);

	/* Reset the QuadSPI memory interface */
	__HAL_RCC_QSPI_FORCE_RESET();
	__HAL_RCC_QSPI_RELEASE_RESET();

	/* Disable the QuadSPI memory interface clock */
	__HAL_RCC_QSPI_CLK_DISABLE();
}

/* CRC-calculator related stuff begin */

void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc)
{
	__HAL_RCC_CRC_CLK_ENABLE();
}

void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc)
{
	__HAL_RCC_CRC_CLK_DISABLE();
}

/* Begin PWM timers related stuff */

void L2HAL_SetupBacklighTimer(void)
{
	/* Setting up timer itself */
	BacklightTimerHandle.Instance = HAL_DISPLAY_BACKLIGHT_TIMER;
	BacklightTimerHandle.Init.Prescaler = (uint32_t)(SystemCoreClock / HAL_DISPLAY_BACKLIGHT_TIMER_FREQ) - 1;
	BacklightTimerHandle.Init.Period = HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD;
	BacklightTimerHandle.Init.ClockDivision = 0;
	BacklightTimerHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	BacklightTimerHandle.Init.RepetitionCounter = 0;
	BacklightTimerHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if (HAL_OK != HAL_TIM_PWM_Init(&BacklightTimerHandle))
	{
		L2HAL_Error(Generic);
	}

	/* Setting up PWM */
	HAL_SetBacklightLevel(0);
}


void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	if (HAL_DISPLAY_BACKLIGHT_TIMER == htim->Instance)
	{
		HAL_DISPLAY_BACKLIGHT_TIMER_CLOCK_IN();

		L2HAL_MCU_ClockPortIn(HAL_DISPLAY_BACKLIGHT_TIMER_PORT);

		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = HAL_DISPLAY_BACKLIGHT_TIMER_PIN_AF;
		GPIO_InitStruct.Pin = HAL_DISPLAY_BACKLIGHT_TIMER_PIN;
		HAL_GPIO_Init(HAL_DISPLAY_BACKLIGHT_TIMER_PORT, &GPIO_InitStruct);
	}
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim)
{
	if (HAL_DISPLAY_BACKLIGHT_TIMER == htim->Instance)
	{
		/* Returning PB3 to normal mode, input direction (to be safe) */
		L2HAL_MCU_ClockPortIn(HAL_DISPLAY_BACKLIGHT_TIMER_PORT);

		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = HAL_DISPLAY_BACKLIGHT_TIMER_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(HAL_DISPLAY_BACKLIGHT_TIMER_PORT, &GPIO_InitStruct);
	}
}

/* End of PWM timers related stuff */

/* Begin SPI-related stuff */

void L2HAL_SetupSPI(void)
{
	/* SPI1 */
	Spi1Handle.Instance = SPI1;
	Spi1Handle.Init.Mode = SPI_MODE_MASTER;
	Spi1Handle.Init.Direction = SPI_DIRECTION_2LINES;
	Spi1Handle.Init.DataSize =  SPI_DATASIZE_8BIT;
	Spi1Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	Spi1Handle.Init.CLKPhase = SPI_PHASE_1EDGE;
	Spi1Handle.Init.CLKPolarity = SPI_POLARITY_LOW;
	Spi1Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	Spi1Handle.Init.TIMode = SPI_TIMODE_DISABLE;
	Spi1Handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	Spi1Handle.Init.NSS = SPI_NSS_SOFT;

	if(HAL_SPI_Init(&Spi1Handle) != HAL_OK)
	{
		/* Initialization Error */
		L2HAL_Error(Generic);
	}
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI1)
	{
		/**
		 * SPI1 at PA5 (SCK), PA6 (MISO) and PA7 (MOSI)
		 */
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_SPI1_CLK_ENABLE();
		__HAL_RCC_DMA2_CLK_ENABLE();

		GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

		GPIO_InitStruct.Pin = GPIO_PIN_5;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_7;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* TX DMA */
		Spi1TxDmaHandle.Instance = DMA2_Stream3;
		Spi1TxDmaHandle.Init.Channel = DMA_CHANNEL_3;
		Spi1TxDmaHandle.Init.Direction = DMA_MEMORY_TO_PERIPH;
		Spi1TxDmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
		Spi1TxDmaHandle.Init.MemInc = DMA_MINC_ENABLE;
		Spi1TxDmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		Spi1TxDmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		Spi1TxDmaHandle.Init.Mode = DMA_NORMAL;
		Spi1TxDmaHandle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
		Spi1TxDmaHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		Spi1TxDmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		Spi1TxDmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;
		Spi1TxDmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;

		if (HAL_DMA_Init(&Spi1TxDmaHandle) != HAL_OK)
		{
			L2HAL_Error(Generic);
		}

		__HAL_LINKDMA(hspi, hdmatx, Spi1TxDmaHandle);

		HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 14, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

		/* RX DMA */
		Spi1RxDmaHandle.Instance = DMA2_Stream2;
		Spi1RxDmaHandle.Init.Channel = DMA_CHANNEL_3;
		Spi1RxDmaHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
		Spi1RxDmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
		Spi1RxDmaHandle.Init.MemInc = DMA_MINC_ENABLE;
		Spi1RxDmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		Spi1RxDmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		Spi1RxDmaHandle.Init.Mode = DMA_NORMAL;
		Spi1RxDmaHandle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
		Spi1RxDmaHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		Spi1RxDmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		Spi1RxDmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;
		Spi1RxDmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;

		if (HAL_DMA_Init(&Spi1RxDmaHandle) != HAL_OK)
		{
			L2HAL_Error(Generic);
		}

		__HAL_LINKDMA(hspi, hdmarx, Spi1RxDmaHandle);

		HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 14, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI1)
	{
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

		HAL_DMA_DeInit(&Spi1TxDmaHandle);
		HAL_NVIC_DisableIRQ(DMA2_Stream3_IRQn);

		HAL_DMA_DeInit(&Spi1RxDmaHandle);
		HAL_NVIC_DisableIRQ(DMA2_Stream2_IRQn);
	}
}

void L2HAL_DisplayDmaCompleted(DMA_HandleTypeDef *hdma)
{
	L2HAL_GC9A01_LFB_MarkDataTransferAsCompleted(&DisplayContext);
}


void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
	if (hsd->Instance == SDMMC1)
	{
		__HAL_RCC_SDMMC1_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();

		__HAL_RCC_DMA2_CLK_ENABLE();

		GPIO_InitTypeDef GPIO_InitStruct;

		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

		/* PC8 - SD D0 */
		GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
		GPIO_InitStruct.Pin = GPIO_PIN_8;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* PC9 - SD D1 */
		GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
		GPIO_InitStruct.Pin = GPIO_PIN_9;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* PC10 - SD D2 */
		GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
		GPIO_InitStruct.Pin = GPIO_PIN_10;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* PC11 - SD D3 */
		GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
		GPIO_InitStruct.Pin = GPIO_PIN_11;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* PC12 - SD CLOCK */
		GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
		GPIO_InitStruct.Pin = GPIO_PIN_12;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* PD2 - SD CMD */
		GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
		GPIO_InitStruct.Pin = GPIO_PIN_2;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
}

void HAL_SD_MspDeInit(SD_HandleTypeDef *hsd)
{
	if (hsd->Instance == SDMMC1)
	{
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

		__HAL_RCC_SDMMC1_CLK_DISABLE();
	}
}

void L2HAL_SetupSdcard(void)
{
	/* Low speed, narrow mode, for init */
	SdcardHandle.Instance = SDMMC1;
	SdcardHandle.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
	SdcardHandle.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
	SdcardHandle.Init.BusWide = SDMMC_BUS_WIDE_1B;
	SdcardHandle.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_ENABLE;
	SdcardHandle.Init.ClockDiv = 268; // 108 MHz / (268 + 2) = 400 kHz

	if (HAL_SD_Init(&SdcardHandle) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	if (HAL_SD_InitCard(&SdcardHandle) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	/* Full speed, wide mode */
	SdcardHandle.Init.ClockDiv = 3; // 108 MHz / (3 + 2) = 21.6 MHz
	if (HAL_SD_ConfigWideBusOperation(&SdcardHandle, SDMMC_BUS_WIDE_4B) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}
}

void HAL_JPEG_MspInit(JPEG_HandleTypeDef *hjpeg)
{
	__HAL_RCC_JPEG_CLK_ENABLE();

	__HAL_RCC_JPEG_FORCE_RESET();
	__HAL_RCC_JPEG_RELEASE_RESET();

	/* Enable DMA clock */
	__DMA2_CLK_ENABLE();

	HAL_NVIC_SetPriority(JPEG_IRQn, 8, 0);
	HAL_NVIC_EnableIRQ(JPEG_IRQn);

	/* Input DMA */
	JpegInDmaHandle.Instance = DMA2_Stream0;
	JpegInDmaHandle.Init.Channel = DMA_CHANNEL_9;
	JpegInDmaHandle.Init.Direction = DMA_MEMORY_TO_PERIPH;
	JpegInDmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
	JpegInDmaHandle.Init.MemInc = DMA_MINC_ENABLE;
	JpegInDmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	JpegInDmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	JpegInDmaHandle.Init.Mode = DMA_NORMAL;
	JpegInDmaHandle.Init.Priority = DMA_PRIORITY_HIGH;
	JpegInDmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	JpegInDmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	JpegInDmaHandle.Init.MemBurst = DMA_MBURST_INC4;
	JpegInDmaHandle.Init.PeriphBurst = DMA_PBURST_INC4;

	__HAL_LINKDMA(hjpeg, hdmain, JpegInDmaHandle);

	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 8, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

	HAL_DMA_DeInit(&JpegInDmaHandle);
	HAL_DMA_Init(&JpegInDmaHandle);


	/* Output DMA */
	JpegOutDmaHandle.Instance = DMA2_Stream1;
	JpegOutDmaHandle.Init.Channel = DMA_CHANNEL_9;
	JpegOutDmaHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
	JpegOutDmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
	JpegOutDmaHandle.Init.MemInc = DMA_MINC_ENABLE;
	JpegOutDmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	JpegOutDmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	JpegOutDmaHandle.Init.Mode = DMA_NORMAL;
	JpegOutDmaHandle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
	JpegOutDmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	JpegOutDmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	JpegOutDmaHandle.Init.MemBurst = DMA_MBURST_INC4;
	JpegOutDmaHandle.Init.PeriphBurst = DMA_PBURST_INC4;

	__HAL_LINKDMA(hjpeg, hdmaout, JpegOutDmaHandle);

	HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 8, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

	HAL_DMA_DeInit(&JpegOutDmaHandle);
	HAL_DMA_Init(&JpegOutDmaHandle);
}

void HAL_JPEG_MspDeInit(JPEG_HandleTypeDef *hjpeg)
{
	__HAL_RCC_JPEG_CLK_DISABLE();
}

