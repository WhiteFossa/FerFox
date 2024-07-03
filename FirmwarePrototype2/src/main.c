/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <main.h>

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[])
{
	/* Mandatory for STM32 HAL */
	HAL_Init();

	/* Our hardware */
	L2HAL_Init();
	HAL_IntiHardware();

	/* QSPI */
	QspiHandle.Instance = QUADSPI;

	/* pSRAM init */
	L2HAL_LY68L6400_QSPI_Init
	(
		&RamContext,
		&QspiHandle,

		HAL_PSRAM_CS_PORT,
		HAL_PSRAM_CS_PIN,

		HAL_PSRAM_CLK_PORT,
		HAL_PSRAM_CLK_PIN,

		HAL_PSRAM_SIO0_PORT,
		HAL_PSRAM_SIO0_PIN,

		HAL_PSRAM_SIO1_PORT,
		HAL_PSRAM_SIO1_PIN
	);

	/* Test port */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_14;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Test data */
	uint8_t testByte = 0xA5;
	uint32_t testNumber = 0x00;

	#define TEST_BLOCK_SIZE 1024U

	//#define TEST_RAM_SIZE 8388608U
	#define TEST_RAM_SIZE (8192U * 1024U)

	uint8_t writeBuffer[TEST_BLOCK_SIZE];
	uint8_t readBuffer[TEST_BLOCK_SIZE];

	while(1)
	{
		for (uint32_t i = 0; i < TEST_BLOCK_SIZE; i++)
		{
			writeBuffer[i] = (uint8_t)(testByte + i % 255);
		}

		for (uint32_t baseAddr = 0; baseAddr < TEST_RAM_SIZE; baseAddr += TEST_BLOCK_SIZE)
		{
			uint32_t remainingSize = TEST_RAM_SIZE - baseAddr;
			if (remainingSize > TEST_BLOCK_SIZE)
			{
				remainingSize = TEST_BLOCK_SIZE;
			}

			L2HAL_LY68L6400_QSPI_MemoryWrite(&RamContext, baseAddr, remainingSize, writeBuffer);

			L2HAL_LY68L6400_QSPI_MemoryRead(&RamContext, baseAddr, remainingSize, readBuffer);

			if (memcmp(writeBuffer, readBuffer, remainingSize) != 0)
			{
			//	trace_printf("PSRAM Failure, base addr: %d\n", baseAddr);
				L2HAL_Error(Generic);
			}
		}

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
		//trace_printf("Check %d complete!\n", testNumber);

		testByte ++;
		testNumber ++;
	}

	/* Main loop
	while (true)
	{
		trace_puts("Yiff");
	}*/
}

#pragma GCC diagnostic pop
