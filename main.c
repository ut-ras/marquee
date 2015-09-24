#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/adc.h>

#include "shifter.h"
#include "display.h"

void heartbeat(void) {
    static int blink_on = true;
    SetPin(PIN_F3, blink_on);
    blink_on = !blink_on;
}

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

tPin rows[7] = { PIN_A4, PIN_A3, PIN_A2, PIN_D6, PIN_D7, PIN_A6, PIN_A5 };

tShifter sh = {
    PIN_B7, PIN_E0, PIN_B2,
    7, 96, rows, true, data
};


#define BUFFER_WIDTH 256
int buffer_index = 0;
char buffer[BUFFER_WIDTH];

// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here
    CallEvery(heartbeat, 0, 1.0f);
    InitDisplay(&sh);

    sh.cb = (void (*)(void *))DisplayUpdate;
    sh.cb_data = &sh;
    
    while (1) {
        char c = (char)Getc();

        if (buffer_index == 0 && c != '=')
            continue;

        if (c == '\r' || buffer_index == BUFFER_WIDTH-1) {
            Display(&sh, buffer_index-1, buffer+1);
            buffer_index = 0;
        } else {
            buffer[buffer_index++] = c;
        }
    }
}
