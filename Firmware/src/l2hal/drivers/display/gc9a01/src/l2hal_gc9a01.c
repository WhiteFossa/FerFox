/*
 * l2hal_gc9a01.c
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#include <l2hal_gc9a01.h>
#include <l2hal_gc9a01_private.h>
#include <l2hal_errors.h>

L2HAL_GC9A01_ContextStruct L2HAL_GC9A01_Init
(
	SPI_HandleTypeDef *spiHandle,

	GPIO_TypeDef* resetPort,
	uint16_t resetPin,

	GPIO_TypeDef* dataCommandPort,
	uint16_t dataCommandPin,

	GPIO_TypeDef* chipSelectPort,
	uint16_t chipSelectPin,

	GPIO_TypeDef* backlightPort,
	uint16_t backlightPin,

	enum L2HAL_GC9A01_Orientation orientation
)
{
	L2HAL_GC9A01_ContextStruct context;

	context.SPIHandle = spiHandle;

	context.ResetPort = resetPort;
	context.ResetPin = resetPin;

	context.DataCommandPort = dataCommandPort;
	context.DataCommandPin = dataCommandPin;

	context.ChipSelectPort = chipSelectPort;
	context.ChipSelectPin = chipSelectPin;

	context.BacklightPort = backlightPort;
	context.BacklightPin = backlightPin;

	/* Initializing pins */
	GPIO_InitTypeDef GPIO_InitStruct;

	/* Reset */
	L2HAL_GC9A01_ClockPortIn(context.ResetPort);
	GPIO_InitStruct.Pin = context.ResetPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(context.ResetPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin(context.ResetPort, context.ResetPin, GPIO_PIN_RESET); /* Keep display resetted till driver will take control */

	/* D/C */
	GPIO_InitStruct.Pin = context.DataCommandPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(context.DataCommandPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin(context.DataCommandPort, context.DataCommandPin, GPIO_PIN_RESET); /* 0 - Command mode */

	/* C/S */
	GPIO_InitStruct.Pin = context.ChipSelectPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(context.ChipSelectPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin(context.ChipSelectPort, context.ChipSelectPin, GPIO_PIN_SET); /* 1 - Not selected */

	/* Backlight */
	GPIO_InitStruct.Pin = context.BacklightPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(context.BacklightPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin(context.BacklightPort, context.BacklightPin, GPIO_PIN_RESET); /* 0 - Not lit */

	L2HAL_GC9A01_ResetDisplay(&context);

	/* Initialization sequence */
	L2HAL_GC9A01_WriteCommand(&context, 0xEF);

	L2HAL_GC9A01_WriteCommand(&context, 0xEB);
	L2HAL_GC9A01_WriteByteData(&context, 0x14);

	L2HAL_GC9A01_WriteCommand(&context, 0xFE);
	L2HAL_GC9A01_WriteCommand(&context, 0xEF);

	L2HAL_GC9A01_WriteCommand(&context, 0xEB);
	L2HAL_GC9A01_WriteByteData(&context, 0x14);

	L2HAL_GC9A01_WriteCommand(&context, 0x84);
	L2HAL_GC9A01_WriteByteData(&context, 0x40);

	L2HAL_GC9A01_WriteCommand(&context, 0x85);
	L2HAL_GC9A01_WriteByteData(&context, 0xFF);

	L2HAL_GC9A01_WriteCommand(&context, 0x86);
	L2HAL_GC9A01_WriteByteData(&context, 0xFF);

	L2HAL_GC9A01_WriteCommand(&context, 0x87);
	L2HAL_GC9A01_WriteByteData(&context, 0xFF);

	L2HAL_GC9A01_WriteCommand(&context, 0x88);
	L2HAL_GC9A01_WriteByteData(&context, 0x0A);

	L2HAL_GC9A01_WriteCommand(&context, 0x89);
	L2HAL_GC9A01_WriteByteData(&context, 0x21);

	L2HAL_GC9A01_WriteCommand(&context, 0x8A);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);

	L2HAL_GC9A01_WriteCommand(&context, 0x8B);
	L2HAL_GC9A01_WriteByteData(&context, 0x80);

	L2HAL_GC9A01_WriteCommand(&context, 0x8C);
	L2HAL_GC9A01_WriteByteData(&context, 0x01);

	L2HAL_GC9A01_WriteCommand(&context, 0x8D);
	L2HAL_GC9A01_WriteByteData(&context, 0x01);

	L2HAL_GC9A01_WriteCommand(&context, 0x8E);
	L2HAL_GC9A01_WriteByteData(&context, 0xFF);

	L2HAL_GC9A01_WriteCommand(&context, 0x8F);
	L2HAL_GC9A01_WriteByteData(&context, 0xFF);


	L2HAL_GC9A01_WriteCommand(&context, 0xB6);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);

	/* Orientation */
	L2HAL_GC9A01_WriteCommand(&context, 0x36); /* Memory access control */

	/* Parameters for orientation command: MY MX MV ML BGR MH 0 0 */
	switch(orientation)
	{
		case ROTATION_0:
			L2HAL_GC9A01_WriteByteData(&context, 0b00011000);
			break;

		case ROTATION_90:
			L2HAL_GC9A01_WriteByteData(&context, 0b00101000);
			break;

		case ROTATION_180:
			L2HAL_GC9A01_WriteByteData(&context, 0b01001000);
			break;

		case ROTATION_270:
			L2HAL_GC9A01_WriteByteData(&context, 0b01101000);
			break;

		default:
			L2HAL_Error(Generic);
	}

	/* End of orientation */

	L2HAL_GC9A01_WriteCommand(&context, 0x3A); /* Set color mode */
	L2HAL_GC9A01_WriteByteData(&context, 0b01100110); /* 18 bits per pixel, 3 bytes exchange - RGB */

	L2HAL_GC9A01_WriteCommand(&context, 0x90);
	L2HAL_GC9A01_WriteByteData(&context, 0x08);
	L2HAL_GC9A01_WriteByteData(&context, 0x08);
	L2HAL_GC9A01_WriteByteData(&context, 0x08);
	L2HAL_GC9A01_WriteByteData(&context, 0x08);

	L2HAL_GC9A01_WriteCommand(&context, 0xBD);
	L2HAL_GC9A01_WriteByteData(&context, 0x06);

	L2HAL_GC9A01_WriteCommand(&context, 0xBC);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);

	L2HAL_GC9A01_WriteCommand(&context, 0xFF);
	L2HAL_GC9A01_WriteByteData(&context, 0x60);
	L2HAL_GC9A01_WriteByteData(&context, 0x01);
	L2HAL_GC9A01_WriteByteData(&context, 0x04);

	L2HAL_GC9A01_WriteCommand(&context, 0xC3);
	L2HAL_GC9A01_WriteByteData(&context, 0x13);
	L2HAL_GC9A01_WriteCommand(&context, 0xC4);
	L2HAL_GC9A01_WriteByteData(&context, 0x13);

	L2HAL_GC9A01_WriteCommand(&context, 0xC9);
	L2HAL_GC9A01_WriteByteData(&context, 0x22);

	L2HAL_GC9A01_WriteCommand(&context, 0xBE);
	L2HAL_GC9A01_WriteByteData(&context, 0x11);

	L2HAL_GC9A01_WriteCommand(&context, 0xE1);
	L2HAL_GC9A01_WriteByteData(&context, 0x10);
	L2HAL_GC9A01_WriteByteData(&context, 0x0E);

	L2HAL_GC9A01_WriteCommand(&context, 0xDF);
	L2HAL_GC9A01_WriteByteData(&context, 0x21);
	L2HAL_GC9A01_WriteByteData(&context, 0x0c);
	L2HAL_GC9A01_WriteByteData(&context, 0x02);

	L2HAL_GC9A01_WriteCommand(&context, 0xF0);
	L2HAL_GC9A01_WriteByteData(&context, 0x45);
	L2HAL_GC9A01_WriteByteData(&context, 0x09);
	L2HAL_GC9A01_WriteByteData(&context, 0x08);
	L2HAL_GC9A01_WriteByteData(&context, 0x08);
	L2HAL_GC9A01_WriteByteData(&context, 0x26);
	L2HAL_GC9A01_WriteByteData(&context, 0x2A);

	L2HAL_GC9A01_WriteCommand(&context, 0xF1);
	L2HAL_GC9A01_WriteByteData(&context, 0x43);
	L2HAL_GC9A01_WriteByteData(&context, 0x70);
	L2HAL_GC9A01_WriteByteData(&context, 0x72);
	L2HAL_GC9A01_WriteByteData(&context, 0x36);
	L2HAL_GC9A01_WriteByteData(&context, 0x37);
	L2HAL_GC9A01_WriteByteData(&context, 0x6F);

	L2HAL_GC9A01_WriteCommand(&context, 0xF2);
	L2HAL_GC9A01_WriteByteData(&context, 0x45);
	L2HAL_GC9A01_WriteByteData(&context, 0x09);
	L2HAL_GC9A01_WriteByteData(&context, 0x08);
	L2HAL_GC9A01_WriteByteData(&context, 0x08);
	L2HAL_GC9A01_WriteByteData(&context, 0x26);
	L2HAL_GC9A01_WriteByteData(&context, 0x2A);

	L2HAL_GC9A01_WriteCommand(&context, 0xF3);
	L2HAL_GC9A01_WriteByteData(&context, 0x43);
	L2HAL_GC9A01_WriteByteData(&context, 0x70);
	L2HAL_GC9A01_WriteByteData(&context, 0x72);
	L2HAL_GC9A01_WriteByteData(&context, 0x36);
	L2HAL_GC9A01_WriteByteData(&context, 0x37);
	L2HAL_GC9A01_WriteByteData(&context, 0x6F);

	L2HAL_GC9A01_WriteCommand(&context, 0xED);
	L2HAL_GC9A01_WriteByteData(&context, 0x1B);
	L2HAL_GC9A01_WriteByteData(&context, 0x0B);

	L2HAL_GC9A01_WriteCommand(&context, 0xAE);
	L2HAL_GC9A01_WriteByteData(&context, 0x77);

	L2HAL_GC9A01_WriteCommand(&context, 0xCD);
	L2HAL_GC9A01_WriteByteData(&context, 0x63);

	L2HAL_GC9A01_WriteCommand(&context, 0x70);
	L2HAL_GC9A01_WriteByteData(&context, 0x07);
	L2HAL_GC9A01_WriteByteData(&context, 0x07);
	L2HAL_GC9A01_WriteByteData(&context, 0x04);
	L2HAL_GC9A01_WriteByteData(&context, 0x0E);
	L2HAL_GC9A01_WriteByteData(&context, 0x0F);
	L2HAL_GC9A01_WriteByteData(&context, 0x09);
	L2HAL_GC9A01_WriteByteData(&context, 0x07);
	L2HAL_GC9A01_WriteByteData(&context, 0x08);
	L2HAL_GC9A01_WriteByteData(&context, 0x03);

	L2HAL_GC9A01_WriteCommand(&context, 0xE8);
	L2HAL_GC9A01_WriteByteData(&context, 0x34);

	L2HAL_GC9A01_WriteCommand(&context, 0x62);
	L2HAL_GC9A01_WriteByteData(&context, 0x18);
	L2HAL_GC9A01_WriteByteData(&context, 0x0D);
	L2HAL_GC9A01_WriteByteData(&context, 0x71);
	L2HAL_GC9A01_WriteByteData(&context, 0xED);
	L2HAL_GC9A01_WriteByteData(&context, 0x70);
	L2HAL_GC9A01_WriteByteData(&context, 0x70);
	L2HAL_GC9A01_WriteByteData(&context, 0x18);
	L2HAL_GC9A01_WriteByteData(&context, 0x0F);
	L2HAL_GC9A01_WriteByteData(&context, 0x71);
	L2HAL_GC9A01_WriteByteData(&context, 0xEF);
	L2HAL_GC9A01_WriteByteData(&context, 0x70);
	L2HAL_GC9A01_WriteByteData(&context, 0x70);

	L2HAL_GC9A01_WriteCommand(&context, 0x63);
	L2HAL_GC9A01_WriteByteData(&context, 0x18);
	L2HAL_GC9A01_WriteByteData(&context, 0x11);
	L2HAL_GC9A01_WriteByteData(&context, 0x71);
	L2HAL_GC9A01_WriteByteData(&context, 0xF1);
	L2HAL_GC9A01_WriteByteData(&context, 0x70);
	L2HAL_GC9A01_WriteByteData(&context, 0x70);
	L2HAL_GC9A01_WriteByteData(&context, 0x18);
	L2HAL_GC9A01_WriteByteData(&context, 0x13);
	L2HAL_GC9A01_WriteByteData(&context, 0x71);
	L2HAL_GC9A01_WriteByteData(&context, 0xF3);
	L2HAL_GC9A01_WriteByteData(&context, 0x70);
	L2HAL_GC9A01_WriteByteData(&context, 0x70);

	L2HAL_GC9A01_WriteCommand(&context, 0x64);
	L2HAL_GC9A01_WriteByteData(&context, 0x28);
	L2HAL_GC9A01_WriteByteData(&context, 0x29);
	L2HAL_GC9A01_WriteByteData(&context, 0xF1);
	L2HAL_GC9A01_WriteByteData(&context, 0x01);
	L2HAL_GC9A01_WriteByteData(&context, 0xF1);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0x07);

	L2HAL_GC9A01_WriteCommand(&context, 0x66);
	L2HAL_GC9A01_WriteByteData(&context, 0x3C);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0xCD);
	L2HAL_GC9A01_WriteByteData(&context, 0x67);
	L2HAL_GC9A01_WriteByteData(&context, 0x45);
	L2HAL_GC9A01_WriteByteData(&context, 0x45);
	L2HAL_GC9A01_WriteByteData(&context, 0x10);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);

	L2HAL_GC9A01_WriteCommand(&context, 0x67);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0x3C);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0x01);
	L2HAL_GC9A01_WriteByteData(&context, 0x54);
	L2HAL_GC9A01_WriteByteData(&context, 0x10);
	L2HAL_GC9A01_WriteByteData(&context, 0x32);
	L2HAL_GC9A01_WriteByteData(&context, 0x98);

	L2HAL_GC9A01_WriteCommand(&context, 0x74);
	L2HAL_GC9A01_WriteByteData(&context, 0x10);
	L2HAL_GC9A01_WriteByteData(&context, 0x85);
	L2HAL_GC9A01_WriteByteData(&context, 0x80);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);
	L2HAL_GC9A01_WriteByteData(&context, 0x4E);
	L2HAL_GC9A01_WriteByteData(&context, 0x00);

	L2HAL_GC9A01_WriteCommand(&context, 0x98);
	L2HAL_GC9A01_WriteByteData(&context, 0x3e);
	L2HAL_GC9A01_WriteByteData(&context, 0x07);

	L2HAL_GC9A01_WriteCommand(&context, 0x35);
	L2HAL_GC9A01_WriteCommand(&context, 0x21);

	L2HAL_GC9A01_WriteCommand(&context, 0x11);
	HAL_Delay(1000);
	L2HAL_GC9A01_WriteCommand(&context, 0x29);
	HAL_Delay(20);

	/* Active color is black */
	FMGL_API_ColorStruct blackColor;
	blackColor.R = 0x00;
	blackColor.G = 0x00;
	blackColor.B = 0x00;
	L2HAL_GC9A01_SetActiveColor(&context, blackColor);

	/* Filling display with black */
	L2HAL_GC9A01_ClearDisplay(&context);

	/* Finally turning backlight on */
	L2HAL_GC9A01_SwitchBacklight(&context, true);

	return context;
}

void L2HAL_GC9A01_ClockPortIn(GPIO_TypeDef* port)
{
	if (GPIOA == port)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}
	else if (GPIOB == port)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
	}
	else if (GPIOC == port)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}
	else if (GPIOD == port)
	{
		__HAL_RCC_GPIOD_CLK_ENABLE();
	}
	else if (GPIOE == port)
	{
		__HAL_RCC_GPIOE_CLK_ENABLE();
	}
	else if (GPIOH == port)
	{
		__HAL_RCC_GPIOH_CLK_ENABLE();
	}
	else
	{
		L2HAL_Error(Generic);
	}
}

void L2HAL_GC9A01_SwitchBacklight(L2HAL_GC9A01_ContextStruct *context, bool isOn)
{
	if (isOn)
	{
		HAL_GPIO_WritePin(context->BacklightPort, context->BacklightPin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(context->BacklightPort, context->BacklightPin, GPIO_PIN_RESET);
	}
}

void L2HAL_GC9A01_SelectChip(L2HAL_GC9A01_ContextStruct *context, bool isSelected)
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

void L2HAL_GC9A01_ResetDisplay(L2HAL_GC9A01_ContextStruct *context)
{
	L2HAL_GC9A01_SelectChip(context, false);
	HAL_Delay(L2HAL_GC9A01_CS_TO_RESET);

	HAL_GPIO_WritePin(context->ResetPort, context->ResetPin, GPIO_PIN_RESET);
	HAL_Delay(L2HAL_GC9A01_RESET_DURATION);

	HAL_GPIO_WritePin(context->ResetPort, context->ResetPin, GPIO_PIN_SET);
	HAL_Delay(L2HAL_GC9A01_DISPLAY_BOOT_TIME);
}

void L2HAL_GC9A01_WriteCommand(L2HAL_GC9A01_ContextStruct *context, uint8_t command)
{
	HAL_GPIO_WritePin(context->DataCommandPort, context->DataCommandPin, GPIO_PIN_RESET); /* 0 - Command */

	L2HAL_GC9A01_SelectChip(context, true);

	if (HAL_SPI_Transmit(context->SPIHandle, &command, 1, L2HAL_GC9A01_TRANSMIT_TIMEOUT) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	L2HAL_GC9A01_SelectChip(context, false);
}

void L2HAL_GC9A01_WriteData(L2HAL_GC9A01_ContextStruct *context, uint8_t *data, uint16_t dataSize)
{
	HAL_GPIO_WritePin(context->DataCommandPort, context->DataCommandPin, GPIO_PIN_SET); /* 1 - Data */

	L2HAL_GC9A01_SelectChip(context, true);

	if (HAL_SPI_Transmit(context->SPIHandle, data, dataSize, L2HAL_GC9A01_TRANSMIT_TIMEOUT) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	L2HAL_GC9A01_SelectChip(context, false);
}

void L2HAL_GC9A01_WriteByteData(L2HAL_GC9A01_ContextStruct *context, uint8_t byteData)
{
	L2HAL_GC9A01_WriteData(context, &byteData, 1);
}

void L2HAL_GC9A01_SetColumnsRange(L2HAL_GC9A01_ContextStruct *context, uint16_t colStart, uint16_t colEnd)
{
    uint8_t data[4];

    L2HAL_GC9A01_WriteCommand(context, 0x2A); /* Column address */
    data[0] = (colStart >> 8) & 0xFFU;
    data[1] = colStart & 0xFFU;

    data[2] = (colEnd >> 8) & 0xFFU;
    data[3] = colEnd & 0xFFU;

    L2HAL_GC9A01_WriteData(context, data, 4);
}

void L2HAL_GC9A01_SetRowsRange(L2HAL_GC9A01_ContextStruct *context, uint16_t rowStart, uint16_t rowEnd)
{
	uint8_t data[4];

	L2HAL_GC9A01_WriteCommand(context, 0x2B); /* Row address */
	data[0] = (rowStart >> 8) & 0xFFU;
	data[1] = rowStart & 0xFFU;

	data[2] = (rowEnd >> 8) & 0xFFU;
	data[3] = rowEnd & 0xFFU;

	L2HAL_GC9A01_WriteData(context, data, 4);
}

uint16_t L2HAL_GC9A01_GetWidth(void)
{
	return L2HAL_GC9A01_DISPLAY_WIDTH;
}

uint16_t L2HAL_GC9A01_GetHeight(void)
{
	return L2HAL_GC9A01_DISPLAY_HEIGHT;
}

void L2HAL_GC9A01_ClearDisplay(L2HAL_GC9A01_ContextStruct *context)
{
	/* Full width */
	L2HAL_GC9A01_SetColumnsRange(context, 0, L2HAL_GC9A01_DISPLAY_WIDTH - 1);

	uint8_t lineBuffer[L2HAL_GC9A01_DISPLAY_WIDTH * 3];
	for (uint8_t x = 0; x < L2HAL_GC9A01_DISPLAY_WIDTH; x++)
	{
		uint16_t base = x * 3;

		lineBuffer[base + 0] = context->ActiveColor.R;
		lineBuffer[base + 1] = context->ActiveColor.G;
		lineBuffer[base + 2] = context->ActiveColor.B;
	}

	for (uint8_t y = 0; y < L2HAL_GC9A01_DISPLAY_HEIGHT; y++)
	{
		L2HAL_GC9A01_SetRowsRange(context, y, y); /* Row by row */

		L2HAL_GC9A01_WriteCommand(context, 0x2C); /* Start data write */
		L2HAL_GC9A01_WriteData(context, lineBuffer, L2HAL_GC9A01_DISPLAY_WIDTH * 3);
	}
}

void L2HAL_GC9A01_DrawPixel(L2HAL_GC9A01_ContextStruct* context, uint16_t x, uint16_t y)
{
	L2HAL_GC9A01_SetColumnsRange(context, x, x);
	L2HAL_GC9A01_SetRowsRange(context, y, y);

	uint8_t pixelData[3];
	pixelData[0] = context->ActiveColor.R;
	pixelData[1] = context->ActiveColor.G;
	pixelData[2] = context->ActiveColor.B;

	L2HAL_GC9A01_WriteCommand(context, 0x2C);
	L2HAL_GC9A01_WriteData(context, pixelData, 3);

	/* Why, gods, why we need to send the pixel again? */
	L2HAL_GC9A01_WriteCommand(context, 0x3C);
	L2HAL_GC9A01_WriteData(context, pixelData, 3);
}

void L2HAL_GC9A01_SetActiveColor(L2HAL_GC9A01_ContextStruct* context, FMGL_API_ColorStruct color)
{
	context->ActiveColor = color;
}

FMGL_API_ColorStruct L2HAL_GC9A01_GetPixel(L2HAL_GC9A01_ContextStruct* context, uint16_t x, uint16_t y)
{
	/* Dummy because we have no framebuffer */
	FMGL_API_ColorStruct color;
	color.R = 0x00;
	color.G = 0x00;
	color.B = 0x00;

	return color;
}

void L2HAL_GC9A01_PushFramebuffer(L2HAL_GC9A01_ContextStruct* context)
{
	/* Do nothing, we have no framebuffer */
}
