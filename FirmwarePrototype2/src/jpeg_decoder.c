/*
 * jpeg_decoder.c
 *
 *  Created on: Jul 8, 2024
 *      Author: earlybeasts
 */

#include <jpeg_decoder.h>

void JpegDecodeToPsramBlocking(char* path, uint32_t targetAddress)
{
	volatile bool isReady = false;

	LIBHWJPEG_DecodeFile(path, &OnJpegDecodeToPsramBlockingCompleted, &isReady, NULL);

	while (!isReady) { }

	L2HAL_LY68L6400_QSPI_MemoryWrite(&RamContext, targetAddress, JpegWidth * JpegHeight * 3, JpegImageDataPtr);

	free(JpegImageDataPtr);
	JpegImageDataPtr = NULL;
}

void OnJpegDecodeToPsramBlockingCompleted(uint16_t* widthPtr, uint16_t* heightPtr, uint8_t* imagePtr, void* arbitraryDataPtr)
{
	JpegWidth = *widthPtr;
	JpegHeight = *heightPtr;
	JpegImageDataPtr = imagePtr;
}
