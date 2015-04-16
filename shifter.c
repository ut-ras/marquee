
#include "shifter.h"

#include <StellarisWare/inc/hw_ints.h>
#include <StellarisWare/inc/hw_memmap.h>
#include <StellarisWare/inc/hw_gpio.h>
#include <StellarisWare/driverlib/interrupt.h>
#include <StellarisWare/driverlib/gpio.h>
#include <StellarisWare/driverlib/sysctl.h>




static void ShiftSelect(tShifter *sh, int n) {
    int i;
    
    for (i = 0; i < sh->height; i++) {
        if ((i == n) == (!sh->invert))
            SetPinZ(sh->rows[i]);
        else
            SetPin(sh->rows[i], false);
    }
}

void InitShift(tShifter *sh) {
    sh->active = -1;
    
    ShiftSelect(sh, -1);
    SetPin(sh->dline, false);
    SetPin(sh->clk, false);
    SetPin(sh->strobe, false);
}

void ShiftUpdate(tShifter *sh) {
    int i;
    const unsigned char *d = sh->data;
    
    // Clear things here to keep artifacts from appearing
    ShiftSelect(sh, -1);
    
    sh->active = (sh->active + 1) % sh->height;
   
    for (i = 0; i < sh->width; i++) {
        SetPin(sh->dline, (*d++) & (1 << sh->active));
        SetPin(sh->clk, true);
        SetPin(sh->clk, false);
    }

    SetPin(sh->strobe, true);
    SetPin(sh->strobe, false);
    ShiftSelect(sh, sh->active);
}

void ShiftRunUS(tShifter *sh, tTime us) {
    CallEveryUS(ShiftUpdate, sh, us/sh->height);
}

void ShiftRun(tShifter *sh, float s) {
    ShiftRunUS(sh, US(s));
}
