#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "stdint.h"
#include "pthread.h"

#define FILE_DELIM " "
#define MAX_THREADS 16

int data[256][256] = { {0 } };
int meshSize, threadIds[MAX_THREADS];
bool threadWorkDone[MAX_THREADS] = {0, };
pthread_t threads[MAX_THREADS];
pthread_mutex_t mutex_data, mutex_phaseComplete;
pthread_cond_t condition_phaseComplete;

void bubblesort(int array[], int len, bool reverse) {
	int temp;

	for (unsigned int i = 0; i < len - 1; i++) {
		for (unsigned int j = 0; j < len - i - 1; j++) {
			if (array[j + (reverse ? 1 : 0)] > array[j + (reverse ? 0 : 1)]) {
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

void printData() {
	for (int y = 0; y < meshSize; y++)
		for (int x = 0; x < meshSize; x++)
			printf("%s%i\t%s", x == 0 ? "|" : "", data[y][x], x == meshSize - 1 ? "|\n" : "");
}

bool allThreadsComplete() {
	for (int i = 0; i < meshSize; i++) {
		if (!threadWorkDone[i])
			return false;
	}

	return true;
}

void *meshThreadFunc(void *arg) {
	printf("#%i Created\n", arg);
	int arrayCopy[meshSize];
	int threadNumber = (int)(uintptr_t)arg;

	for (int phase = 0; phase <= ceil(log2(meshSize + 1.0)); phase++) {
		if (phase % 2 == 0) { // Column sort
			for (int i = 0; i < meshSize; i++)
				arrayCopy[i] = data[i][threadNumber]; // Copy column data

			bubblesort(arrayCopy, meshSize, false);
			pthread_mutex_lock(&mutex_data);

			for (int i = 0; i < meshSize; i++) // Write new column data
				data[i][threadNumber] = arrayCopy[i];

			pthread_mutex_unlock(&mutex_data);

		} else { // Row sort
			for (int i = 0; i < meshSize; i++)
				arrayCopy[i] = data[threadNumber][i]; // Copy row data

			if (threadNumber % 2 == 0) { // Increasing from left to right
				bubblesort(arrayCopy, meshSize, false);

			} else { // Decreasing from left to right
				bubblesort(arrayCopy, meshSize, true);
			}

			pthread_mutex_lock(&mutex_data);

			for (int i = 0; i < meshSize; i++) // Write new row data
				data[threadNumber][i] = arrayCopy[i];

			pthread_mutex_unlock(&mutex_data);
		}

		printf("#%i done phase %i\n", threadNumber, phase);
		threadWorkDone[threadNumber] = true;

		if (!allThreadsComplete()) { // If not all threads are complete, wait
			pthread_mutex_lock(&mutex_phaseComplete);
			pthread_cond_wait(&condition_phaseComplete, &mutex_phaseComplete); // Wait for phases to complete
			pthread_mutex_unlock(&mutex_phaseComplete);

		} else {
			for (size_t i = 0; i < meshSize; i++)
				threadWorkDone[i] = false; // Reset thread work

			printf("#%i is the last thread!\n", threadNumber);
			pthread_cond_broadcast(&condition_phaseComplete); // Broadcast that we can proceed
		}
	}

	pthread_exit(NULL);
}

int main (void) {
	FILE *inputFile;
	char buf[255];
	int line;
	pthread_attr_t attr;
	inputFile = fopen("input.txt", "r");

	for (line = 0; fgets(buf, sizeof(buf) / sizeof(char), (FILE*)inputFile) != NULL; line++) {
		char *p = strtok(buf, FILE_DELIM);

		for (int i = 0; p != NULL; i++) {
			data[line][i] = atoi(p);
			p = strtok(NULL, FILE_DELIM);
		}
	}

	fclose(inputFile); // Close input file
	meshSize = line; // Set the size of the mesh

	if (meshSize > MAX_THREADS) {
		printf("Error, too many threads needed to sort.");
		return 1;
	}

	printData(); // Print unsorted data
	pthread_mutex_init(&mutex_data, NULL); // Init mutex for data
	pthread_mutex_init(&mutex_phaseComplete, NULL); // Init mutex for phase complete
	pthread_cond_init (&condition_phaseComplete, NULL); // Init condition for phase complete
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (int i = 0; i < meshSize; i++) { // Create $(meshSize) threads
		threadIds[i] = i;
		pthread_create(&threads[i], &attr, meshThreadFunc, (void*)(uintptr_t)threadIds[i]);
	}

	pthread_attr_destroy(&attr);

	for (int i = 0; i < meshSize; i++) { // Join all $(meshSize) threads
		void *status;
		pthread_join(threads[i], &status);

		if (status != 0) {
			printf("Thread #%i exited with %i\n", i, status);
			return 1;
		}
	}

	printData(); // Print sorted data
	pthread_mutex_destroy(&mutex_data); // Destroy mutex
	pthread_exit(NULL); // Wait for all threads to stop execution
	return 0;
}
