#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pthread.h"

#define DELIM " "

int data[256][256] = { {0 } };
int height, width;

void bubblesort(int *array) {
	/*for (unsigned int i = 0; i < myArray->size(); i++)
	    for (unsigned int j = 0; j < myArray->size()-1; j++)
	        if (myArray->at(j) < myArray->at(j+1))
	            swap((*myArray)[j], (*myArray)[j+1]);
	*/
}

void debug_printData() {
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			printf("%s%i\t%s", x == 0 ? "|" : "", data[x][y], x == width - 1 ? "|\n" : "");
}

int main (void) {
	FILE *inputFile;
	char buf[255];
	int line;
	inputFile = fopen("input.txt", "r");

	for (line = 0; fgets(buf, sizeof(buf) / sizeof(char), (FILE*)inputFile) != NULL; line++) {
		char *p = strtok(buf, DELIM);

		for (int i = 0; p != NULL; i++) {
			data[line][i] = atoi(p);
			p = strtok(NULL, DELIM);
			width = i; // Set the data width
		}
	}

	fclose(inputFile); // Close input file
	height = line;
	debug_printData();
	///////////////////////////////////////SORT CODE
	pthread_exit(NULL); // Wait for all threads to stop execution
	return 0;
}
