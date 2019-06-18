#ifndef DRAW_H
#define DRAW_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "fractal.h"
#include "pile.h"

#define FILENAME "fractal"
#define NFILENAME 20
#define EXTENSION ".pbm"
#define NEXTENSION 4
#define TYPE 4
#define BYTE 8

enum {UP='u', DOWN='d', ON='1', OFF='0'};

FILE *open_file(int argc, char *argv[]);
void close_file(FILE *fp);
void init_file(FILE *fp, int type, char **buffer);
void write_bit(char buffer[], unsigned int i, unsigned int j, char state);
void printBin(int num, int bits);
void drawTriangle(char buffer[], float pos[2], float side, float half, char state, char orientation);
unsigned int roundFloat(float x);
void drawAllTriangles(char buffer[], Entry *pile, float side, float half, char state, char orientation);
void readFractal(FILE *fp, char buffer[]);
void writeFractal(FILE *fp, char buffer[]);

unsigned int W;		// width
unsigned int H;		// height
unsigned int N;		// number of chars per line
unsigned int T;		// total number of chars
unsigned int O;		// initial bytes offset


#endif /* DRAW_H */
