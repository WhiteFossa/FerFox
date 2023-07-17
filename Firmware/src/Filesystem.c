/*
 * Filesystem.c
 *
 *  Created on: Jul 17, 2023
 *      Author: fossa
 */

#include <Filesystem.h>
#include <stddef.h>
#include <stdlib.h>
#include <l2hal_errors.h>
#include <pngle.h>

bool MountSDCardFS(void)
{
	SDCardFsPtr = malloc(sizeof(FATFS));
	FRESULT fResult = f_mount(SDCardFsPtr, "0", 1);

	if (FR_OK == fResult)
	{
		return true;
	}

	free(SDCardFsPtr);
	SDCardFsPtr = NULL;

	return false;
}


void UnmountSDCardFS(void)
{
	if (NULL == SDCardFsPtr)
	{
		return;
	}

	f_unmount("0");

	free(SDCardFsPtr);
	SDCardFsPtr = NULL;
}

void LoadPngFromFile(const char* path)
{
	FIL file;
	FRESULT fResult = f_open(&file, path, FA_READ);
	if (fResult != FR_OK)
	{
		L2HAL_Error(Generic);
	}

	/* File opened */
	uint32_t imageSize = f_size(&file);

	/* Preparing to read image from SD-card */
	uint8_t fileBuffer[PNG_LOAD_BUFFER_SIZE];

	/* Begin of PNG drawing */
	uint32_t blockNumber = 0;
	uint32_t fed = 0;
	while (fed < imageSize)
	{
		size_t bytesRead;
		fResult = f_read(&file, fileBuffer, PNG_LOAD_BUFFER_SIZE, &bytesRead);
		if (fResult != FR_OK)
		{
			L2HAL_Error(Generic);
		}

		fed += pngle_feed(PngleContext, fileBuffer, bytesRead);

		blockNumber ++;
	}
	/* End of PNG drawing */

	fResult = f_close(&file);
	if (fResult != FR_OK)
	{
		L2HAL_Error(Generic);
	}
}

size_t JpegInputFunction(JDEC* jdec, uint8_t* buff, size_t ndata)
{
	FIL* filePtr = ((JpegDecoderSessionStruct*)jdec->device)->FilePtr;

	size_t bytesRead;
	FRESULT fResult = f_read(filePtr, buff, ndata, &bytesRead);
	if (fResult != FR_OK)
	{
		L2HAL_Error(Generic);
	}

	return bytesRead;
}

int JpegOutputFunction (JDEC* jdec, void* bitmap, JRECT* rect)
{
	FMGL_API_ColorStruct color;
	uint16_t bitmapX, bitmapY;
	uint16_t width = (rect->right - rect->left) + 1;
	for (uint16_t y = rect->top; y <= rect->bottom; y++)
	{
		bitmapY = y - rect->top;

		for (uint16_t x = rect->left; x <= rect->right; x++)
		{
			bitmapX = x - rect->left;

			color = ((FMGL_API_ColorStruct*)bitmap)[bitmapY * width + bitmapX];

			FMGL_API_SetActiveColor(&FmglContext, color);
			FMGL_API_DrawPixel(&FmglContext, (uint16_t)x, (uint16_t)y);
		}
	}

	return 1;
}

void LoadJpegFromFile(const char* path)
{
	FIL file;
	JpegDecoderSessionStruct session;
	session.FilePtr = &file;

	JDEC decoder = {0};

	FRESULT fResult = f_open(session.FilePtr, path, FA_READ);
	if (fResult != FR_OK)
	{
		L2HAL_Error(Generic);
	}

	uint8_t workArea[JPEG_WORKSPACE_SIZE];
	if (JDR_OK != jd_prepare(&decoder, JpegInputFunction, workArea, JPEG_WORKSPACE_SIZE, &session))
	{
		L2HAL_Error(Generic);
	}

	if (JDR_OK != jd_decomp(&decoder, JpegOutputFunction, 0))
	{
		L2HAL_Error(Generic);
	}

	fResult = f_close(session.FilePtr);
	if (fResult != FR_OK)
	{
		L2HAL_Error(Generic);
	}
}

