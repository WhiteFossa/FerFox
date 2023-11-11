
// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include <main.h>
#include <HAL.h>
#include <terminusRegular12.h>

int main(int argc, char* argv[])
{
	/* Mandatory for STM32 HAL */
	HAL_Init();

	/* Our hardware */
	L2HAL_Init();
	HAL_IntiHardware();

	/* RAM initialization */
	L2HAL_LY68L6400_Init
	(
		&RamContext,
		&SPI2Handle,

		HAL_PSRAM_CS_PORT,
		HAL_PSRAM_CS_PIN
	);

	/* CRC calculation unit initialization */
	CRC_Context = L2HAL_CRC_Init();

	/* Display driver initialization */
	L2HAL_GC9A01_Init
	(
		&DisplayContext,
		&SPI2Handle,

		HAL_DISPLAY_RESET_PORT,
		HAL_DISPLAY_RESET_PIN,

		HAL_DISPLAY_DC_PORT,
		HAL_DISPLAY_DC_PIN,

		HAL_DISPLAY_CS_PORT,
		HAL_DISPLAY_CS_PIN,

		ROTATION_180,

		&RamContext,
		&L2HAL_LY68L6400_MemoryWrite,
		&L2HAL_LY68L6400_MemoryRead,

		L2HAL_GC9A01_DIRTY_PIXELS_BUFFER_SIZE,

		0,

		&CRC_Context
	);

	HAL_SetBacklightLevel(HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD); /* Full brightness */

	/* SD Card driver initialization */
	enum L2HAL_SDCard_InitResult sdCardInitResult = L2HAL_SDCard_Init
	(
		&SDCardContext,
		&SPI1Handle,

		HAL_SDCARD_CS_PORT,
		HAL_SDCARD_CS_PIN
	);

	if (NoCardInserted == sdCardInitResult)
	{
		L2HAL_Error(Generic); /* TODO: Show "Insert SD-card" message */
	}
	else if (Success != sdCardInitResult)
	{
		L2HAL_Error(Generic); /* Failed to initialize SD-card */
	}


	FMGL_API_ColorStruct OffColor;
	OffColor.R = 0;
	OffColor.G = 0;
	OffColor.B = 0;

	/* Attaching FMGL to display */
	FmglContext = FMGL_API_AttachToDriver
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

	/* Setting up PNGLE */
	PngleContext = pngle_new();
	pngle_set_draw_callback(PngleContext, PngleOnDraw);

	/* Mounting SD-card filesystem */
	if (!MountSDCardFS())
	{
		/* TODO: Offer to format SD-card*/
		L2HAL_Error(Generic);
	}

	/* Loading animations */
	for (uint8_t frame = 0; frame < FRAMES_COUNT; frame++)
	{
		framebuffersAddresses[frame] = frame * L2HAL_GC9A01_FRAMEBUFFER_SIZE + L2HAL_GC9A01_DIRTY_PIXELS_BUFFER_SIZE;

		L2HAL_GC9A01_SetFramebufferBaseAddress(&DisplayContext, framebuffersAddresses[frame]);

		char filename[32];
		sprintf(filename, "animation%d.jpeg", frame + 1);
		LoadJpegFromFile(filename);
	}

//	L2HAL_GC9A01_SetFramebufferBaseAddress(&DisplayContext, 1000000);
//	LoadJpegFromFile("image.jpeg");

	sprintf(fpsMessageBuffer, "Wait...");

	uint8_t frame = 0;
	while(true)
	{
		L2HAL_GC9A01_SetFramebufferBaseAddress(&DisplayContext, framebuffersAddresses[frame]);

		/* Drawing FPS */
		uint16_t width, height;
		FMGL_API_RenderTextWithLineBreaks(&FmglContext, &font, 0, 112, &width, &height, false, fpsMessageBuffer);

		/* Pushing framebuffer */
		FMGL_API_PushFramebuffer(&FmglContext);

		if (frame == FRAMES_COUNT - 1)
		{
			frame = 0;
		}
		else
		{
			frame ++;
		}

		fpsCounter ++;
	}
}

void PngleOnDraw(pngle_t *pngle, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t rgba[4])
{
	FMGL_API_ColorStruct color;
	color.R = rgba[0];
	color.G = rgba[1];
	color.B = rgba[2];

	FMGL_API_SetActiveColor(&FmglContext, color);
	FMGL_API_DrawPixel(&FmglContext, (uint16_t)x, (uint16_t)y);
}

void FpsHandler(void)
{
	fpsHandlerCounter ++;

	if (fpsHandlerCounter == 10000)
	{
		fps = fpsCounter;
		fpsCounter = 0;
		fpsHandlerCounter = 0;

		sprintf(fpsMessageBuffer, "FPS:%.1f", fps / 10.0f);
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
