/**
 * @file shifter.c
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief Implementation of the shifter driver.
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <lib/shifter/shifter.h>

#define ON(pin) (GPIOSetBit(pin, true))
#define DATA(pin, data) (GPIOSetBit(pin, data))
#define OFF(pin) (GPIOSetBit(pin, false))

Shifter_t ShifterInit(ShifterConfig_t config) {
    /* Initialize GPIO pins as digital outputs. */
    GPIOConfig_t pinConfig = {
        .pin=PIN_COUNT,
        .pull=GPIO_PULL_DOWN,
        .isOutput=true
    };
    pinConfig.pin=config.clockPin;
    GPIOInit(pinConfig);
    pinConfig.pin=config.dataPin;
    GPIOInit(pinConfig);
    pinConfig.pin=config.outputEnablePin;
    GPIOInit(pinConfig);
    pinConfig.pin=config.strobePin;
    GPIOInit(pinConfig);

    Shifter_t shifter = {
        .clockPin=config.clockPin,
        .dataPin=config.dataPin,
        .outputEnablePin=config.outputEnablePin,
        .strobePin=config.strobePin
    };
    
    ON(shifter.outputEnablePin);
    return shifter;
}

void ShifterShiftIn(Shifter_t* shifter, bool data) {
    ON(shifter->strobePin);
    DATA(shifter->dataPin, data);
    ON(shifter->clockPin);
    OFF(shifter->clockPin);
    OFF(shifter->strobePin);
}

void ShifterShiftInMulti(Shifter_t* shifter, uint64_t data, uint8_t count) {
    ON(shifter->strobePin);

    for (uint8_t i = 0; i < count; ++i) {
        DATA(shifter->dataPin, (data >> i) & 0x1);
        ON(shifter->clockPin);
        OFF(shifter->clockPin);
    }

    OFF(shifter->strobePin);
}
