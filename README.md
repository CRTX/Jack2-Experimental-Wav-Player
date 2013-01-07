Version 1.0

Program usage after compiling:

wavplayer -play /location/to/your/soundfile.wav

Notes:

-Only supports little-endian processors for now.

-Have to manually change the amount of bytes read for each bit rate format in WavReader.cpp:52

1 byte = 8 bit
2 bytes = 16bit
3 bytes = 24bit
4 bytes = 32bit
