
#include "display.h"
#include "font.h"


void InitDisplay(tShifter *sh) {
    InitShift(sh);
    ShiftRun(sh, (1.0f/45.0f));
}

void Display(tShifter *sh, const char *message) {
    int i, j, k;

    for (i = 0; message[i]; i++) {
        for (j = 0; j < FONT_WIDTH; j++) {
            sh->data[i*FONT_WIDTH + j] = 0;

            for (k = 0; k < FONT_HEIGHT; k++) {
                sh->data[i*FONT_WIDTH + j] |= 
                    (1&(font[(message[i]-' ')*FONT_WIDTH + j] >> k)) << FONT_HEIGHT-1-k;
            }
        }
    }
}

