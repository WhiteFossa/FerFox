/*
 * l2hal_sdcard.c
 *
 *  Created on: Jul 15, 2023
 *      Author: fossa
 */

#include <l2hal_sdcard_private.h>
#include <l2hal_sdcard.h>

void L2HAL_SDCard_Init
(
	L2HAL_SDCard_ContextStruct* context,
	SPI_HandleTypeDef *spiHandle,

	GPIO_TypeDef* chipSelectPort,
	uint16_t chipSelectPin
)
{
	context->SPIHandle = spiHandle;

	context->ChipSelectPort = chipSelectPort;
	context->ChipSelectPin = chipSelectPin;

	/*
	Step 1.

	Set DI and CS high and apply 74 or more clock pulses to SCLK. Without this
	step under certain circumstances SD-card will not work. For instance, when
	multiple SPI devices are sharing the same bus (i.e. MISO, MOSI, CS).
	*/
	L2HAL_SDCard_Select(context, false);

	const uint8_t high = 0xFF;
	for(uint8_t i = 0; i < 10; i++) // Each packet is 8 bits long, so 8 x 10 bits are sent, i.e. 80 clocks
	{
		L2HAL_SDCard_WriteDataNoCSControl(context, &high, 1);
	}

	/*
	Step 2.

	Send CMD0 (GO_IDLE_STATE): Reset the SD card.
	*/
	L2HAL_SDCard_Select(context, true);
	L2HAL_SDCard_WaitForBusyCleared(context);

	const uint8_t cmd0[] = { 0x40 | 0x00 /* CMD0 */, 0x00, 0x00, 0x00, 0x00 /* ARG = 0 */, (0x4A << 1) | 1 /* CRC7 + end bit */ };
	L2HAL_SDCard_WriteDataNoCSControl(context, cmd0, sizeof(cmd0));

	if(L2HAL_SDCard_ReadR1(context) != 0x01)
	{
		L2HAL_SDCard_Select(context, false);
		L2HAL_Error(Generic);
	}

	/*
	Step 3.

	After the card enters idle state with a CMD0, send a CMD8 with argument of
	0x000001AA and correct CRC prior to initialization process. If the CMD8 is
	rejected with illegal command error (0x05), the card is SDC version 1 or
	MMC version 3. If accepted, R7 response (R1(0x01) + 32-bit return value)
	will be returned. The lower 12 bits in the return value 0x1AA means that
	the card is SDC version 2 and it can work at voltage range of 2.7 to 3.6
	volts. If not the case, the card should be rejected.
	*/
	L2HAL_SDCard_WaitForBusyCleared(context);

	const uint8_t cmd8[] = { 0x40 | 0x08 /* CMD8 */, 0x00, 0x00, 0x01, 0xAA /* ARG */, (0x43 << 1) | 1 /* CRC7 + end bit */ };
	L2HAL_SDCard_WriteDataNoCSControl(context, cmd8, sizeof(cmd8));

	if(L2HAL_SDCard_ReadR1(context) != 0x01)
	{
		L2HAL_SDCard_Select(context, false);
		L2HAL_Error(Generic);
	}

	uint8_t r7Response[4];
	L2HAL_SDCard_ReadData(context, r7Response, sizeof(r7Response));

	if(((r7Response[2] & 0x01) != 1) || (r7Response[3] != 0xAA))
	{
		L2HAL_SDCard_Select(context, false);
		L2HAL_Error(Generic);
	}

	/*
	Step 4.

	And then initiate initialization with ACMD41 with HCS flag (bit 30).
	*/
	while(true)
	{
		L2HAL_SDCard_WaitForBusyCleared(context);

		const uint8_t cmd55[] = { 0x40 | 0x37 /* CMD55 */, 0x00, 0x00, 0x00, 0x00 /* ARG */, (0x7F << 1) | 1 /* CRC7 + end bit */ };
		L2HAL_SDCard_WriteDataNoCSControl(context, cmd55, sizeof(cmd55));

		if(L2HAL_SDCard_ReadR1(context) != 0x01)
		{
			L2HAL_SDCard_Select(context, false);
			L2HAL_Error(Generic);
		}

		L2HAL_SDCard_WaitForBusyCleared(context);

		const uint8_t acmd41[] = { 0x40 | 0x29 /* ACMD41 */, 0x40, 0x00, 0x00, 0x00 /* ARG */, (0x7F << 1) | 1 /* CRC7 + end bit */ };
		L2HAL_SDCard_WriteDataNoCSControl(context, acmd41, sizeof(acmd41));

		uint8_t r1 = L2HAL_SDCard_ReadR1(context);
		if(r1 == 0x00)
		{
			// Ready
			break;
		}

		if(r1 != 0x01)
		{
			L2HAL_SDCard_Select(context, false);
			L2HAL_Error(Generic);
		}
	}

	/*
	Step 5.

	After the initialization completed, read OCR register with CMD58 and check
	CCS flag (bit 30). When it is set, the card is a high-capacity card known
	as SDHC/SDXC.
	*/
	L2HAL_SDCard_WaitForBusyCleared(context);

	const uint8_t cmd58[] = { 0x40 | 0x3A /* CMD58 */, 0x00, 0x00, 0x00, 0x00 /* ARG */, (0x7F << 1) | 1 /* CRC7 + end bit */ };
	L2HAL_SDCard_WriteDataNoCSControl(context, cmd58, sizeof(cmd58));

	if(L2HAL_SDCard_ReadR1(context) != 0x00)
	{
		L2HAL_SDCard_Select(context, false);
		L2HAL_Error(Generic);
	}

	uint8_t response[4];
	L2HAL_SDCard_ReadData(context, response, sizeof(response));

	if((response[0] & 0xC0) != 0xC0)
	{
		L2HAL_SDCard_Select(context, false);
		L2HAL_Error(Generic);
	}

	/* Done */
	L2HAL_SDCard_Select(context, false);
}

void L2HAL_SDCard_Select(L2HAL_SDCard_ContextStruct *context, bool isSelected)
{
	const uint8_t high = 0xFF;
	L2HAL_SDCard_WriteDataNoCSControl(context, &high, 1);

	if (isSelected)
	{
		HAL_GPIO_WritePin(context->ChipSelectPort, context->ChipSelectPin, GPIO_PIN_RESET); /* Active low*/
	}
	else
	{
		HAL_GPIO_WritePin(context->ChipSelectPort, context->ChipSelectPin, GPIO_PIN_SET);
	}

	L2HAL_SDCard_WriteDataNoCSControl(context, &high, 1);
}

void L2HAL_SDCard_WriteDataNoCSControl(L2HAL_SDCard_ContextStruct *context, uint8_t *data, uint16_t dataSize)
{
	if (HAL_SPI_Transmit(context->SPIHandle, data, dataSize, 1000) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}
}

void L2HAL_SDCard_ReadData(L2HAL_SDCard_ContextStruct *context, uint8_t *buffer, uint16_t readSize)
{
	uint8_t toTransmit = 0xFF;
	while(readSize > 0)
	{
		if (HAL_SPI_TransmitReceive(context->SPIHandle, &toTransmit, buffer, 1, 1000) != HAL_OK)
		{
			L2HAL_Error(Generic);
		}

		buffer++;
		readSize--;
	}
}

void L2HAL_SDCard_WaitForBusyCleared(L2HAL_SDCard_ContextStruct *context)
{
	uint8_t flags;
	do
	{
		L2HAL_SDCard_ReadData(context, &flags, 1);
	}
	while(flags != 0xFF);
}

uint8_t L2HAL_SDCard_ReadR1(L2HAL_SDCard_ContextStruct *context)
{
	uint8_t r1Response;

	uint8_t toTransmit = 0xFF;
	while(true)
	{
		if (HAL_SPI_TransmitReceive(context->SPIHandle, &toTransmit, &r1Response, 1, 1000) != HAL_OK)
		{
			L2HAL_Error(Generic);
		}

		if((r1Response & 0x80) == 0) // 8th bit alwyas zero, r1 recevied
		{
			break;
		}
	}
	return r1Response;
}
