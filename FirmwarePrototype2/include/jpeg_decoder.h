/*
 * jpeg_decoder.h
 *
 *  Created on: Jul 8, 2024
 *      Author: earlybeasts
 */

#ifndef INCLUDE_JPEG_DECODER_H_
#define INCLUDE_JPEG_DECODER_H_

#include <stddef.h>
#include <stdint.h>
#include <tjpgdcnf.h>
#include <tjpgd.h>
#include <fmgl.h>
#include <filesystem.h>

extern FMGL_API_DriverContext FmglContext;
extern FATFS* SdFsPtr;

/**
 * Internal buffer size for JPEG decoder
 */
#define JPEG_WORKSPACE_SIZE 3092

/**
 * Structure with information on JPEG decoding session
 */
typedef struct
{
	FIL* FilePtr; /* We read JPEG from this file */
}
JpegDecoderSessionStruct;

/**
 * Function, reading JPEG-data from file
 * @param jdec JPEG decoder object
 * @param buff Buffer to store data here
 * @param ndata How much bytes we need to store
 * @return How much bytes were read
 */
size_t JpegInputFunction(JDEC* jdec, uint8_t* buff, size_t ndata);

/**
 * Function to write JPEG pixels to framebuffer
 * @param jdec JPEG decoder object
 * @param bitmap Pixels to write
 * @param rect Rectangle within image with bitmap
 * @return 1 to continue, 0 to abort
 */
int JpegOutputFunction (JDEC* jdec, void* bitmap, JRECT* rect);

/**
 * Load JPEG file from given path
 * @param path File path on SD-card
 */
void LoadJpegFromFile(const char* path);



#endif /* INCLUDE_JPEG_DECODER_H_ */
