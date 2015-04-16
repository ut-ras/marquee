
#include "shifter.h"

#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_WIDTH 24

void InitDisplay(tShifter *sh);

void Display(tShifter *sh, const char *message);

#endif
