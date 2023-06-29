
// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include <main.h>
#include <stm32f4xx_hal.h>
#include <HAL.h>

int main(int argc, char* argv[])
{
	/* Mandatory for STM32 HAL */
	HAL_Init();

	/* Our hardware */
	L2HAL_Init();
	HAL_IntiHardware();

	/* Main loop */
	while(true)
	{
		HAL_SwitchLed(true);
		HAL_Delay(1000);

		HAL_SwitchLed(false);
		HAL_Delay(1000);
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
