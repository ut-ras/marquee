"""
@file:      bdfToSerial.py
@author:    Matthew Yu (matthewjkyu@gmail.com)
@brief:     Takes a bdf files and converts it into a custom font file for use in
            the marquee sign board.
@version:   0.1.0
@requirements: Python 3
@date:      2022-03-20
@copyright: Copyright (c) 2021.

@example:
STARTCHAR A
ENCODING 65
SWIDTH 1000 0
DWIDTH 4 0
BBX 3 5 0 0
BITMAP
40
A0
E0
A0
A0
ENDCHAR

0100 0000
1010 0000
1110 0000
1010 0000
1010 0000
"""

import argparse
import os

parser = argparse.ArgumentParser()
parser.add_argument('--file_name')
args = parser.parse_args()

filename = args.file_name

with open(filename, "r") as read_file:
    ENCODING_START = 32
    ENCODING_END = 126
    BIT_SHIFT = 8
    encodings = {
        # Start at 0d32 (space)
        # End at 0d126 (tilde)
    }
    encoding_width = 5
    encoding_height = 7
    
    # Capture encodings from 0d32 to 0d126.
    while True:
        line = read_file.readline()
        if not line:
            break
        elif "FONTBOUNDINGBOX" in line:
            encoding_width = int(line.split()[1])
            encoding_height = int(line.split()[2])
        elif "STARTCHAR" in line:
            char_name = line.split()[-1]

            line = read_file.readline()
            encoding_value = int(line.split()[-1])
            if (encoding_value >= ENCODING_START and encoding_value <= ENCODING_END):
                encodings[encoding_value] = {}

                read_file.readline() # SWDITH
                read_file.readline() # DWIDTH

                # Add in character name.
                encodings[encoding_value]["char_name"] = char_name

                # Get minimum size of character.
                line = read_file.readline().split() # BBX
                encodings[encoding_value]["size"] = (int(line[1]), int(line[2]))
                encodings[encoding_value]["bitmap"] = []

                # Capture bitmap for character.
                read_file.readline() # BITMAP
                for i in range(int(line[2])):
                    line = read_file.readline().split() # BBX
                    encodings[encoding_value]["bitmap"].append(int(line[0], 16))

    print("ENCODINGS\n")
    for _, encoding in encodings.items():
        print(encoding)
        (width, height) = encoding["size"]
        for i in range(height):
            bits = encoding["bitmap"][i]
            for j in range(BIT_SHIFT):
                bit = (bits >> (BIT_SHIFT-1-j)) & 0x1
                if (bit):
                    print('#', end = '')
                else:
                    print(' ', end='')
            print()

    # Write header file.
    with open(os.path.splitext(filename)[0] + "_font.h", "w") as write_file:
        write_file.write(f'''/**
 * @file {os.path.splitext(filename)[0] + "_font.h"}
 * @author Matthew Yu
 * @brief Character encoding mapping for the IEEE RAS demobots.
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 */
#pragma once

#include <stdint.h>

#define CHAR_WIDTH {encoding_width}
#define CHAR_HEIGHT {encoding_height}
#define CHAR_SIZE CHAR_WIDTH / 8 + 1 // in terms of bytes.
#define NUM_CHARS {ENCODING_END - ENCODING_START + 1}

extern char mapping[NUM_CHARS];
extern char bitmap[NUM_CHARS][CHAR_SIZE];
'''
        )

    # Write implementation file.
    with open(os.path.splitext(filename)[0] + "_font.c", "w") as write_file:
        write_file.write(f'''/**
 * @file {os.path.splitext(filename)[0] + "_font.c"}
 * @author Matthew Yu
 * @brief Character encoding mapping for the IEEE RAS demobots.
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 */

#include <lib/font/{os.path.splitext(filename)[0] + "_font.h"}>


'''
        )

        mapping = [32] * (ENCODING_END - ENCODING_START + 1)
        bitmap = [[0]] * (ENCODING_END - ENCODING_START + 1)
        for ascii_value, encoding in encodings.items():
            mapping[int(ascii_value) - ENCODING_START] = int(ascii_value)
            bitmap[int(ascii_value) - ENCODING_START] = encoding["bitmap"]

        # Write character mapping.
        write_file.write("char mapping[NUM_CHARS] = {")
        idx = 0
        for char in mapping:
            if idx % 5 == 0:
                write_file.write('\n    ')
            write_file.write(f"{char},")
            idx = idx + 1
        write_file.write("\n};\n")
        
        # Write bitmaps.
        write_file.write("char bitmap[NUM_CHARS][CHAR_SIZE] = {\n")
        for char in bitmap:
            write_file.write(f"    {char},\n")
        write_file.write("}\n")
