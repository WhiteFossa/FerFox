/*
 * libhwjpeg.h
 *
 *  Created on: Jul 28, 2024
 *      Author: earlybeasts
 */

#ifndef LIBHWJPEG_LIBHWJPEG_H_
#define LIBHWJPEG_LIBHWJPEG_H_

#include <stm32f7xx_hal.h>
#include <l2hal_errors.h>
#include <stdint.h>
#include <ff.h>
#include <jpeg_utils.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Input buffer size
 */
#define LIBHWJPEG_IN_BUFFER_SIZE 768

/**
 * Output buffer size
 */
#define LIBHWJPEG_OUT_BUFFER_SIZE 768

/**
 * Pointer to codec
 */
static JPEG_HandleTypeDef* LIBHWJPEG_CodecPtr;

/**
 * File handler
 */
static FIL LIBHWJPEG_FileHandler;

/**
 * Input buffer
 */
static uint8_t LIBHWJPEG_InBuffer[LIBHWJPEG_IN_BUFFER_SIZE];

/**
 * Output buffer
 */
static uint8_t LIBHWJPEG_OutBuffer[LIBHWJPEG_OUT_BUFFER_SIZE];

/**
 * How many bytes are read already
 */
static uint32_t LIBHWJPEG_ReadBytes;

/**
 * Image width
 */
static uint32_t LIBHWJPEG_ImageWidth;

/**
 * Image height
 */
static uint32_t LIBHWJPEG_ImageHeight;

/**
 * Current X coordinate
 */
static uint16_t LIBHWJPEG_CurrentX;

/**
 * Current Y coordinate
 */
static uint16_t LIBHWJPEG_CurrentY;

/**
 * YCbCr -> RGB conversion function
 */
static JPEG_YCbCrToRGB_Convert_Function LIBHWJPEG_YCbCrToRgbFunction;

/**
 * MCUs count
 */
static uint32_t LIBHWJPEG_McusCount;

/**
 * Current MCU
 */
static uint32_t LIBHWJPEG_CurrentMcu;

/**
 * Resulted image buffer. Malloc'd by the library, must be free by user
 */
static uint8_t* LIBHWJPEG_ResultBuffer;

/**
 * Setting it to true when decoding is complete
 */
static bool* LIBHWJPEG_IsReadyPtr;

/**
 * Pointer to arbitrary data, fed to completion handler
 */
static void* LIBHWJPEG_ResultArbitraryDataPtr;

/**
 * Called when image decoded
 * @param Pointer to image width
 * @param Pointer to image height
 * @param Pointer to image buffer (RGB)
 * @param Pointer to arbitrary data
 */
static void (*LIBHWJPEG_CompletionHandler)(uint16_t*, uint16_t*, uint8_t*, void*);

/**
 * Initialize library
 */
void LIBHWJPEG_Init(JPEG_HandleTypeDef* codec);

/**
 * Decode JPEG file
 */
void LIBHWJPEG_DecodeFile
(
	const char* path,
	void (*completionHandler)(uint16_t*, uint16_t*, uint8_t*, void*),
	bool* isReadyPtr,
	void* arbitraryDataPtr
);

/**
 * Private function - read file
 */
void LIBHWJPEG_Private_FileRead(uint32_t startPosition);



#endif /* LIBHWJPEG_LIBHWJPEG_H_ */
