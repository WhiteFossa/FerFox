/*
 * l2hal_ly68l6400.c
 *
 *  Created on: Sep 29, 2023
 *      Author: fossa
 */

#include <l2hal_ly68l6400_private.h>

void L2HAL_LY68L6400_Init
(
	L2HAL_LY68L6400_ContextStruct* context,
	SPI_HandleTypeDef *spiHandle,

	GPIO_TypeDef* chipSelectPort,
	uint16_t chipSelectPin
)
{
	context->SPIHandle = spiHandle;

	context->ChipSelectPort = chipSelectPort;
	context->ChipSelectPin = chipSelectPin;

	HAL_Delay(100);

	uint8_t commandBuffer[4];

	/* Reset enable */
	commandBuffer[0] = 0x66;
	L2HAL_LY68L6400_SelectChip(context, true);
	L2HAL_LY68L6400_WriteData(context, commandBuffer, 1);
	L2HAL_LY68L6400_SelectChip(context, false);

	/* Reset */
	commandBuffer[0] = 0x99;
	L2HAL_LY68L6400_SelectChip(context, true);
	L2HAL_LY68L6400_WriteData(context, commandBuffer, 1);
	L2HAL_LY68L6400_SelectChip(context, false);

	HAL_Delay(100);

	/* Chip ID - is chip on bus? */
	uint8_t readIdBuffer[2];

	commandBuffer[0] = 0x9F;
	commandBuffer[1] = 0x00;
	commandBuffer[2] = 0x00;
	commandBuffer[3] = 0x00;
	L2HAL_LY68L6400_SelectChip(context, true);
	L2HAL_LY68L6400_WriteData(context, commandBuffer, 4);
	L2HAL_LY68L6400_ReadData(context, readIdBuffer, 2);
	L2HAL_LY68L6400_SelectChip(context, false);

	if (readIdBuffer[0] != 0x0D || readIdBuffer[1] != 0x5D)
	{
		// Chip is not on bus or failed
		L2HAL_Error(Generic);
	}

	/* Experiments */
	uint8_t dbgWriteBuffer[32];
	dbgWriteBuffer[0] = 0x00;
	dbgWriteBuffer[1] = 0x01;
	dbgWriteBuffer[2] = 0x02;
	dbgWriteBuffer[3] = 0x03;
	dbgWriteBuffer[4] = 0x04;
	dbgWriteBuffer[5] = 0x05;
	dbgWriteBuffer[6] = 0x06;
	dbgWriteBuffer[7] = 0x07;
	dbgWriteBuffer[8] = 0x08;
	dbgWriteBuffer[9] = 0x09;
	dbgWriteBuffer[10] = 0x0A;
	dbgWriteBuffer[11] = 0x0B;
	dbgWriteBuffer[12] = 0x0C;
	dbgWriteBuffer[13] = 0x0D;
	dbgWriteBuffer[14] = 0x0E;
	dbgWriteBuffer[15] = 0x0F;
	dbgWriteBuffer[16] = 0x10;
	dbgWriteBuffer[17] = 0x11;
	dbgWriteBuffer[18] = 0x12;
	dbgWriteBuffer[19] = 0x13;
	dbgWriteBuffer[20] = 0x14;
	dbgWriteBuffer[21] = 0x15;
	dbgWriteBuffer[22] = 0x16;
	dbgWriteBuffer[23] = 0x17;
	dbgWriteBuffer[24] = 0x18;
	dbgWriteBuffer[25] = 0x19;
	dbgWriteBuffer[26] = 0x1A;
	dbgWriteBuffer[27] = 0x1B;
	dbgWriteBuffer[28] = 0x1C;
	dbgWriteBuffer[29] = 0x1D;
	dbgWriteBuffer[30] = 0x1E;
	dbgWriteBuffer[31] = 0x1F;

	L2HAL_LY68L6400_MemoryWriteInternal(context, 0, 32, dbgWriteBuffer);

	uint8_t dbgReadBuffer[32];
	L2HAL_LY68L6400_MemoryReadInternal(context, 0, 32, dbgReadBuffer);

	for (uint8_t i = 0; i < 32; i++)
	{
		if (dbgReadBuffer[i] != dbgWriteBuffer[i])
		{
			L2HAL_Error(Generic);
		}
	}
}

void L2HAL_LY68L6400_SelectChip(L2HAL_LY68L6400_ContextStruct *context, bool isSelected)
{
	if (isSelected)
	{
		HAL_GPIO_WritePin(context->ChipSelectPort, context->ChipSelectPin, GPIO_PIN_RESET); /* Active low*/
	}
	else
	{
		HAL_GPIO_WritePin(context->ChipSelectPort, context->ChipSelectPin, GPIO_PIN_SET);
	}
}

void L2HAL_LY68L6400_WriteData(L2HAL_LY68L6400_ContextStruct *context, uint8_t* data, uint16_t dataSize)
{
	context->IsDataTransferInProgress = true;

	if (HAL_SPI_Transmit_DMA(context->SPIHandle, data, dataSize) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	L2HAL_LY68L6400_WaitForDataTransferCompletion(context);
}

void L2HAL_LY68L6400_ReadData(L2HAL_LY68L6400_ContextStruct *context, uint8_t* dataBuffer, uint16_t readSize)
{
	uint8_t* transmitData = malloc(readSize);
	memset(transmitData, 0xFF, readSize);

	context->IsDataTransferInProgress = true;
	if (HAL_SPI_TransmitReceive_DMA(context->SPIHandle, transmitData, dataBuffer, readSize) != HAL_OK)
	{
		free(transmitData);
		L2HAL_Error(Generic);
	}

	L2HAL_LY68L6400_WaitForDataTransferCompletion(context);

	free(transmitData);
}

void L2HAL_LY68L6400_WaitForDataTransferCompletion(L2HAL_LY68L6400_ContextStruct *context)
{
	while (context->IsDataTransferInProgress) {} /* First wait for DMA completion */
	while (HAL_SPI_GetState(context->SPIHandle) != HAL_SPI_STATE_READY) { } /* Then wait for SPI ready*/
}

void L2HAL_LY68L6400_MarkDataTransferAsCompleted(L2HAL_LY68L6400_ContextStruct *context)
{
	context->IsDataTransferInProgress = false;
}

void L2HAL_LY68L6400_MemoryReadInternal(L2HAL_LY68L6400_ContextStruct *context, uint32_t startAddress, uint8_t size, uint8_t* buffer)
{
	if (size > L2HAL_LY68L6400_MAX_READ_BYTES)
	{
		L2HAL_Error(Generic);
	}

	if (startAddress + (uint32_t)size >= L2HAL_LY68L6400_CAPACITY)
	{
		L2HAL_Error(Generic);
	}

	uint8_t commandBuffer[5];

	commandBuffer[0] = 0x0B; /* Fast read */
	commandBuffer[1] = (startAddress & 0xFF0000) >> 16; // Address MSB
	commandBuffer[2] = (startAddress & 0xFF00) >> 8;
	commandBuffer[3] = startAddress & 0xFF; // Address LSB
	commandBuffer[4] = 0x00; // Wait cycle

	L2HAL_LY68L6400_SelectChip(context, true);
	L2HAL_LY68L6400_WriteData(context, commandBuffer, 5);
	L2HAL_LY68L6400_ReadData(context, buffer, size);
	L2HAL_LY68L6400_SelectChip(context, false);
}

void L2HAL_LY68L6400_MemoryWriteInternal(L2HAL_LY68L6400_ContextStruct *context, uint32_t startAddress, uint8_t size, uint8_t* buffer)
{
	if (size > L2HAL_LY68L6400_MAX_READ_BYTES)
	{
		L2HAL_Error(Generic);
	}

	if (startAddress + (uint32_t)size >= L2HAL_LY68L6400_CAPACITY)
	{
		L2HAL_Error(Generic);
	}

	uint8_t commandBuffer[4];

	commandBuffer[0] = 0x02; /* Write */
	commandBuffer[1] = (startAddress & 0xFF0000) >> 16; // Address MSB
	commandBuffer[2] = (startAddress & 0xFF00) >> 8;
	commandBuffer[3] = startAddress & 0xFF; // Address LSB

	L2HAL_LY68L6400_SelectChip(context, true);
	L2HAL_LY68L6400_WriteData(context, commandBuffer, 4); // Sending command
	L2HAL_LY68L6400_WriteData(context, buffer, size); // Writing data
	L2HAL_LY68L6400_SelectChip(context, false);
}

