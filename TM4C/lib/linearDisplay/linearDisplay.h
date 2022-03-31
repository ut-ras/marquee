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

#include <stdint.h>
#include <lib/segment/segment.h>
#include <lib/Timer/Timer.h>


typedef struct LinearDisplayConfig {
    uint8_t numSegments;
    ShifterConfig_t shifterConfig;
    GPIOPin_t rowPins[SEGMENT_ROWS];
    TimerConfig_t displayTimerConfig;
} LinearDisplayConfig_t;

typedef struct LinearDisplay {
    Segment_t* segments[];
    Timer_t displayTimer;
} LinearDisplay_t;

LinearDisplay_t LinearDisplayInit(void);

void LinearDisplayPushChar(LinearDisplay_t* display, char data);

void LinearDisplayPushString(LinearDisplay_t* display, char* data);

/* TODO: support for 12x48 images. */

void LinearDisplayClear(LinearDisplay_t* display);

void LinearDisplayStart(LinearDisplay_t* display);

void LinearDisplayStop(LinearDisplay_t* display);

void LinearDisplayChangeUpdateRate(LinearDisplay* display, uint32_t freq);
