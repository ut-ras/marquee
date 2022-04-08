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
#include <stdlib.h>

#include <lib/linearDisplay/linearDisplay.h>
#include <lib/PLL/PLL.h>
#include <lib/Timer/Timer.h>

/** 
 * These function declarations are defined in the startup.s assembly file for
 * managing interrupts. 
 */
void EnableInterrupts(void);    // Defined in startup.s
void DisableInterrupts(void);   // Defined in startup.s
void WaitForInterrupt(void);    // Defined in startup.s
void SegmentPublish(uint32_t* args);

static LinearDisplay_t display;

int main(void) {
    PLLInit(BUS_80_MHZ);
    DisableInterrupts();
    DelayInit();
    
    ShifterConfig_t shifterConfig = {
        .clockPin=PIN_E0,
        .strobePin=PIN_B2,
        .outputEnablePin=PIN_B5, // HW FORCED HIGH
        .dataPin=PIN_B7
    };

    LinearDisplayConfig_t displayConfig = {
        .numSegments=1,
        .shifterConfig=shifterConfig,
        .timerId=TIMER_0A,
        .rowPins={
            PIN_A5, // Row 1
            PIN_A6, // Row 2
            PIN_D7, // Row 3
            PIN_D6, // Row 4
            PIN_A2, // Row 5
            PIN_A3, // Row 6
            PIN_A4, // Row 7
        }
    };

    LinearDisplayInit(displayConfig, &display);

    LinearDisplayPushString(&display, "HELLOWORLD", 10);


    EnableInterrupts();
    //LinearDisplayStart(&display);

    while (true) {
        SegmentPublish((uint32_t*)&(display.segment));
        DelayMicrosec(100);
    }

    return 1;
}