/**
 * @file tom-thumb_font.h
 * @author Matthew Yu
 * @brief Character encoding mapping for the IEEE RAS demobots.
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 */
#pragma once

#include <stdint.h>

#define CHAR_WIDTH 4
#define CHAR_HEIGHT 6
#define CHAR_SIZE (CHAR_WIDTH / 8) + 1 // in terms of bytes.
#define NUM_CHARS 95

extern char mapping[NUM_CHARS];
extern char bitmap[NUM_CHARS][CHAR_HEIGHT];
