#include "draw.h"


FILE *open_file(int argc, char *argv[]){
	FILE *fp;
	char filename[NFILENAME+NEXTENSION+1];
	int n;

	if(argc>1){
		n = strlen(argv[1]);
		if(n>NFILENAME)
			n = NFILENAME;

		strncpy(filename, argv[1], n);
	}
	else{
		n = strlen(FILENAME);
		strncpy(filename, FILENAME, n);
	}

	strncpy(filename+n, EXTENSION, NEXTENSION);
	filename[n+NEXTENSION] = '\0';

	if((fp = fopen(filename, "w+")) == NULL){
		printf("Error opening file \"%s\"\nExited.\n", filename);
		perror("fopen");
		exit(-1);
	}
	else
		printf("Opened file \"%s\"\n", filename);

	W = WIDTH;
	H = HEIGHT;

	return fp;
}


void close_file(FILE *fp){
	fclose(fp);
	printf("Closed file\n");
}	


void init_file(FILE *fp, int type, char **buffer){
	O = 0;
	switch(type){
		case 4:
			O += fprintf(fp, "P4\n");
			break;
	}

	O += fprintf(fp, "%u %u\n", W, H);

	N = (W-1)/BYTE + 1;		// chars per line. number is ceiled
	T = N*H;

	char c;
	if(INVERTED)
		c = -1;
	else
		c = 0;

	*buffer = (char *) malloc(T);

	for(int i=0; i<T; i++){
		(*buffer)[i] = c;
		if(STEPS)
			fputc(c, fp);
	}

	return;
}


void write_bit(char buffer[], unsigned int i, unsigned int j, char state){
	unsigned int i1 = i*N + j/BYTE;
	unsigned int i2 = j%BYTE;

	if(PRINT)
		printf("(%d, %d) - %c\n", i, j, state);

	if(i<0 || i>=H || j<0 || j>=W){
		printf("Out of range. Clipping\n");
		if(i<0)
			i=0;
		else if(i>=H)
			i=H-1;
		if(j<0)
			j=0;
		else if(j>=W)
			j=W-1;
	}

	char c = buffer[i1];

	unsigned char mask;
	mask = 1;
	mask = mask<<(BYTE-1-i2);

	if(INVERTED)
		state = state^(ON^OFF);

	if(state==ON){
		c = c | mask;
	}
	else if(state==OFF){
		mask = ~mask;
		c = c & mask;
	}
	else{
		printf("Unrecognized state: %c\n", state);
		return;
	}

	buffer[i1] = c;

	return;
}


void printBin(int num, int bits){
	int pow;
	int mask = 1 << (bits - 1);

	for(pow=0; pow<bits; pow++){
		printf("%d", (mask & num)>>(bits-pow-1));
		mask = mask>>1;
	}

	putchar('\n');
}


void drawTriangle(char buffer[], float pos[2], float side, float half, char state, char orientation){
	unsigned int i, j, imax, jmax;
	float dx, dy;
	
	dy = half;

	imax = roundFloat(pos[0]+dy);

	for(i=roundFloat(pos[0]-dy); i<imax; i++){
		switch(orientation){
			case UP:
				dx = (i-pos[0]+dy)/sqrt(3);
				break;
			case DOWN:
				dx = (pos[0]+dy-i)/sqrt(3);
				break;
		}

		jmax = roundFloat(pos[1]+dx);

		for(j=roundFloat(pos[1]-dx); j<jmax; j++){
			write_bit(buffer, i, j, state);
		}
	}
	
	return;
}


unsigned int roundFloat(float x){
	return (unsigned int)(x+0.5);
}


void drawAllTriangles(char buffer[], Entry *pile, float side, float half, char state, char orientation){
	for(; pile!=NULL; pile=pile->next)
		drawTriangle(buffer, pile->pos, side, half, state, orientation);

	return;
}


void readFractal(FILE *fp, char buffer[]){
	unsigned int count;

	fseek(fp, O, SEEK_SET);	// check if -1 or correct
	for(count=0; count<T; count++)
		buffer[count] = fgetc(fp);

	return;
}


void writeFractal(FILE *fp, char buffer[]){
	unsigned int count;

	fseek(fp, O, SEEK_SET);	// check if -1 or correct
	for(count=0; count<T; count++)
		fputc(buffer[count], fp);

	return;
}
