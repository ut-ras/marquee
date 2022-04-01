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

    bool colOn = false;
    /* Turn on relevant rows if found. */
    for (uint8_t row = 0; row < SEGMENT_ROWS; ++row) {
        if (((Segment_t*)args)->state[row][col]) {
            GPIOSetBit(((Segment_t*)args)->rowPins[row], true);
            colOn = true;
        } else {
            GPIOSetBit(((Segment_t*)args)->rowPins[row], false);
				}
    }
    if (colOn) {
        /* Shift only relevant column on. */
        uint64_t shiftData = 1 << col;
        /* Shift bits down the segment. */
        ShifterShiftInMulti(&((Segment_t*)args)->shifter, shiftData, SEGMENT_COLUMNS);
    }

    col = (col + 1) % SEGMENT_COLUMNS;
}

void SegmentInit(SegmentConfig_t config, Segment_t* segment) {
    TimerConfig_t timerConfig = {
        .timerID=config.timerID,
        .period=freqToPeriod(config.timerFreq, MAX_FREQ),
        .timerTask=SegmentPublish,
        .isPeriodic=true,
        .priority=5,
        .timerArgs=(uint32_t*)segment
    };
		
    segment->segmentID  = config.segmentID;
    segment->shifter    = ShifterInit(config.shifterConfig);
    segment->timer = TimerInit(timerConfig);

    /* Initialize GPIO pins as digital outputs. */
    GPIOConfig_t pinConfig = {
        .pin=PIN_COUNT,
        .pull=GPIO_PULL_DOWN,
        .isOutput=true
    };

    for (uint8_t i = 0; i < SEGMENT_ROWS; ++i) {
        segment->rowPins[i] = config.rowPins[i];
        pinConfig.pin = config.rowPins[i];
        GPIOInit(pinConfig);
				GPIOSetBit(pinConfig.pin, false);
    }
		
		/* Clear state. */
		for (uint8_t row = 0; row < SEGMENT_ROWS; ++row) {
				for (uint8_t col = 0; col < SEGMENT_COLUMNS; ++col) {
						segment->state[row][col] = false;
				}
		}
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

void SegmentStart(Segment_t* seg) {
    TimerStart(seg->timer);
}

void SegmentStop(Segment_t* seg) {
    TimerStop(seg->timer);
}
