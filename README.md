# marquee
Code for displaying things on the marquee in the RAS room

To change the text displayed, just open up a `make uart` screen and enter in your text. No backspaces, and Enter will send the text.

To change the default message, change the buffer in main.c and change `buffer_index` to one less than the message length.

To change the scroll speed, mess with the constant that multiplies the last parameter to CallEveryUS (in ShiftRunUS) towards the end of shifter.c.
