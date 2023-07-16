/*
 * l2hal_sdcard_private.h
 *
 *  Created on: Jul 15, 2023
 *      Author: fossa
 */

#ifndef L2HAL_DRIVERS_SDCARD_INCLUDE_L2HAL_SDCARD_PRIVATE_H_
#define L2HAL_DRIVERS_SDCARD_INCLUDE_L2HAL_SDCARD_PRIVATE_H_

#include <l2hal_mcu.h>
#include <l2hal_sdcard.h>
#include <stdbool.h>

/**
 * Select / deselect sdcard
 */
void L2HAL_SDCard_Select(L2HAL_SDCard_ContextStruct *context, bool isSelected);


/**
 * Send data to SD-card WITHOUT control of CS
 * @param context SD-card context
 * @param data Data to send
 * @param dataSize Data size
 */
void L2HAL_SDCard_WriteDataNoCSControl(L2HAL_SDCard_ContextStruct *context, uint8_t *data, uint16_t dataSize);


/**
 * Read data from SD-card into buffer
 * @param context SD-card context
 * @param buffer Data will be read here
 * @param readSize How much data to read
 */
void L2HAL_SDCard_ReadData(L2HAL_SDCard_ContextStruct *context, uint8_t *buffer, uint16_t readSize);

/**
 * Wait for BUSY flag cleared
 * @param context SD-card context
 */
void L2HAL_SDCard_WaitForBusyCleared(L2HAL_SDCard_ContextStruct *context);


/**
 * Read SD-card R1 answer
 * @param context SD-card context
 * @return R1 data
 */
uint8_t L2HAL_SDCard_ReadR1(L2HAL_SDCard_ContextStruct *context);

#endif /* L2HAL_DRIVERS_SDCARD_INCLUDE_L2HAL_SDCARD_PRIVATE_H_ */
