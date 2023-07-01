
// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include <main.h>
#include <HAL.h>
#include <Awesome.h>
#include <terminusRegular12.h>

int main(int argc, char* argv[])
{
	/* Mandatory for STM32 HAL */
	HAL_Init();

	/* Our hardware */
	L2HAL_Init();
	HAL_IntiHardware();

	DisplayContext = L2HAL_GC9A01_Init
	(
		&SPI1Handle,

		HAL_DISPLAY_RESET_PORT,
		HAL_DISPLAY_RESET_PIN,

		HAL_DISPLAY_DC_PORT,
		HAL_DISPLAY_DC_PIN,

		HAL_DISPLAY_CS_PORT,
		HAL_DISPLAY_CS_PIN,

		ROTATION_180
	);

	FMGL_API_ColorStruct OffColor;
	OffColor.R = 0;
	OffColor.G = 0;
	OffColor.B = 0;

	FMGL_API_ColorStruct AwesomeColor;
	AwesomeColor.R = 0xFF;
	AwesomeColor.G = 0xFF;
	AwesomeColor.B = 0x00;

	/* Attaching FMGL to display */
	fmglContext = FMGL_API_AttachToDriver
	(
		&DisplayContext,
		&L2HAL_GC9A01_GetWidth,
		&L2HAL_GC9A01_GetHeight,
		&L2HAL_GC9A01_SetActiveColor,
		&L2HAL_GC9A01_DrawPixel,
		&L2HAL_GC9A01_GetPixel,
		&L2HAL_GC9A01_PushFramebuffer,
		OffColor
	);

	/* Preparing sprite to draw */
	sprite.Width = Awesome_width;
	sprite.Height = Awesome_height;
	sprite.Raster = Awesome_bits;

	/* Drawing sprite */
	FMGL_API_RenderXBM(&fmglContext, &sprite, 8, 8, 7, 7, AwesomeColor, OffColor, FMGL_XBMTransparencyModeTransparentInactive);

	/* Pushing framebuffer */
	FMGL_API_PushFramebuffer(&fmglContext);

	uint16_t brightness = 0;
	int8_t brightnessAdd = 1;

	while(true)
	{
		if (brightness == HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD)
		{
			brightnessAdd = -1;
		}
		else if (brightness == 0)
		{
			brightnessAdd = 1;
		}

		HAL_SetBacklightLevel(brightness);

		brightness += brightnessAdd;

		HAL_Delay(5);

/*		AwesomeColor.R += 3;
		AwesomeColor.G -= 7;
		AwesomeColor.B += 4;

		 Drawing sprite
		FMGL_API_RenderXBM(&fmglContext, &sprite, 8, 8, 7, 7, AwesomeColor, OffColor, FMGL_XBMTransparencyModeTransparentInactive);

		 Pushing framebuffer
		FMGL_API_PushFramebuffer(&fmglContext);*/
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
