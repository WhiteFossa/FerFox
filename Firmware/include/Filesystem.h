/*
 * Filesystem.h
 *
 *  Created on: Jul 17, 2023
 *      Author: fossa
 */

#ifndef INCLUDE_FILESYSTEM_H_
#define INCLUDE_FILESYSTEM_H_

#include <ffconf.h>
#include <ff.h>
#include <stdbool.h>
#include <stddef.h>
#include <pngle.h>

/**
 * Buffer size for PNG files load
 */
#define PNG_LOAD_BUFFER_SIZE 512

extern FATFS* SDCardFsPtr;
extern pngle_t* PngleContext;

/**
 * Attempt to mount SD-card filesystem
 * @return True if mount successful, false otherwise
 */
bool MountSDCardFS(void);

/**
 * Unmount previously-mounted SD-card filesystem. Do nothing in case if not mounted
 */
void UnmountSDCardFS(void);

/**
 * Load PNG file from given path
 * @param path File path on SD-card
 */
void LoadPngFromFile(const char* path);

#endif /* INCLUDE_FILESYSTEM_H_ */
