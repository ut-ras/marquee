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

    SegmentConfig_t segmentConfig = {
        .segmentID = 0,
        .shifterConfig=shifterConfig,
        .rowPins={
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
        }
    };

    Segment_t segment = SegmentInit(segmentConfig);
    uint8_t xDims = 5;
    for (uint8_t i = 0; i < xDims; ++i) {
        for (uint8_t j = 0; j < xDims; ++j) {
            SegmentSetPixel(&segment, i, j, 1);
            SegmentSetPixel(&segment, i, xDims-j, 1);
        }
    }
    SegmentPublish(&segment);

    while (true);
    return 1;
}