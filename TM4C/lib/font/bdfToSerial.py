"""
bdfToSerial.py

This program takes bdf files and extracts the character encoding and converts it
into a char array. 

Input file: <fontset_name>.bdf
Output file: <fontset_name>.h
Output file internals:
```c
uint8_t <fontset_name>[<NUM_BYTES>] = {
    <BYTESTRING>
};
```

Character Encoding mapping.

Char            A

Pixels      1 1 1 1 1
            1 0 0 0 1
            1 1 1 1 1
            1 0 0 0 1
            1 0 0 0 1

Serial      11111_10001_11111_10001_10001

Reverse
Serial      10001_10001_11111_10001_11111

Padded     B4        B3        B2        B1
         0001_0001_1000_1111_1110_0011_1111

Num bytes per char: ceil(5*5/8) = ceil(25/8) = 4

Since there are 128 characters, there are a total of 128 * 4 bytes or 512 bytes
for a 5x5 mapping. For a 7x7 mapping, there are total of 128 * ceil(7*7/8) or
128 * 7 or 896 bytes.

The fontsets only support useful ASCII characters (things like exclamation
marks, letters, numbers, etc.). ASCII values like NUL or BS will show up as a
blank space.
"""