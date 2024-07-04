/*
 * hal.c
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#include <hal.h>

void HAL_IntiHardware(void)
{
	/* Setting up start-up conditions for PSRAM immediately after power up */
	L2HAL_MCU_ClockPortIn(HAL_QSPI_PORT1);
	L2HAL_MCU_ClockPortIn(HAL_QSPI_PORT2);

	GPIO_InitTypeDef GPIO_InitStruct;

	/* PSRAM CS -> HIGH */
	GPIO_InitStruct.Pin = HAL_PSRAM_CS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(HAL_PSRAM_CS_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_PSRAM_CS_PORT, HAL_PSRAM_CS_PIN, GPIO_PIN_SET);

	/* PSRAM SIO0 -> LOW */
	GPIO_InitStruct.Pin = HAL_PSRAM_SIO0_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(HAL_PSRAM_SIO0_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_PSRAM_SIO0_PORT, HAL_PSRAM_SIO0_PIN, GPIO_PIN_RESET);

	/* PSRAM SIO1 -> LOW */
	GPIO_InitStruct.Pin = HAL_PSRAM_SIO1_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(HAL_PSRAM_SIO1_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_PSRAM_SIO1_PORT, HAL_PSRAM_SIO1_PIN, GPIO_PIN_RESET);

	/* PSRAM SIO2 -> LOW */
	GPIO_InitStruct.Pin = HAL_PSRAM_SIO2_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(HAL_PSRAM_SIO2_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_PSRAM_SIO2_PORT, HAL_PSRAM_SIO2_PIN, GPIO_PIN_RESET);

	/* PSRAM SIO3 -> LOW */
	GPIO_InitStruct.Pin = HAL_PSRAM_SIO3_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(HAL_PSRAM_SIO3_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_PSRAM_SIO3_PORT, HAL_PSRAM_SIO3_PIN, GPIO_PIN_RESET);

	/* PSRAM CLK -> LOW */
	GPIO_InitStruct.Pin = HAL_PSRAM_CLK_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(HAL_PSRAM_CLK_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_PSRAM_CLK_PORT, HAL_PSRAM_CLK_PIN, GPIO_PIN_RESET);

	/* Initializing display pins */
	/* Reset */
	L2HAL_MCU_ClockPortIn(HAL_DISPLAY_RESET_PORT);
	GPIO_InitStruct.Pin = HAL_DISPLAY_RESET_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(HAL_DISPLAY_RESET_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_DISPLAY_RESET_PORT, HAL_DISPLAY_RESET_PIN, GPIO_PIN_RESET); /* Keep display resetted till driver will take control */

	/* D/C */
	L2HAL_MCU_ClockPortIn(HAL_DISPLAY_DC_PORT);
	GPIO_InitStruct.Pin = HAL_DISPLAY_DC_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(HAL_DISPLAY_DC_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_DISPLAY_DC_PORT, HAL_DISPLAY_DC_PIN, GPIO_PIN_RESET); /* 0 - Command mode */

	/* C/S */
	L2HAL_MCU_ClockPortIn(HAL_DISPLAY_CS_PORT);
	GPIO_InitStruct.Pin = HAL_DISPLAY_CS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(HAL_DISPLAY_CS_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(HAL_DISPLAY_CS_PORT, HAL_DISPLAY_CS_PIN, GPIO_PIN_SET); /* 1 - Not selected */
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

	if (HAL_OK != HAL_TIM_PWM_Start(&BacklightTimerHandle, HAL_DISPLAY_BACKLIGHT_TIMER_CHANNEL))
	{
		L2HAL_Error(Generic);
	}
}
