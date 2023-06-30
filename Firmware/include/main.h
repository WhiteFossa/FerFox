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

/**
 * Draws background text with given font.
 * @param fontSettings Pointer to font settings.
 */
void DrawBackgroundText(FMGL_API_FontSettings* fontSettings);

#endif /* INCLUDE_MAIN_H_ */
