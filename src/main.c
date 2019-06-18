#include "main.h"

int main(int argc, char *argv[]){
	FILE *fp;
	char *buffer;

	fp = open_file(argc, argv);

	init_file(fp, TYPE, &buffer);
	
	drawFractal(fp, buffer, W*99/100, ITERATIONS);

	close_file(fp);
	free((char *)buffer);

	return 0;
}
