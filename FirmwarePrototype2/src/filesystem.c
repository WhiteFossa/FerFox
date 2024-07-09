/*
 * filesystem.c
 *
 *  Created on: Jul 8, 2024
 *      Author: earlybeasts
 */

#include <filesystem.h>

bool MountSdCardFs(void)
{
	SdFsPtr = malloc(sizeof(FATFS));
	FRESULT fResult = f_mount(SdFsPtr, "0", 1);

	if (FR_OK == fResult)
	{
		return true;
	}

	free(SdFsPtr);
	SdFsPtr = NULL;

	return false;
}


void UnmountSdCardFs(void)
{
	if (NULL == SdFsPtr)
	{
		return;
	}

	f_unmount("0");

	free(SdFsPtr);
	SdFsPtr = NULL;
}
