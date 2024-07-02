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
	HAL_NVIC_SetPriority(QUADSPI_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(QUADSPI_IRQn);

	/* NVIC configuration for DMA interrupt */
	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0x00, 0);
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

/*void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{

}*/

/* CRC-calculator related stuff end */
