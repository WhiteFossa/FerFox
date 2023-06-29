/*
 * HAL.c
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#include <HAL.h>


void HAL_IntiHardware(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

	/* LED */
	GPIO_InitStruct.Pin = HAL_LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(HAL_LED_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_LED_PORT, HAL_LED_PIN, GPIO_PIN_SET);

	/* Display-related pins initialization*/

	/* Reset */
	GPIO_InitStruct.Pin = HAL_DISPLAY_RESET_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(HAL_DISPLAY_RESET_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_DISPLAY_RESET_PORT, HAL_DISPLAY_RESET_PIN, GPIO_PIN_RESET); /* Keep display resetted till driver will take control */

	/* D/C */
	GPIO_InitStruct.Pin = HAL_DISPLAY_DC_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(HAL_DISPLAY_DC_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_DISPLAY_DC_PORT, HAL_DISPLAY_DC_PIN, GPIO_PIN_RESET); /* 0 - Command mode */

	/* C/S */
	GPIO_InitStruct.Pin = HAL_DISPLAY_CS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(HAL_DISPLAY_CS_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_DISPLAY_CS_PORT, HAL_DISPLAY_CS_PIN, GPIO_PIN_SET); /* 1 - Not selected */

	/* Backlight */
	GPIO_InitStruct.Pin = HAL_DISPLAY_BACKLIGHT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(HAL_DISPLAY_BACKLIGHT_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_DISPLAY_BACKLIGHT_PORT, HAL_DISPLAY_BACKLIGHT_PIN, GPIO_PIN_RESET); /* 0 - Not lit */
}


void HAL_SwitchLed(bool isOn)
{
	if (isOn)
	{
		HAL_GPIO_WritePin(HAL_LED_PORT, HAL_LED_PIN, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(HAL_LED_PORT, HAL_LED_PIN, GPIO_PIN_RESET);
	}
}
