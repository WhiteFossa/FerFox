/*
 * l2hal_ly68l6400_qspi.c
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#include <l2hal_ly68l6400_qspi_private.h>

void L2HAL_LY68L6400_QSPI_Init
(
	L2HAL_LY68L6400_QSPI_ContextStruct* context,

	QSPI_HandleTypeDef *qspiHandle,

	GPIO_TypeDef* chipSelectPort,
	uint16_t chipSelectPin,

	GPIO_TypeDef* clockPort,
	uint16_t clockPin,

	GPIO_TypeDef* mosiPort,
	uint16_t mosiPin,

	GPIO_TypeDef* misoPort,
	uint16_t misoPin
)
{
	/* Context setup */
	context->QSPIHandle = qspiHandle;

	context->ChipSelectPort = chipSelectPort;
	context->ChipSelectPin = chipSelectPin;

	context->ClockPort = clockPort;
	context->ClockPin = clockPin;

	context->MosiPort = mosiPort;
	context->MosiPin = mosiPin;

	context->MisoPort = misoPort;
	context->MisoPin = misoPin;

	HAL_Delay(100);

	/* After previous reset chip might be in QSPI mode, we have to pull it out from it */
	HAL_QSPI_DeInit(context->QSPIHandle);

	qspiHandle->Init.ClockPrescaler = 8; // Temporarily as slow as possible
	qspiHandle->Init.FifoThreshold = 1;
	qspiHandle->Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
	qspiHandle->Init.FlashSize = 22; // 23 bits addressing
	qspiHandle->Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_2_CYCLE;
	qspiHandle->Init.ClockMode = QSPI_CLOCK_MODE_0;
	qspiHandle->Init.FlashID = QSPI_FLASH_ID_1;
	qspiHandle->Init.DualFlash = QSPI_DUALFLASH_DISABLE;

	if (HAL_QSPI_Init(context->QSPIHandle) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	QSPI_CommandTypeDef sCommand = { 0 };

	sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
	sCommand.Instruction = 0xF5;

	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
	sCommand.Address = 0x00;

	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.AlternateBytesSize = 0;
	sCommand.AlternateBytes = 0;

	sCommand.DataMode = QSPI_DATA_NONE;
	sCommand.NbData = 0;

	sCommand.DummyCycles = 0;

	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;

	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(context->QSPIHandle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	/* Now chip must be in SPI mode, deinitializing QSPI */
	HAL_QSPI_DeInit(context->QSPIHandle);

	/* Starting in soft SPI mode to check chip state and switch it to QSPI mode */
	L2HAL_LY68L6400_QSPI_SoftSpi_Init(context);


	/* Reset enable */
	L2HAL_LY68L6400_QSPI_SoftSpi_SelectChip(context, true);
	L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(context, 0x66);
	L2HAL_LY68L6400_QSPI_SoftSpi_SelectChip(context, false);

	/* Reset */
	L2HAL_LY68L6400_QSPI_SoftSpi_SelectChip(context, true);
	L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(context, 0x99);
	L2HAL_LY68L6400_QSPI_SoftSpi_SelectChip(context, false);

	/* Chip ID - is chip on bus? */
	uint8_t readIdBuffer[2];

	L2HAL_LY68L6400_QSPI_SoftSpi_SelectChip(context, true);
	L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(context, 0x9F);
	L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(context, 0x00);
	L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(context, 0x00);
	L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(context, 0x00);

	readIdBuffer[0] = L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(context, 0x00);
	readIdBuffer[1] = L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(context, 0x00);

	L2HAL_LY68L6400_QSPI_SoftSpi_SelectChip(context, false);

	if (readIdBuffer[0] != 0x0D || readIdBuffer[1] != 0x5D)
	{
		// Chip is not on bus or failed
		L2HAL_Error(Generic);
	}

	/* Going to QSPI mode */
	L2HAL_LY68L6400_QSPI_SoftSpi_SelectChip(context, true);
	L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(context, 0x35);
	L2HAL_LY68L6400_QSPI_SoftSpi_SelectChip(context, false);

	HAL_Delay(100);

	qspiHandle->Init.ClockPrescaler = 8; // Temporarily as slow as possible
	qspiHandle->Init.FifoThreshold = 1;
	qspiHandle->Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
	qspiHandle->Init.FlashSize = 22; // 23 bits addressing
	qspiHandle->Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_2_CYCLE;
	qspiHandle->Init.ClockMode = QSPI_CLOCK_MODE_0;
	qspiHandle->Init.FlashID = QSPI_FLASH_ID_1;
	qspiHandle->Init.DualFlash = QSPI_DUALFLASH_DISABLE;

	if (HAL_QSPI_Init(context->QSPIHandle) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	uint8_t testByte = 0xA5;
	uint32_t testNumber = 0x00;

	while(1)
	{
		/* Test data */
		#define TEST_BLOCK_SIZE 8
		uint8_t writeBuffer[TEST_BLOCK_SIZE];
		for (uint8_t i = 0; i < TEST_BLOCK_SIZE; i++)
		{
			writeBuffer[i] = testByte + i;
		}

		uint8_t readBuffer[TEST_BLOCK_SIZE];

		for (uint32_t baseAddr = 0; baseAddr < L2HAL_LY68L6400_QSPI_CAPACITY; baseAddr += TEST_BLOCK_SIZE)
		{
			L2HAL_LY68L6400_QSPI_MemoryWriteInternal(context, baseAddr, TEST_BLOCK_SIZE, writeBuffer);

			L2HAL_LY68L6400_QSPI_MemoryReadInternal(context, baseAddr, TEST_BLOCK_SIZE, readBuffer);

			if (memcmp(writeBuffer, readBuffer, TEST_BLOCK_SIZE) != 0)
			{
				trace_printf("PSRAM Failure, base addr: %d\n", baseAddr);
				L2HAL_Error(Generic);
			}

			if (baseAddr % 262144 == 0)
			{
				trace_printf("Base addr %d OK\n", baseAddr);
			}
		}

		trace_printf("Check %d complete!\n", testNumber);

		testByte ++;
		testNumber ++;
	}
}

void L2HAL_LY68L6400_QSPI_SoftSpi_Init(L2HAL_LY68L6400_QSPI_ContextStruct *context)
{
	L2HAL_MCU_ClockPortIn(context->ChipSelectPort);
	L2HAL_MCU_ClockPortIn(context->ClockPort);
	L2HAL_MCU_ClockPortIn(context->MosiPort);
	L2HAL_MCU_ClockPortIn(context->MisoPort);

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* CS -> OUT, initially HIGH */
	GPIO_InitStruct.Pin = context->ChipSelectPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(context->ChipSelectPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin(context->ChipSelectPort, context->ChipSelectPin, GPIO_PIN_SET);

	/* Clock -> OUT, initially LOW */
	GPIO_InitStruct.Pin = context->ClockPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(context->ClockPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin(context->ClockPort, context->ClockPin, GPIO_PIN_RESET);

	/* MOSI -> OUT, initially LOW */
	GPIO_InitStruct.Pin = context->MosiPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(context->MosiPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin(context->MosiPort, context->MosiPin, GPIO_PIN_RESET);

	/* MISO -> IN */
	GPIO_InitStruct.Pin = context->MisoPin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(context->MisoPort, &GPIO_InitStruct);
}

void L2HAL_LY68L6400_QSPI_SoftSpi_SelectChip(L2HAL_LY68L6400_QSPI_ContextStruct *context, bool isSelected)
{
	if (isSelected)
	{
		HAL_GPIO_WritePin(context->ChipSelectPort, context->ChipSelectPin, GPIO_PIN_RESET); /* Active low*/
	}
	else
	{
		HAL_GPIO_WritePin(context->ChipSelectPort, context->ChipSelectPin, GPIO_PIN_SET);
	}

	HAL_Delay(1);
}

void L2HAL_LY68L6400_QSPI_SoftSpi_SetClockState(L2HAL_LY68L6400_QSPI_ContextStruct *context, bool isHigh)
{
	if (isHigh)
	{
		HAL_GPIO_WritePin(context->ClockPort, context->ClockPin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(context->ClockPort, context->ClockPin, GPIO_PIN_RESET);
	}
}

void L2HAL_LY68L6400_QSPI_SoftSpi_SetMosiState(L2HAL_LY68L6400_QSPI_ContextStruct *context, bool isHigh)
{
	if (isHigh)
	{
		HAL_GPIO_WritePin(context->MosiPort, context->MosiPin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(context->MosiPort, context->MosiPin, GPIO_PIN_RESET);
	}
}

GPIO_PinState L2HAL_LY68L6400_QSPI_SoftSpi_ReadMisoState(L2HAL_LY68L6400_QSPI_ContextStruct *context)
{
	return HAL_GPIO_ReadPin(context->MisoPort, context->MisoPin);
}

uint8_t L2HAL_LY68L6400_QSPI_SoftSpi_SwapBytes(L2HAL_LY68L6400_QSPI_ContextStruct *context, uint8_t toSend)
{
	uint8_t readData = 0;

	for (uint8_t i = 0; i < 8; i++)
	{
		L2HAL_LY68L6400_QSPI_SoftSpi_SetClockState(context, false);
		HAL_Delay(1);

		L2HAL_LY68L6400_QSPI_SoftSpi_SetMosiState(context, toSend & 0x80);

		HAL_Delay(1);

		toSend <<= 1;

		L2HAL_LY68L6400_QSPI_SoftSpi_SetClockState(context, true);
		HAL_Delay(1);

		readData <<= 1;
		if (L2HAL_LY68L6400_QSPI_SoftSpi_ReadMisoState(context) == GPIO_PIN_SET)
		{
			readData |= 0x01;
		}

		HAL_Delay(1);
	}

	return readData;
}

void L2HAL_LY68L6400_QSPI_MemoryReadInternal(L2HAL_LY68L6400_QSPI_ContextStruct *context, uint32_t startAddress, uint8_t size, uint8_t* buffer)
{
	if (size > L2HAL_LY68L6400_QSPI_MAX_READ_BYTES)
	{
		L2HAL_Error(Generic);
	}

	if (startAddress + (uint32_t)size > L2HAL_LY68L6400_QSPI_CAPACITY)
	{
		L2HAL_Error(Generic);
	}

	QSPI_CommandTypeDef sCommand = { 0 };

	sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
	sCommand.Instruction = 0xEB;

	sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
	sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
	sCommand.Address = startAddress;

	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.AlternateBytesSize = 0;
	sCommand.AlternateBytes = 0;

	sCommand.DataMode = QSPI_DATA_4_LINES;
	sCommand.NbData = size;

	sCommand.DummyCycles = 6;

	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;

	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(context->QSPIHandle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	if (HAL_QSPI_Receive(context->QSPIHandle, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}
}

void L2HAL_LY68L6400_QSPI_MemoryWriteInternal(L2HAL_LY68L6400_QSPI_ContextStruct *context, uint32_t startAddress, uint8_t size, uint8_t* buffer)
{
	if (size > L2HAL_LY68L6400_QSPI_MAX_READ_BYTES)
	{
		L2HAL_Error(Generic);
	}

	if (startAddress + (uint32_t)size > L2HAL_LY68L6400_QSPI_CAPACITY)
	{
		L2HAL_Error(Generic);
	}

	QSPI_CommandTypeDef sCommand = { 0 };

	sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
	sCommand.Instruction = 0x38;

	sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
	sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
	sCommand.Address = startAddress;

	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.AlternateBytesSize = 0;
	sCommand.AlternateBytes = 0;

	sCommand.DataMode = QSPI_DATA_4_LINES;
	sCommand.NbData = size;

	sCommand.DummyCycles = 0;

	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;

	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (HAL_QSPI_Command(context->QSPIHandle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	if (HAL_QSPI_Transmit(context->QSPIHandle, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}
}