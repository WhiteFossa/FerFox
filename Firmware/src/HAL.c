/*
 * HAL.c
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#include <HAL.h>


void HAL_IntiHardware(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

	/* LED */
	GPIO_InitStruct.Pin = HAL_LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(HAL_LED_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_LED_PORT, HAL_LED_PIN, GPIO_PIN_SET);
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
