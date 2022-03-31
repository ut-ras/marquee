/**
 * @file segment.h
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief A segment PCB of the marquee consists of 14 rows and 48 columns. Each
 * pair of columns is controlled by an output pin of ULN2003AN/ULN2803A
 * darlington driver, for a total of 4 driver ICs (12 columns per IC).
 * 
 * As a quick explainer for the darlington driver:
 *  - If an input pin is HIGH, the corresponding output pin is LOW and sinks
 *    current from the column of LEDs.
 *  - If an input pin is LOW, the corresponding output pin is HiZ and the column
 *    of LEDs is essentially open circuit.
 * 
 * The four darlington drivers on the segment PCB are controlled by three
 * HCF4094BE 8-stage shift and store bus registers with 3-stage outputs.
 * Looking at the HCF4094BE truth table, we care about the following events:
 *  - Given a rising clock edge and output enable is high
 *    - On strobe low, Qs = Q7
 *    - On strobe high, Q1 = serial data in, Qn = Qn-1, Qs = Q7
 * 
 * On the other hand, each row is controlled by MOSFET array. If the MOSFET gate
 * is high, then a HV power source sends current through the row, providing that
 * the column is shorted to ground.
 * 
 * As such, LEDs can be lit up at a minimum resolution of 1x2, provided that the
 * row MOSFET and column darlington pair are activated, granting a closed
 * circuit path between HV and GND.
 * 
 * This segment driver seeks to be able to turn on or off localized LED pairs on
 * the segment, given a row and column pair value.
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdbool.h>
#include <stdint.h>
#include <lib/GPIO/GPIO.h>

#define SEGMENT_ROWS 14
#define SEGMENT_COLUMNS 24

typedef struct SegmentConfig {
    uint8_t segmentID;
    ShifterConfig_t shifterConfig;
    GPIOPin_t rowPins[SEGMENT_ROWS];
} SegmentConfig_t;

typedef struct Segment {
    uint8_t segmentID;
    Shifter_t shifter;
    GPIOPin_t rowPins[SEGMENT_ROWS];
    bool state[SEGMENT_ROWS][SEGMENT_COLUMNS];
} Segment_t;

/**
 * @brief SegmentInit Initializes a virtual marquee segment and the relevant
 * pins. 
 * 
 * @param config Segment configuration.
 * @return Segment_t Virtual segment instance.
 */
Segment_t SegmentInit(SegmentConfig_t config);

/**
 * @brief SegmentSetPixel Sets a single pixel in the virtual state of the
 * segment.
 * 
 * @param seg Segment to modify.
 * @param row Row of pixel.
 * @param column Column of pixel.
 * @param state New state of pixel.
 */
void SegmentSetPixel(Segment_t* seg, uint8_t row, uint8_t column, bool state);

/**
 * @brief SegmentClear Clears the virtual state of the segment.
 * 
 * @param seg Segment to clear.
 */
void SegmentClear(Segment_t* seg);

/**
 * @brief SegmentPublish Publishes the virtual segment state data to a physical
 * segment of the marquee. This shifts data into the HCF4094BE shift registers
 * and turns on the row MOSFETs.
 * 
 * @param seg Segment to publish data for.
 */
void SegmentPublish(Segment_t* seg);