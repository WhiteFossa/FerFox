/*
 * libhwjpeg.c
 *
 *  Created on: Jul 28, 2024
 *      Author: earlybeasts
 */

#include <libhwjpeg.h>

void LIBHWJPEG_Init(JPEG_HandleTypeDef* codec)
{
	LIBHWJPEG_CodecPtr = codec;

	JPEG_InitColorTables();

	HAL_JPEG_Init(LIBHWJPEG_CodecPtr);
}

void LIBHWJPEG_DecodeFile
(
	const char* path,
	FMGL_API_DriverContext* fmglContextPtr,
	void (*completionHandler)(uint16_t, uint16_t, uint8_t*, void*),
	void* arbitraryDataPtr
)
{
	LIBHWJPEG_ReadBytes = 0;
	LIBHWJPEG_CurrentX = 0;
	LIBHWJPEG_CurrentY = 0;
	LIBHWJPEG_CurrentMcu = 0;
	LIBHWJPEG_FmglContextPtr = fmglContextPtr;
	LIBHWJPEG_CompletionHandler = completionHandler;
	LIBHWJPEG_ResultArbitraryDataPtr = arbitraryDataPtr;

	FRESULT fResult = f_open(&LIBHWJPEG_FileHandler, path, FA_READ);
	if (fResult != FR_OK)
	{
		L2HAL_Error(Generic);
	}

	/* First read */
	LIBHWJPEG_Private_FileRead(0);

	if (HAL_OK != HAL_JPEG_Decode(LIBHWJPEG_CodecPtr, LIBHWJPEG_InBuffer, LIBHWJPEG_IN_BUFFER_SIZE, LIBHWJPEG_OutBuffer, LIBHWJPEG_OUT_BUFFER_SIZE, 1000))
	{
		L2HAL_Error(Generic);
	}
}


void LIBHWJPEG_Private_FileRead(uint32_t startPosition)
{
	if (FR_OK != f_lseek(&LIBHWJPEG_FileHandler, startPosition))
	{
		L2HAL_Error(Generic);
	}

	size_t bytesRead;
	FRESULT fResult = f_read(&LIBHWJPEG_FileHandler, LIBHWJPEG_InBuffer, LIBHWJPEG_IN_BUFFER_SIZE, &bytesRead);
	if (fResult != FR_OK)
	{
		L2HAL_Error(Generic);
	}
}

void HAL_JPEG_InfoReadyCallback(JPEG_HandleTypeDef *hjpeg, JPEG_ConfTypeDef *pInfo)
{
	if (JPEG_420_SUBSAMPLING == pInfo->ChromaSubsampling)
	{
		if ((pInfo->ImageWidth % 16) != 0)
		{
			pInfo->ImageWidth += (16 - (pInfo->ImageWidth % 16));
		}

		if ((pInfo->ImageHeight % 16) != 0)
		{
			pInfo->ImageHeight += (16 - (pInfo->ImageHeight % 16));
		}
	}

	if (JPEG_422_SUBSAMPLING == pInfo->ChromaSubsampling)
	{
		if ((pInfo->ImageWidth % 16) != 0)
		{
			pInfo->ImageWidth += (16 - (pInfo->ImageWidth % 16));
		}

		if ((pInfo->ImageHeight % 8) != 0)
		{
			pInfo->ImageHeight += (8 - (pInfo->ImageHeight % 8));
		}
	}

	if (JPEG_444_SUBSAMPLING == pInfo->ChromaSubsampling)
	{
		if ((pInfo->ImageWidth % 8) != 0)
		{
			pInfo->ImageWidth += (8 - (pInfo->ImageWidth % 8));
		}

		if ((pInfo->ImageHeight % 8) != 0)
		{
			pInfo->ImageHeight += (8 - (pInfo->ImageHeight % 8));
		}
	}

	LIBHWJPEG_ImageWidth = pInfo->ImageWidth;
	LIBHWJPEG_ImageHeight = pInfo->ImageHeight;

	LIBHWJPEG_ResultBuffer = malloc(LIBHWJPEG_ImageWidth * LIBHWJPEG_ImageHeight * 3);

	if (HAL_OK != JPEG_GetDecodeColorConvertFunc(pInfo, &LIBHWJPEG_YCbCrToRgbFunction, &LIBHWJPEG_McusCount))
	{
		L2HAL_Error(Generic);
	}
}

void HAL_JPEG_GetDataCallback(JPEG_HandleTypeDef *hjpeg, uint32_t NbDecodedData)
{
	LIBHWJPEG_ReadBytes += NbDecodedData;

	LIBHWJPEG_Private_FileRead(LIBHWJPEG_ReadBytes);

	HAL_JPEG_ConfigInputBuffer(hjpeg, LIBHWJPEG_InBuffer, LIBHWJPEG_IN_BUFFER_SIZE);
}

void HAL_JPEG_DataReadyCallback(JPEG_HandleTypeDef *hjpeg, uint8_t *pDataOut, uint32_t OutDataLength)
{
	uint32_t convertedBytesCount;
	LIBHWJPEG_CurrentMcu += LIBHWJPEG_YCbCrToRgbFunction(pDataOut, LIBHWJPEG_ResultBuffer, LIBHWJPEG_CurrentMcu, OutDataLength, &convertedBytesCount);

	HAL_JPEG_ConfigOutputBuffer(hjpeg, LIBHWJPEG_OutBuffer, LIBHWJPEG_OUT_BUFFER_SIZE);
}

void HAL_JPEG_DecodeCpltCallback(JPEG_HandleTypeDef *hjpeg)
{
	if (FR_OK != f_close(&LIBHWJPEG_FileHandler))
	{
		L2HAL_Error(Generic);
	}

	LIBHWJPEG_CompletionHandler(LIBHWJPEG_ImageWidth, LIBHWJPEG_ImageHeight, LIBHWJPEG_ResultBuffer, LIBHWJPEG_ResultArbitraryDataPtr);
}

void HAL_JPEG_ErrorCallback(JPEG_HandleTypeDef *hjpeg)
{
	L2HAL_Error(Generic);
}
