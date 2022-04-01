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

#include <lib/segment/segment.h>

static Segment_t segment;

/**
 * @brief 
 * 
 * @return int 
 */
int main(void) {
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
        }
    };

    segment = SegmentInit(segmentConfig);
    uint8_t xDims = 5;
    for (uint8_t i = 0; i < xDims; ++i) {
            SegmentSetPixel(&segment, i, i, 1);
            SegmentSetPixel(&segment, i, xDims-i, 1);
    }
    SegmentPublish(&segment);

    while (true) {
        
    }
    return 1;
}