/**
 * @file tom-thumb_font.c
 * @author Matthew Yu
 * @brief Character encoding mapping for the IEEE RAS demobots.
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 */

#include <lib/font/tom-thumb_font.h>


char mapping[NUM_CHARS] = {
    32,33,34,35,36,
    37,38,39,40,41,
    42,43,44,45,46,
    47,48,49,50,51,
    52,53,54,55,56,
    57,58,59,60,61,
    62,63,64,65,66,
    67,68,69,70,71,
    72,73,74,75,76,
    77,78,79,80,81,
    82,83,84,85,86,
    87,88,89,90,91,
    92,93,94,95,96,
    97,98,99,100,101,
    102,103,104,105,106,
    107,108,109,110,111,
    112,113,114,115,116,
    117,118,119,120,121,
    122,123,124,125,126,
};
char bitmap[NUM_CHARS][CHAR_SIZE] = {
    [0],
    [128, 128, 128, 0, 128],
    [160, 160],
    [160, 224, 160, 224, 160],
    [96, 192, 96, 192, 64],
    [128, 32, 64, 128, 32],
    [192, 192, 224, 160, 96],
    [128, 128],
    [64, 128, 128, 128, 64],
    [128, 64, 64, 64, 128],
    [160, 64, 160],
    [64, 224, 64],
    [64, 128],
    [224],
    [128],
    [32, 32, 64, 128, 128],
    [96, 160, 160, 160, 192],
    [64, 192, 64, 64, 64],
    [192, 32, 64, 128, 224],
    [192, 32, 64, 32, 192],
    [160, 160, 224, 32, 32],
    [224, 128, 192, 32, 192],
    [96, 128, 224, 160, 224],
    [224, 32, 64, 128, 128],
    [224, 160, 224, 160, 224],
    [224, 160, 224, 32, 192],
    [128, 0, 128],
    [64, 0, 64, 128],
    [32, 64, 128, 64, 32],
    [224, 0, 224],
    [128, 64, 32, 64, 128],
    [224, 32, 64, 0, 64],
    [64, 160, 224, 128, 96],
    [64, 160, 224, 160, 160],
    [192, 160, 192, 160, 192],
    [96, 128, 128, 128, 96],
    [192, 160, 160, 160, 192],
    [224, 128, 224, 128, 224],
    [224, 128, 224, 128, 128],
    [96, 128, 224, 160, 96],
    [160, 160, 224, 160, 160],
    [224, 64, 64, 64, 224],
    [32, 32, 32, 160, 64],
    [160, 160, 192, 160, 160],
    [128, 128, 128, 128, 224],
    [160, 224, 224, 160, 160],
    [160, 224, 224, 224, 160],
    [64, 160, 160, 160, 64],
    [192, 160, 192, 128, 128],
    [64, 160, 160, 224, 96],
    [192, 160, 224, 192, 160],
    [96, 128, 64, 32, 192],
    [224, 64, 64, 64, 64],
    [160, 160, 160, 160, 96],
    [160, 160, 160, 64, 64],
    [160, 160, 224, 224, 160],
    [160, 160, 64, 160, 160],
    [160, 160, 64, 64, 64],
    [224, 32, 64, 128, 224],
    [224, 128, 128, 128, 224],
    [128, 64, 32],
    [224, 32, 32, 32, 224],
    [64, 160],
    [224],
    [128, 64],
    [192, 96, 160, 224],
    [128, 192, 160, 160, 192],
    [96, 128, 128, 96],
    [32, 96, 160, 160, 96],
    [96, 160, 192, 96],
    [32, 64, 224, 64, 64],
    [96, 160, 224, 32, 64],
    [128, 192, 160, 160, 160],
    [128, 0, 128, 128, 128],
    [32, 0, 32, 32, 160, 64],
    [128, 160, 192, 192, 160],
    [192, 64, 64, 64, 224],
    [224, 224, 224, 160],
    [192, 160, 160, 160],
    [64, 160, 160, 64],
    [192, 160, 160, 192, 128],
    [96, 160, 160, 96, 32],
    [96, 128, 128, 128],
    [96, 192, 96, 192],
    [64, 224, 64, 64, 96],
    [160, 160, 160, 96],
    [160, 160, 224, 64],
    [160, 224, 224, 224],
    [160, 64, 64, 160],
    [160, 160, 96, 32, 64],
    [224, 96, 192, 224],
    [96, 64, 128, 64, 96],
    [128, 128, 0, 128, 128],
    [192, 64, 32, 64, 192],
    [96, 192],
}
