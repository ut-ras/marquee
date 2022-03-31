/**
 * @file LinearDisplayExample.c
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief Example program demonstrating output to the marquee display in linear
 * display mode. 
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include <stdbool.h>

#include <lib/linearDisplay/linearDisplay.h>

/**
 * @brief 
 * 
 * @return int 
 */
int main(void) {
    ShifterConfig_t shifterConfig = {
        .clockPin=PIN_F0,
        .strobePin=PIN_F1,
        .outputEnablePin=PIN_F2,
        .dataPin=PIN_F3
    };

    GPIOPin_t rowPins[SEGMENT_ROWS] = {
        PIN_A0, // Row 1
        PIN_A1, // Row 2
        PIN_A2, // Row 3
        PIN_A3, // Row 4
        PIN_A4, // Row 5
        PIN_A0, // Row 6
        PIN_A1, // Row 7
        PIN_A2, // Row 8
        PIN_A3, // Row 9
        PIN_A4, // Row 10
        PIN_A0, // Row 11
        PIN_A1, // Row 12
        PIN_A2, // Row 13
        PIN_A3  // Row 14
    };

    TimerConfig_t timerConfig = {
        .timerID=TIMER_0A,
        .period=freqToPeriod(1, MAX_FREQ),
        .priority=5
    };

    LinearDisplayConfig_t displayConfig = {
        .numSegments=1,
        .shifterConfig=shifterConfig,
        .displayTimerConfig=timerConfig,
        .rowPins=rowPins
    };

    LinearDisplay_t LinearDisplayInit(displayConfig);

    while (true) {

    }

    return 1;
}