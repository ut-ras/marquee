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

LinearDisplay_t LinearDisplayInit(LinearDisplayConfig_t config) {
    LinearDisplay_t display;
    return display;
}

void LinearDisplayPushChar(LinearDisplay_t* display, char data) {

}

void LinearDisplayPushString(LinearDisplay_t* display, char* data) {

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