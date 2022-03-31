/**
 * @file wrappingLinearDisplay.h
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief This linear driver display takes in some sort of preformatted input
 * (say, characters, or 12 pixel tall images), and displays it onto the marquee.
 * This particular configuration is multiple segments combined in series,
 * sharing the same shifter config pins. 
 * 
 * Text wraps around this display until overwritten. 
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include <lib/segment/segment.h>


typedef struct WrappingLinearDisplayConfig {
    uint8_t numSegments;
    ShifterConfig_t shifterConfig;
    GPIOPin_t rowPins[SEGMENT_ROWS];
} WrappingLinearDisplayConfig_t;

typedef struct WrappingLinearDisplay {
    Segment_t* segments[];
} WrappingLinearDisplay_t;

WrappingLinearDisplay_t WrappingLinearDisplayInit(void);
