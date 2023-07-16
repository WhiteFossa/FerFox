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
		uint32_t bytesRead;
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
