/**
 * @file SegmentExample.c
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief Example program demonstrating output an X to a single segment
 * of the marquee. 
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include <stdbool.h>

#include <lib/PLL/PLL.h>
#include <lib/segment/segment.h>
#include <lib/Timer/Timer.h>

/** 
 * These function declarations are defined in the startup.s assembly file for
 * managing interrupts. 
 */
void EnableInterrupts(void);    // Defined in startup.s
void DisableInterrupts(void);   // Defined in startup.s
void WaitForInterrupt(void);    // Defined in startup.s


static Segment_t segment;

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

    SegmentConfig_t segmentConfig = {
        .segmentID = 0,
        .shifterConfig=shifterConfig,
        .rowPins={
            PIN_A5, // Row 1
            PIN_A6, // Row 2
            PIN_D7, // Row 3
            PIN_D6, // Row 4
            PIN_A2, // Row 5
            PIN_A3, // Row 6
            PIN_A4, // Row 7
        },
        .timerID=TIMER_0A,
        .timerFreq=45
    };

    SegmentInit(segmentConfig, &segment);

    EnableInterrupts();

    SegmentStart(&segment);

    uint8_t x = 0;
    while (true) {
        SegmentSetPixel(&segment, 0, (x+0)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 1, (x+1)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 2, (x+2)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 3, (x+3)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 4, (x+4)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 5, (x+5)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 6, (x+6)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 6, (x+0)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 5, (x+1)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 4, (x+2)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 2, (x+4)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 1, (x+5)%SEGMENT_COLUMNS, 1);
        SegmentSetPixel(&segment, 0, (x+6)%SEGMENT_COLUMNS, 1);
        x = (x+1) % SEGMENT_COLUMNS;
        DelayMillisec(250);
        SegmentClear(&segment);
    }
}