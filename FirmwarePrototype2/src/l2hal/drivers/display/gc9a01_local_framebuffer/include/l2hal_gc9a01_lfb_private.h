/*
 * L2HAL_GC9A01_LFB_lfb_private.h
 *
 *  Created on: Jul 4, 2024
 *      Author: earlybeasts
 */

#ifndef L2HAL_DRIVERS_DISPLAY_GC9A01_LOCAL_FRAMEBUFFER_INCLUDE_L2HAL_GC9A01_LFB_LFB_PRIVATE_H_
#define L2HAL_DRIVERS_DISPLAY_GC9A01_LOCAL_FRAMEBUFFER_INCLUDE_L2HAL_GC9A01_LFB_LFB_PRIVATE_H_

#include <l2hal_mcu.h>
#include <stdint.h>

/**
 * Interval between CS and RESET signals during display reset
 */
#define L2HAL_GC9A01_LFB_CS_TO_RESET 5

/**
 * Reset signal duration
 */
#define L2HAL_GC9A01_LFB_RESET_DURATION 10


/**
 * Wait this time after reset before starting to send commands
 */
#define L2HAL_GC9A01_LFB_DISPLAY_BOOT_TIME 120

/**
 * Wait this time after exiting from sleepmode
 */
#define L2HAL_GC9A01_LFB_DISPLAY_SLEEP_OUT_TIME 120

/**
 * Wait this time after issuing "Display ON" command
 */
#define L2HAL_GC9A01_LFB_DISPLAY_AFTER_ON_TIME 20

/**
 * Select / deselect chip
 */
void L2HAL_GC9A01_LFB_SelectChip(L2HAL_GC9A01_LFB_ContextStruct *context, bool isSelected);

/**
 * Send reset signal to display
 */
void L2HAL_GC9A01_LFB_ResetDisplay(L2HAL_GC9A01_LFB_ContextStruct *context);

/**
 * Write command to display
 */
void L2HAL_GC9A01_LFB_WriteCommand(L2HAL_GC9A01_LFB_ContextStruct *context, uint8_t command);

/**
 * Write data to display
 */
void L2HAL_GC9A01_LFB_WriteData(L2HAL_GC9A01_LFB_ContextStruct *context, uint8_t *data, uint16_t dataSize);

/**
 * Special case - send one byte of data to display (useful for initialization)
 */
void L2HAL_GC9A01_LFB_WriteByteData(L2HAL_GC9A01_LFB_ContextStruct *context, uint8_t byteData);

/**
 * Hang till the DMA transfer completed
 */
void L2HAL_GC9A01_LFB_WaitForDataTransferCompletion(L2HAL_GC9A01_LFB_ContextStruct *context);


#endif /* L2HAL_DRIVERS_DISPLAY_GC9A01_LOCAL_FRAMEBUFFER_INCLUDE_L2HAL_GC9A01_LFB_LFB_PRIVATE_H_ */
