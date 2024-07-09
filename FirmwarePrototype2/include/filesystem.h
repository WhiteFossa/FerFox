/*
 * filesystem.h
 *
 *  Created on: Jul 8, 2024
 *      Author: earlybeasts
 */

#ifndef INCLUDE_FILESYSTEM_H_
#define INCLUDE_FILESYSTEM_H_

#include <ffconf.h>
#include <ff.h>
#include <stdbool.h>
#include <stdlib.h>

extern FATFS* SdFsPtr;

/**
 * Attempt to mount SD-card filesystem
 * @return True if mount successful, false otherwise
 */
bool MountSdCardFs(void);

/**
 * Unmount previously-mounted SD-card filesystem. Do nothing in case if not mounted
 */
void UnmountSdCardFs(void);


#endif /* INCLUDE_FILESYSTEM_H_ */
