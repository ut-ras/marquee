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


LinearDisplay_t LinearDisplayInit(LinearDisplayConfig_t config) {
    LinearDisplay_t display;
    return display;
}

void LinearDisplayPushChar(LinearDisplay_t* display, char data) {
    //sizeof(bitmap[data-32])/sizeof(char) // is this the size of a single row of bitmap?
    uint8_t x = 0;
    for (int i = 0; i < sizeof(bitmap[data-32])/sizeof(char); i++){//for loop by row
        SegmentSetPixel(&(display->segments), i, (x+0)%SEGMENT_COLUMNS, bitmap[data-32][i]&(0x40)>>6);
        SegmentSetPixel(&(display->segments), i, (x+1)%SEGMENT_COLUMNS, bitmap[data-32][i]&(0x20)>>5);
        SegmentSetPixel(&(display->segments), i, (x+2)%SEGMENT_COLUMNS, bitmap[data-32][i]&(0x10)>>4);
        SegmentSetPixel(&(display->segments), i, (x+3)%SEGMENT_COLUMNS, bitmap[data-32][i]&(0x08)>>3);
        SegmentSetPixel(&(display->segments), i, (x+4)%SEGMENT_COLUMNS, bitmap[data-32][i]&(0x04)>>2);
        SegmentSetPixel(&(display->segments), i, (x+5)%SEGMENT_COLUMNS, bitmap[data-32][i]&(0x02)>>1);
        SegmentSetPixel(&(display->segments), i, (x+6)%SEGMENT_COLUMNS, bitmap[data-32][i]&(0x01)>>0);
        // if (bitmap[data-32][i]&(0x40) == 1){
        //     SegmentSetPixel(&(display->segments), i, (x+0)%SEGMENT_COLUMNS, 1);
        // }
        // if (bitmap[data-32][i]&(0x20) == 1){
        //     SegmentSetPixel(&(display->segments), i, (x+1)%SEGMENT_COLUMNS, 1);
        // }
        // if (bitmap[data-32][i]<<2>>7 == 1){
        //     SegmentSetPixel(&(display->segments), i, (x+2)%SEGMENT_COLUMNS, 1);
        // }
        // if (bitmap[data-32][i]<<3>>7 == 1){
        //     SegmentSetPixel(&(display->segments), i, (x+3)%SEGMENT_COLUMNS, 1);
        // }
        // if (bitmap[data-32][i]<<4>>7 == 1){
        //     SegmentSetPixel(&(display->segments), i, (x+4)%SEGMENT_COLUMNS, 1);
        // }
        // if (bitmap[data-32][i]<<5>>7 == 1){
        //     SegmentSetPixel(&(display->segments), i, (x+5)%SEGMENT_COLUMNS, 1);
        // }
        // if (bitmap[data-32][i]<<6>>7 == 1){
        //     SegmentSetPixel(&(display->segments), i, (x+6)%SEGMENT_COLUMNS, 1);
        // }
    }
    x = (x+1) % SEGMENT_COLUMNS;
    DelayMillisec(250);
    SegmentClear(&(display->segment));
}

void LinearDisplayPushString(LinearDisplay_t* display, char* data) {
    for (int i = 0; data[i] != '\0'; i++){
        LinearDisplayPushChar(display, data[i]);
    }
}

/* TODO: support for 12x48 images. */

void LinearDisplayClear(LinearDisplay_t* display) {

}

void LinearDisplayStart(LinearDisplay_t* display) {

}

void LinearDisplayStop(LinearDisplay_t* display) {

}

void LinearDisplayChangeUpdateRate(LinearDisplay_t* display, uint32_t freq) {
    
}