/**
 * @file linearDisplay.h
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief This linear driver display takes in some sort of preformatted input
 * (say, characters, or 12 pixel tall images), and displays it onto the marquee.
 * This particular configuration is multiple segments combined in series,
 * sharing the same shifter config pins.
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <stdint.h>
#include <lib/segment/segment.h>
#include <lib/Timer/Timer.h>


/**
 * @brief Struct defining the configuration of a linear static display.
 */
typedef struct LinearDisplayConfig {
    /* Number of segments to display. */
    uint8_t numSegments;

    /* Pin configuration for the shifter. */
    ShifterConfig_t shifterConfig;

    /* Timer configuration for updating the display. */
    TimerID_t timerId;

    /* Pin configuration for rows. */
    GPIOPin_t rowPins[SEGMENT_ROWS];
} LinearDisplayConfig_t;

typedef struct LinearDisplay {
    /* Segment to display. */
    Segment_t segment;

    /* Timer controlling display operation. */
    Timer_t displayTimer;
} LinearDisplay_t;

/**
 * @brief 
 * 
 * @param config 
 */
void LinearDisplayInit(LinearDisplayConfig_t config, LinearDisplay_t* display);

/**
 * @brief 
 * 
 * @param display 
 * @param data 
 */
void LinearDisplayPushChar(LinearDisplay_t* display, char data, uint8_t offShift);

void LinearDisplayPushString(LinearDisplay_t* display, char* data, uint8_t size);

//void LinearDisplayPushEmoji(LinearDisplay_t* display, enum Emoji emoji);
/* TODO: support for 12x48 images. */

void LinearDisplayClear(LinearDisplay_t* display);

void LinearDisplayStart(LinearDisplay_t* display);

void LinearDisplayStop(LinearDisplay_t* display);

void LinearDisplayChangeUpdateRate(LinearDisplay_t* display, uint32_t freq);
