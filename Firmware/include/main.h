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
#include <pngle.h>
#include <Filesystem.h>
#include <stdio.h>

#define FRAMES_COUNT 16

uint16_t fpsCounter;
uint16_t fpsHandlerCounter;
uint16_t fps;
char fpsMessageBuffer[32];

FMGL_API_FontSettings font;

uint32_t framebuffersAddresses[FRAMES_COUNT];

/**
 * Called by PNGLE to draw next pixel
 */
void PngleOnDraw(pngle_t *pngle, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t rgba[4]);

/**
 * FPS SysTick handler, used to calculate FPS
 */
void FpsHandler(void);

#endif /* INCLUDE_MAIN_H_ */
