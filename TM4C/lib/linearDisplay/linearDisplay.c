/**
 * @file lineaDisplay.c
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief Implementation of the display driver.
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 
#include <lib/linearDisplay/linearDisplay.h>
#include <lib/segment/segment.h>
#include <lib/font/tom-thumb_font.h>


void LinearDisplayInit(LinearDisplayConfig_t config, LinearDisplay_t* display) {
    
    SegmentConfig_t segmentConfig = {
        .segmentID      = 0,
        .shifterConfig  = config.shifterConfig,
        .rowPins        = {},
        .timerID        = config.timerId,
        .timerFreq      = 150
    };

    for (uint8_t i = 0; i < SEGMENT_ROWS; ++i) {
        segmentConfig.rowPins[i] = config.rowPins[i];
    }

    SegmentInit(segmentConfig, &(display->segment));
    display->displayTimer = display->segment.timer;
}

void LinearDisplayPushChar(LinearDisplay_t* display, char data, uint8_t offShift) {
    for (int i = 0; i < CHAR_HEIGHT; i++){//for loop by row
        SegmentSetPixel(&(display->segment), CHAR_HEIGHT-i, 0 + offShift*CHAR_WIDTH, (bitmap[data-32][i]>>7)&0x01);
        SegmentSetPixel(&(display->segment), CHAR_HEIGHT-i, 1 + offShift*CHAR_WIDTH, (bitmap[data-32][i]>>6)&0x01);
        SegmentSetPixel(&(display->segment), CHAR_HEIGHT-i, 2 + offShift*CHAR_WIDTH, (bitmap[data-32][i]>>5)&0x01);
        SegmentSetPixel(&(display->segment), CHAR_HEIGHT-i, 3 + offShift*CHAR_WIDTH, (bitmap[data-32][i]>>4)&0x01);
        SegmentSetPixel(&(display->segment), CHAR_HEIGHT-i, 4 + offShift*CHAR_WIDTH, (bitmap[data-32][i]>>3)&0x01);
        SegmentSetPixel(&(display->segment), CHAR_HEIGHT-i, 5 + offShift*CHAR_WIDTH, (bitmap[data-32][i]>>2)&0x01);
        SegmentSetPixel(&(display->segment), CHAR_HEIGHT-i, 6 + offShift*CHAR_WIDTH, (bitmap[data-32][i]>>1)&0x01);
        SegmentSetPixel(&(display->segment), CHAR_HEIGHT-i, 7 + offShift*CHAR_WIDTH, (bitmap[data-32][i]>>0)&0x01);
    }
}

void LinearDisplayPushString(LinearDisplay_t* display, char* data, uint8_t size) {
    for (int i = 0; i < size; i++){
        LinearDisplayPushChar(display, data[i], i);
    }
}


/* TODO: support for 12x48 images. */

void LinearDisplayClear(LinearDisplay_t* display) {
    SegmentClear(&display->segment);
}

void LinearDisplayStart(LinearDisplay_t* display) {
    SegmentStart(&display->segment);
}

void LinearDisplayStop(LinearDisplay_t* display) {

}

void LinearDisplayChangeUpdateRate(LinearDisplay_t* display, uint32_t freq) {
    
}