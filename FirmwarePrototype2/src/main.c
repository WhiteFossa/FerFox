/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <main.h>

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[])
{
	/* Mandatory for STM32 HAL */
	HAL_Init();

	/* Our hardware */
	L2HAL_Init();
	HAL_IntiHardware();

	/* QSPI */
	QspiHandle.Instance = QUADSPI;

	/* pSRAM init */
	L2HAL_LY68L6400_QSPI_Init
	(
		&RamContext,
		&QspiHandle,

		HAL_PSRAM_CS_PORT,
		HAL_PSRAM_CS_PIN,

		HAL_PSRAM_CLK_PORT,
		HAL_PSRAM_CLK_PIN,

		HAL_PSRAM_SIO0_PORT,
		HAL_PSRAM_SIO0_PIN,

		HAL_PSRAM_SIO1_PORT,
		HAL_PSRAM_SIO1_PIN
	);

	/* Display */
	HAL_SetBacklightLevel(HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD); /* Full brightness */

	/* Display driver initialization */
	L2HAL_GC9A01_LFB_Init
	(
		&DisplayContext,
		&Spi1Handle,

		HAL_DISPLAY_RESET_PORT,
		HAL_DISPLAY_RESET_PIN,

		HAL_DISPLAY_DC_PORT,
		HAL_DISPLAY_DC_PIN,

		HAL_DISPLAY_CS_PORT,
		HAL_DISPLAY_CS_PIN,

		L2HAL_GC9A01_LFB_ROTATION_180
	);

	/* FMGL initialization */
	FMGL_API_ColorStruct OffColor;
	OffColor.R = 0;
	OffColor.G = 0;
	OffColor.B = 0;

	/* Attaching FMGL to display */
	FmglContext = FMGL_API_AttachToDriver
	(
		&DisplayContext,
		&L2HAL_GC9A01_LFB_GetWidth,
		&L2HAL_GC9A01_LFB_GetHeight,
		&L2HAL_GC9A01_LFB_SetActiveColor,
		&L2HAL_GC9A01_LFB_DrawPixel,
		&L2HAL_GC9A01_LFB_GetPixel,
		&L2HAL_GC9A01_LFB_PushFramebuffer,
		OffColor
	);

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

	/* Hardware JPEG decoder initialization */
	JpegCodecHandle.Instance = JPEG;
	LIBHWJPEG_Init(&JpegCodecHandle);

	mainTickHandlerCounter = 0;
	L2HAL_SysTick_RegisterHandler(&MainTickHandler);

	/* Mounting SD-card filesystem */
	if (!MountSdCardFs())
	{
		uint16_t width, height;
		FMGL_API_DrawRectangleFilled(&FmglContext, 0, 0, 239, 239, OffColor, OffColor);
		FMGL_API_RenderTextWithLineBreaks(&FmglContext, &font, 0, 112, &width, &height, false, "Failed to mount SD card!");
		FMGL_API_PushFramebuffer(&FmglContext);
		L2HAL_Error(Generic);
	}

	/* Loading animations */
	for (uint8_t frame = 0; frame < FRAMES_COUNT; frame++)
	{
		framebuffersAddresses[frame] = frame * L2HAL_GC9A01_LFB_FRAMEBUFFER_SIZE;

		char filename[32];
		sprintf(filename, "animation%d.jpeg", frame + 1);

		uint16_t width, height;
		char loadingMessage[32];
		sprintf(loadingMessage, "Loading %d / %d", frame + 1, FRAMES_COUNT);
		FMGL_API_DrawRectangleFilled(&FmglContext, 0, 0, 239, 239, OffColor, OffColor);
		FMGL_API_RenderTextWithLineBreaks(&FmglContext, &font, 0, 112, &width, &height, false, loadingMessage);
		FMGL_API_PushFramebuffer(&FmglContext);

		JpegDecodeToPsramBlocking(filename, framebuffersAddresses[frame]);
	}

	uint8_t frame = 0;

	/*fpsCounter = 0;*/

	while(true)
	{
		L2HAL_LY68L6400_QSPI_MemoryRead(&RamContext, framebuffersAddresses[frame], L2HAL_GC9A01_LFB_FRAMEBUFFER_SIZE, DisplayContext.Framebuffer);
		L2HAL_GC9A01_LFB_MarkFramebufferAsDirty(&DisplayContext);

		/*uint16_t width, height;
		FMGL_API_RenderTextWithLineBreaks(&FmglContext, &font, 0, 112, &width, &height, false, fpsMessage);*/

		FMGL_API_PushFramebuffer(&FmglContext);

		if (frame == FRAMES_COUNT - 1)
		{
			frame = 0;
		}
		else
		{
			frame ++;
		}

		/*fpsCounter ++;*/
	}
}

void MainTickHandler(void)
{
	if (mainTickHandlerCounter == 1000)
	{
		mainTickHandlerCounter = 0;

		/* Put code, called every second, here */

/*		sprintf(fpsMessage, "FPS: %d", fpsCounter);

		fpsCounter = 0;*/
	}
	else
	{
		mainTickHandlerCounter ++;
	}
}

#pragma GCC diagnostic pop
