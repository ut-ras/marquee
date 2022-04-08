/**
 * @file BasicTestExample.c
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief Testing to see if rows and columns can be controlled.
 * @version 0.1
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** General imports. These can be declared the like the example below. */
#include <stdlib.h>

/** 
 * Device specific imports. Include files and library files are accessed like
 * the below examples.
 */
#include <lib/PLL/PLL.h>
#include <lib/GPIO/GPIO.h>
#include <lib/Timer/Timer.h>
#include <lib/shifter/shifter.h>

/** 
 * These function declarations are defined in the startup.s assembly file for
 * managing interrupts. 
 */
void EnableInterrupts(void);    // Defined in startup.s
void DisableInterrupts(void);   // Defined in startup.s
void WaitForInterrupt(void);    // Defined in startup.s


int main(void) {
    PLLInit(BUS_80_MHZ);
    DisableInterrupts();
    DelayInit();

    GPIOConfig_t pinConfig = {
        .pin=PIN_F1,
        .pull=GPIO_OPEN_DRAIN,
        .isOutput=true,
    };

    GPIOPin_t pins[7] = {
        /* Row pins. */
        PIN_A5,
        PIN_A6,
        PIN_D7,
        PIN_D6,
        PIN_A2,
        PIN_A3,
        PIN_A4,
    };
    
    for (uint8_t i = 0; i < 7; ++i) {
        pinConfig.pin = pins[i];
        GPIOInit(pinConfig);
        GPIOSetBit(pins[i], true);
    }
    
    EnableInterrupts();

    /* Test rows on. No lights should be active. */
    GPIOSetBit(pins[0], false);
    DelayMillisec(1000);
    GPIOSetBit(pins[0], true);
    GPIOSetBit(pins[1], false);
    DelayMillisec(1000);
    GPIOSetBit(pins[1], true);
    GPIOSetBit(pins[2], false);
    DelayMillisec(1000);
    GPIOSetBit(pins[2], true);
    GPIOSetBit(pins[3], false);
    DelayMillisec(1000);
    GPIOSetBit(pins[3], true);
    GPIOSetBit(pins[4], false);
    DelayMillisec(1000);
    GPIOSetBit(pins[4], true);
    GPIOSetBit(pins[5], false);
    DelayMillisec(1000);
    GPIOSetBit(pins[5], true);
    GPIOSetBit(pins[6], false);
    DelayMillisec(1000);
    GPIOSetBit(pins[6], true);

    /* Initialize columns. */
    ShifterConfig_t shifterConfig = {
        .clockPin=PIN_E0,
        .strobePin=PIN_B2,
        .outputEnablePin=PIN_B5, // HW FORCED HIGH
        .dataPin=PIN_B7
    };

    Shifter_t shifter = ShifterInit(shifterConfig);

    /* Test columns on. Lights should be active. */
    GPIOSetBit(pins[0], false);
    ShifterShiftInMulti(&shifter, 0, 36); /* Clear 3 segments. */
    DelayMillisec(1000);
    bool shift = true;
    while (1) {
        ShifterShiftIn(&shifter, shift);
        shift = !shift;
        DelayMillisec(100);
    }
}