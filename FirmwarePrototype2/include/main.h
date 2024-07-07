/*
 * main.h
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#ifndef INCLUDE_MAIN_H_
#define INCLUDE_MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "diag/trace.h"

#include <hal.h>
#include <global_variables.h>

#include <l2hal_gc9a01.h>
#include <l2hal_ly68l6400_qspi.h>

#include <fmgl.h>
#include <terminusRegular12.h>

FMGL_API_FontSettings font;

uint32_t mainTickHandlerCounter;

uint32_t sdcardBlockAddress;
uint32_t sdcardBytesRead;

void MainTickHandler(void);

#endif /* INCLUDE_MAIN_H_ */
