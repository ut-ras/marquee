/**
 * @file font.c
 * @author Matthew Yu (matthewjkyu@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <lib/font/font.h>

#define FONT_5x5_BIT_SIZE 25
#define FONT_9x9_BIT_SIZE 81

/*
Char            A

Pixels      1 1 1 1 1
            1 0 0 0 1
            1 1 1 1 1
            1 0 0 0 1
            1 0 0 0 1

Serial      11111_10001_11111_10001_10001

Reverse
Serial      10001_10001_11111_10001_11111

           B4        B3        B2        B1
        ...|1_0001_1000_1111_1110_0011_1111

Chars pixel maps are appended onto the serial bytestring.
Since there are 128 characters, there are 128 * 25 bits or 3200 bits or 400
bytes.

For a 9x9 map, there are 128 * 81 bits or 10368 bits or 1296 bytes.
*/

/* The fontset is represented as a packed array of bytes; for now the only
available fontset is 5x5, but maybe a dedicated person might add another one for
9x9, 12x12, or even 14x14. */

/* The fontsets only support useful ASCII characters (things like exclamation
marks, letters, numbers, etc.). ASCII values like NUL or BS will show up as a
blank space. There are a total of 128 ASCII values in the standard characterset.
*/

/* For the 5x5 fontset */


