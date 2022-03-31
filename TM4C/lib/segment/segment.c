/**
 * @file segment.c
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief Implementation of the segment driver.
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <lib/segment/segment.h>
#include <lib/shifter/shifter.h>

Segment_t SegmentInit(SegmentConfig_t config) {
    Segment_t segment = {
        .segmentID  = config.segmentID,
        .shifter    = ShifterInit(config.shifterConfig),
        .rowPins    = { PIN_COUNT },
        .state      = { false }
    };

    /* Initialize GPIO pins as digital outputs. */
    GPIOConfig_t pinConfig = {
        .pin=PIN_COUNT,
        .pull=GPIO_PULL_DOWN,
        .isOutput=true
    };

    for (uint8_t i = 0; i < SEGMENT_ROWS; ++i) {
        segment.rowPins[i] = config.rowPins[i];
        pinConfig.pin = config.rowPins[i];
        GPIOInit(pinConfig);
    }

    return segment;
}

void SegmentSetPixel(Segment_t* seg, uint8_t row, uint8_t column, bool state) {
    seg->state[row][column] = state;
}

void SegmentClear(Segment_t* seg) {
    for (uint8_t i = 0; i < SEGMENT_ROWS; ++i) {
        for (uint8_t j = 0; j < SEGMENT_COLUMNS; ++j) {
            seg->state[i][j] = false;
        }
    }
}

void SegmentPublish(Segment_t* seg) {
    /* Collapse rows into one "row". */
    bool columns[SEGMENT_COLUMNS] = { false };
    for (uint8_t col = 0; col < SEGMENT_COLUMNS; ++col) {
        for (uint8_t row = 0; row < SEGMENT_ROWS; ++row) {
            if (seg->state[row][col]) {
                columns[col] = true;
                break;
            }
        }
    }

    /* Shift columns into the HCF4094BE. */
    uint64_t shiftData = 0;
    for (uint8_t i = 0; i < SEGMENT_COLUMNS && i < 64; ++i) {
        shiftData |= columns[i] << i;
    }

    /* Shift bits down the segment. */
    ShifterShiftInMulti(&seg->shifter, shiftData, SEGMENT_COLUMNS);

    /* Collapse columns into one "column". */
    bool rows[SEGMENT_ROWS] = { false };
    for (uint8_t row = 0; row < SEGMENT_ROWS; ++row) {
        for (uint8_t col = 0; col < SEGMENT_COLUMNS; ++col) {
            if (seg->state[row][col]) {
                rows[row] = true;
                break;
            }
        }
    }

    /* Turn on relevant row MOSFETs. */
    for (uint8_t i = 0; i < SEGMENT_ROWS; ++i) {
        GPIOSetBit(seg->rowPins[i], rows[i]);
    }
}
