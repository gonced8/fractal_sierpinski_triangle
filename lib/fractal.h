#ifndef FRACTAL_H
#define FRACTAL_H


#include <stdio.h>
#include <math.h>

#include "main.h"
#include "draw.h"
#include "pile.h"

void drawFractal(FILE *fp, char buffer[], float size, unsigned int iter);
float halfHeight(float size);
void iterate(Entry **pile, float *size, float *half, float count);
Entry *divide(Entry *pile, Entry *entry, float size, float height, float half);


#endif /* FRACTAL_H */
