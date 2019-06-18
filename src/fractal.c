#include "fractal.h"


void drawFractal(FILE *fp, char buffer[], float size, unsigned int iter){
	float pos[2];
	float half = halfHeight(size);		// half height
	unsigned int count;
	Entry *pile;

	if(STEPS)
		readFractal(fp, buffer);

	pos[0] = H/2.;
	pos[1] = W/2.;

	// Draw main triangle
	printf("Iteration %d: \t size=%f\n", 0, size);
	fflush(stdout);
	drawTriangle(buffer, pos, size, half, ON, UP);
	if(STEPS)
		writeFractal(fp, buffer);

	// First down triangle
	size /= 2;
	half = halfHeight(size);
	
	pos[0] += half;
	pile = push(NULL, newEntry(pos));

	printf("Iteration %d: \t size=%f\n", 1, size);
	fflush(stdout);
	drawAllTriangles(buffer, pile, size, half, OFF, DOWN);
	if(STEPS)
		writeFractal(fp, buffer);

	for(count=2; count<=iter; count++){
		iterate(&pile, &size, &half, count);

		printf("Iteration %d: \t size=%f\n", count, size);
		fflush(stdout);
		if(roundFloat(size)){
			drawAllTriangles(buffer, pile, size, half, OFF, DOWN);
			if(STEPS)
				writeFractal(fp, buffer);
		}
		else{
			printf("Size too small to draw\n");
			break;
		}
	}

	if(!STEPS)
		writeFractal(fp, buffer);

	return;
}


float halfHeight(float size){
	return size*sqrtf(3)/4;	
}


void iterate(Entry **pile, float *size, float *half, float count){
	Entry *new = NULL;
	Entry *aux;
	float height = *half;
	
	*size /= 2;
	*half = halfHeight(*size);

	for(aux=*pile; aux!=NULL; aux=aux->next)
		new = divide(new, aux, *size, height, *half);

	clear(*pile);
	*pile = new;

	return;
}


Entry *divide(Entry *pile, Entry *entry, float size, float height, float half){
	float pos[2];

	// Left
	pos[0] = entry->pos[0]+half;
	pos[1] = entry->pos[1]-size;
	pile = push(pile, newEntry(pos));

	// Right
	pos[1] = entry->pos[1]+size;
	pile = push(pile, newEntry(pos));

	// Up
	pos[0] = entry->pos[0]-height-half;
	pos[1] = entry->pos[1];
	pile = push(pile, newEntry(pos));

	return pile;
}
