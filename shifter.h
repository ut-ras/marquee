
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>

#ifndef SHIFTER_H
#define SHIFTER_H

typedef struct Shifter {
    tPin dline;
    tPin clk;
    tPin strobe;
    
    int height;
    int width;
    const tPin *rows;
    tBoolean invert;
    
    unsigned char *data;
    
    int active;
    void (*cb)(void *);
    void *cb_data;
} tShifter;


void InitShift(tShifter *sh);

void ShiftUpdate(tShifter *sh);

void ShiftRunUS(tShifter *sh, tTime us);

void ShiftRun(tShifter *sh, float s);

#endif
