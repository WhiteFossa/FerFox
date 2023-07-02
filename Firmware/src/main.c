
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

	L2HAL_GC9A01_Init
	(
		&DisplayContext,
		&SPI1Handle,

		HAL_DISPLAY_RESET_PORT,
		HAL_DISPLAY_RESET_PIN,

		HAL_DISPLAY_DC_PORT,
		HAL_DISPLAY_DC_PIN,

		HAL_DISPLAY_CS_PORT,
		HAL_DISPLAY_CS_PIN,

		ROTATION_180
	);

	HAL_SetBacklightLevel(HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD); /* Full brightness */

	FMGL_API_ColorStruct OffColor;
	OffColor.R = 0;
	OffColor.G = 0;
	OffColor.B = 0;

	FMGL_API_ColorStruct AwesomeColor;
	AwesomeColor.R = 0x00;
	AwesomeColor.G = 0x00;
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

	int8_t rSpeed = 32;
	int8_t gSpeed = 16;
	int8_t bSpeed = 8;

	int16_t r = 0;
	int16_t g = 0;
	int16_t b = 0;

	fpsCounter = 0;
	fpsHandlerCounter = 0;

	FMGL_API_Font fontData= FMGL_FontTerminusRegular12Init();
	FMGL_API_XBMTransparencyMode transparencyMode = FMGL_XBMTransparencyModeNormal;

	/* Font settings */
	FMGL_API_ColorStruct OnColor;
	OnColor.R = 0xFF;
	OnColor.G = 0xFF;
	OnColor.B = 0xFF;

	font.Font = &fontData;
	font.Scale = 1;
	font.CharactersSpacing = 0;
	font.LinesSpacing = 0;
	font.FontColor = &OnColor;
	font.BackgroundColor = &OffColor;
	font.Transparency = &transparencyMode;

	L2HAL_SysTick_RegisterHandler(&FpsHandler);

	while(true)
	{

		r += rSpeed;
		if (r < 0)
		{
			r = 0;
			rSpeed *= -1;
		}
		else if (r > 255)
		{
			r = 255;
			rSpeed *= -1;
		}

		g += gSpeed;
		if (g < 0)
		{
			g = 0;
			gSpeed *= -1;
		}
		else if (g > 255)
		{
			g = 255;
			gSpeed *= -1;
		}

		b += bSpeed;
		if (b < 0)
		{
			b = 0;
			bSpeed *= -1;
		}
		else if (b > 255)
		{
			b = 255;
			bSpeed *= -1;
		}

		AwesomeColor.R = r;
		AwesomeColor.G = g;
		AwesomeColor.B = b;

		/* Drawing sprite */
		FMGL_API_RenderXBM(&fmglContext, &sprite, 0, 0, 1, 1, AwesomeColor, OffColor, FMGL_XBMTransparencyModeTransparentInactive);

		/* Drawing FPS */
		/*uint16_t width, height;
		char buffer[32];
		sprintf(buffer, "FPS: %d", fps);
		FMGL_API_RenderTextWithLineBreaks(&fmglContext, &font, 50, 50, &width, &height, false, buffer);/*

		/* Pushing framebuffer */
		FMGL_API_PushFramebuffer(&fmglContext);

		fpsCounter ++;
	}
}

void FpsHandler(void)
{
	fpsHandlerCounter ++;

	if (fpsHandlerCounter == 1000)
	{
		fps = fpsCounter;
		fpsCounter = 0;
		fpsHandlerCounter = 0;
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
