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

/**
 * @brief SegmentPublish Publishes the virtual segment state data to a physical
 * segment of the marquee. This shifts data into the HCF4094BE shift registers
 * and turns on the row MOSFETs.
 *
 * @param seg Segment to publish data for.
 */
void SegmentPublish(uint32_t* args) {
    static uint8_t col = 0;
    
    if (col == 0) {
        ShifterShiftIn(&((Segment_t*)args)->shifter, 1);
    } else {
        ShifterShiftIn(&((Segment_t*)args)->shifter, 0);    
    }
    
    for (uint8_t row = 0; row < SEGMENT_ROWS; ++row) {
        if (((Segment_t*)args)->state[row][col]) {
            /* Rows are negative logic. */
            GPIOSetBit(((Segment_t*)args)->rowPins[row], false);
        } else {
            GPIOSetBit(((Segment_t*)args)->rowPins[row], true);
        }
    }

    
    col = (col + 1) % SEGMENT_COLUMNS;
}

void SegmentInit(SegmentConfig_t config, Segment_t* segment) {
    TimerConfig_t timerConfig = {
        .timerID    = config.timerID,
        .period     = freqToPeriod(config.timerFreq, MAX_FREQ)/SEGMENT_COLUMNS,
        .timerTask  = SegmentPublish,
        .isPeriodic = true,
        .priority   = 5,
        .timerArgs  = (uint32_t*)segment
    };

    segment->segmentID  = config.segmentID;
    segment->shifter    = ShifterInit(config.shifterConfig);
    segment->timer      = TimerInit(timerConfig);

    /* Initialize GPIO pins as digital outputs. */
    GPIOConfig_t pinConfig = {
        .pin        = PIN_COUNT,
        .pull       = GPIO_OPEN_DRAIN,
        .isOutput   = true
    };

    for (uint8_t i = 0; i < SEGMENT_ROWS; ++i) {
        segment->rowPins[i] = config.rowPins[i];
        pinConfig.pin = config.rowPins[i];
        GPIOInit(pinConfig);
        GPIOSetBit(pinConfig.pin, true); /* Pins are negative logic. */
    }

    /* Clear state. */
    for (uint8_t row = 0; row < SEGMENT_ROWS; ++row) {
        for (uint8_t col = 0; col < SEGMENT_COLUMNS; ++col) {
            segment->state[row][col] = false;
        }
    }
}

void SegmentSetPixel(Segment_t* seg, uint8_t row, uint8_t column, bool state) {
    if (column >= SEGMENT_COLUMNS) return;
    seg->state[row][column] = state;
}

void SegmentClear(Segment_t* seg) {
    for (uint8_t i = 0; i < SEGMENT_ROWS; ++i) {
        for (uint8_t j = 0; j < SEGMENT_COLUMNS; ++j) {
            seg->state[i][j] = false;
        }
    }
}

void SegmentStart(Segment_t* seg) {
    TimerStart(seg->timer);
}

void SegmentStop(Segment_t* seg) {
    TimerStop(seg->timer);
}
