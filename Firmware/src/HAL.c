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
		HAL_GPIO_WritePin(HAL_LED_PORT, HAL_LED_PIN, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(HAL_LED_PORT, HAL_LED_PIN, GPIO_PIN_SET);
	}
}

void HAL_SetBacklightLevel(uint16_t level)
{
	if (level > HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD)
	{
		level = HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD;
	}

	TIM_OC_InitTypeDef sConfig = { 0 };
	sConfig.OCMode = TIM_OCMODE_PWM1;
	sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfig.OCFastMode = TIM_OCFAST_DISABLE;
	sConfig.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	sConfig.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfig.Pulse = level;

	if (HAL_OK != HAL_TIM_PWM_ConfigChannel(&BacklightTimerHandle, &sConfig, HAL_DISPLAY_BACKLIGHT_TIMER_CHANNEL))
	{
		L2HAL_Error(Generic);
	}

	/* Start channel 2 */
	if (HAL_OK != HAL_TIM_PWM_Start(&BacklightTimerHandle, HAL_DISPLAY_BACKLIGHT_TIMER_CHANNEL))
	{
		L2HAL_Error(Generic);
	}
}
