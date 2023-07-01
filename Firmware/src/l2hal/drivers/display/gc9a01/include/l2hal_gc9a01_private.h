/*
 * l2hal_gc9a01_private.h
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#ifndef L2HAL_DRIVERS_DISPLAY_GC9A01_INCLUDE_L2HAL_GC9A01_PRIVATE_H_
#define L2HAL_DRIVERS_DISPLAY_GC9A01_INCLUDE_L2HAL_GC9A01_PRIVATE_H_

#include <l2hal_mcu.h>
#include <stdint.h>

/**
 * Interval between CS and RESET signals during display reset
 */
#define L2HAL_GC9A01_CS_TO_RESET 5

/**
 * Reset signal duration
 */
#define L2HAL_GC9A01_RESET_DURATION 10


/**
 * Wait this time after reset before starting to send commands
 */
#define L2HAL_GC9A01_DISPLAY_BOOT_TIME 120

/**
 * Wait this time after exiting from sleepmode
 */
#define L2HAL_GC9A01_DISPLAY_SLEEP_OUT_TIME 120

/**
 * Wait this time after issuing "Display ON" command
 */
#define L2HAL_GC9A01_DISPLAY_AFTER_ON_TIME 20

/**
 * Throw fatal error if data transmit is not completed during this interval
 */
#define L2HAL_GC9A01_TRANSMIT_TIMEOUT 1000

/**
 * Display sizes
 */
#define L2HAL_GC9A01_DISPLAY_WIDTH 240
#define L2HAL_GC9A01_DISPLAY_HEIGHT 240


/**
 * Select / deselect chip
 */
void L2HAL_GC9A01_SelectChip(L2HAL_GC9A01_ContextStruct *context, bool isSelected);

/**
 * Send reset signal to display
 */
void L2HAL_GC9A01_ResetDisplay(L2HAL_GC9A01_ContextStruct *context);

/**
 * Write command to display
 */
void L2HAL_GC9A01_WriteCommand(L2HAL_GC9A01_ContextStruct *context, uint8_t command);

/**
 * Write data to display
 */
void L2HAL_GC9A01_WriteData(L2HAL_GC9A01_ContextStruct *context, uint8_t *data, uint16_t dataSize);

/**
 * Special case - send one byte of data to display (useful for initialization)
 */
void L2HAL_GC9A01_WriteByteData(L2HAL_GC9A01_ContextStruct *context, uint8_t byteData);

#endif /* L2HAL_DRIVERS_DISPLAY_GC9A01_INCLUDE_L2HAL_GC9A01_PRIVATE_H_ */
