#!/bin/sh
#gcc fractal.c -Wall -pedantic -Wextra $(sdl2-config --cflags --libs) -o fractal
gcc pngFromFractal.c -Wall -pedantic -Wextra $(sdl2-config --cflags --libs) -lSDL2_image -o pngFromfractal
