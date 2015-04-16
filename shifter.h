
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>

typedef struct Shifter {
    tPin dline;
    tPin clk;
    tPin strobe;
    
    int rowcount;
    const tPin *rows;
    tBoolean invert;
    
    const char *format;
    const unsigned char *data;
    
    int active;
} tShifter;


void InitShift(tShifter *sh);

void ShiftUpdate(tShifter *sh);

void ShiftRunUS(tShifter *sh, tTime us);

void ShiftRun(tShifter *sh, float s);
