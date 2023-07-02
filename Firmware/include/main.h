/*
 * main.h
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#ifndef INCLUDE_MAIN_H_
#define INCLUDE_MAIN_H_

#include <stdbool.h>
#include <GlobalVariables.h>
#include <fmgl.h>

uint16_t fpsCounter;
uint16_t fpsHandlerCounter;
uint16_t fps;

FMGL_API_FontSettings font;

/**
 * FPS SysTick handler, used to calculate FPS
 */
void FpsHandler(void);

#endif /* INCLUDE_MAIN_H_ */
