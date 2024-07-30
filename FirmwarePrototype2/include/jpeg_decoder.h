/*
 * jpeg_decoder.h
 *
 *  Created on: Jul 8, 2024
 *      Author: earlybeasts
 */

#ifndef INCLUDE_JPEG_DECODER_H_
#define INCLUDE_JPEG_DECODER_H_

#include <stdint.h>
#include <libhwjpeg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <l2hal.h>
#include <l2hal_ly68l6400_qspi.h>

extern L2HAL_LY68L6400_QSPI_ContextStruct RamContext;

static uint16_t JpegWidth;
static uint16_t JpegHeight;
static uint8_t* JpegImageDataPtr;

/**
 * Decode image to PSRAM
 */
void JpegDecodeToPsramBlocking(char* path, uint32_t targetAddress);

/**
 * Decode image to PSRAM completion handler
 */
void OnJpegDecodeToPsramBlockingCompleted(uint16_t* widthPtr, uint16_t* heightPtr, uint8_t* imagePtr, void* arbitraryDataPtr);


#endif /* INCLUDE_JPEG_DECODER_H_ */
