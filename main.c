#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/adc.h>

#include "shifter.h"

// Blink the LED to show we're on
tBoolean blink_on = true;

void blink(void) {
    SetPin(PIN_F3, blink_on);
    blink_on = !blink_on;
}

tShifter sh;

tPin rows[7] = { PIN_A4, PIN_A3, PIN_A2, PIN_D6, PIN_D7, PIN_A6, PIN_A5 };

const char format[] = "dddddddd dddddddd dddddddd"
                      "dddddddd dddddddd dddddddd"
                      "dddddddd dddddddd dddddddd"
                      "dddddddd dddddddd dddddddd";

unsigned char data[] = { 
    0 ,1 ,2 ,3 , 4 ,5 ,6 , 7, 8 ,9 ,10,11, 
    12,13,14,15, 16,17,18,19, 20,21,22,23,
    24,25,26,27, 28,29,30,31, 32,33,34,35,
    36,37,38,39, 40,41,42,43, 44,45,46,47,
    48,49,50,51, 52,53,54,55, 56,57,58,59, 
    60,61,62,63, 64,65,66,67, 68,69,70,71,
    72,73,74,75, 76,77,78,79, 80,81,82,83,
    84,85,86,87, 88,89,90,91, 92,93,94,95,
};

tADC *aud0;
tADC *aud1;


void hi(tADC *adc) {
    int i = 0;
    
    ShiftUpdate(&sh);
    
    sh.data += 1;
    
    //for (i = 0; i < (8*3*4)-1; i++) {
    //    data[i] = data[i+1];
    //}
    
    //Printf("hi %f\n", (ADCRead(adc) - ADCRead(adc)));
    //data[8*3*4-1] = 1 << (unsigned char)(7 * (100 * (ADCRead(adc) + ADCRead(adc))));
}

// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here
    //CallEvery(blink, 0, 0.5);
    
    sh.dline = PIN_B7;
    sh.clk = PIN_E0;
    sh.strobe = PIN_B2;
    
    sh.rowcount = 7;
    sh.rows = rows;
    sh.invert = true;
    
    sh.format = format;
    sh.data = data;
    
    InitShift(&sh);
    
    
    aud0 = InitializeADC(PIN_D0);
    aud1 = InitializeADC(PIN_D1);
    
    CallEvery(hi, 0, (1.0f/50.0f) / 7);
    
    //ADCBackgroundRead(aud0, hi, aud0);
    
    //ShiftRun(&sh, (1.0f / 60.0f));
    
    //Printf("Hello World!\n");
    
    { while (1) {
        //hi(aud0);
        
        
        //{int i = 0; while (i < 100000) i++;}
        //Wait(1.0f/30.0f);
        
        // Runtime code can go here
        //ShiftUpdate(&sh);
        //Printf("Hello World!\n");
        //{ volatile int i = 0;
        //  for (; i < 10000; i++);
        //}
        //WaitUS(1000);
    } }
}
