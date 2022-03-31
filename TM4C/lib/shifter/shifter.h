/**
 * @file shifter.h
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief This shifter driver controls shifting of bits through the HCF4094BE
 * 8-stage shift and store bus register with 3 stage outputs.
 * Looking at the HCF4094BE truth table, we care about the following events:
 *  - Given a rising clock edge and output enable is high
 *    - On strobe low, Qs = Q7
 *    - On strobe high, Q1 = serial data in, Qn = Qn-1, Qs = Q7
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include <stdbool.h>
#include <lib/GPIO/GPIO.h>

typedef struct ShifterConfig {
    GPIOPin_t clockPin;
    GPIOPin_t strobePin;
    GPIOPin_t outputEnablePin;
    GPIOPin_t dataPin;
} ShifterConfig_t;

typedef struct Shifter {
    GPIOPin_t clockPin;
    GPIOPin_t strobePin;
    GPIOPin_t outputEnablePin;
    GPIOPin_t dataPin;
} Shifter_t;

/**
 * @brief Initializes a virtual HCF4094BE shifter on a set of pins.
 * 
 * @param config Shifter configuration.
 * @return Shifter associated with this config.
 */
Shifter_t ShifterInit(ShifterConfig_t config);

/**
 * @brief ShifterShiftIn shifts in one bit of data.
 * 
 * @param shifter Reference to a shifter.
 * @param data Boolean data to shift.
 */
void ShifterShiftIn(Shifter_t* shifter, bool data);

/**
 * @brief ShifterShiftInMulti shifts in multiple bits at once.
 * 
 * @param shifter Reference to a shifter.
 * @param data Boolean data, packed into up to 64 bits.
 * @param count How many bits to shift.
 */
void ShifterShiftInMulti(Shifter_t* shifter, uint64_t data, uint8_t count);