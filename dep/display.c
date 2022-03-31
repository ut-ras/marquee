
#include <string.h>

#include "display.h"
#include "font.h"


static int off;
static int len;
static char message[256];

void DisplayUpdate(tShifter *sh) {
    int i, j;

    for (i = 0; i < DISPLAY_WIDTH; i++) {
        sh->data[i] = 0;

        for (j = 0; j < FONT_HEIGHT; j++) {
            int k = len > (DISPLAY_WIDTH/FONT_WIDTH) ? (i + off) % (FONT_WIDTH*len) : i;
            unsigned char ch = k/FONT_WIDTH < len ? message[k/FONT_WIDTH] : ' ';

            sh->data[i] |= (1&(font[(ch-' ')*FONT_WIDTH + k%FONT_WIDTH] >> j)) << FONT_HEIGHT-1-j;
        }
    }

    if (len > DISPLAY_WIDTH/FONT_WIDTH)
        off++;
}

void InitDisplay(tShifter *sh) {
    InitShift(sh);
    ShiftRun(sh, (1.0f/62.5f));
}

void Display(tShifter *sh, int l, const char *m) {
    off = 0;
    len = l;
    memcpy(message, m, len);

    if (len > DISPLAY_WIDTH/FONT_WIDTH)
        message[len++] = ' ';
}

void DisplayRunUS(tShifter *sh, tTime us) {
    CallEveryUS(DisplayUpdate, sh, us);
}

void DisplayRun(tShifter *sh, float s) {
    DisplayRunUS(sh, US(s));
}
