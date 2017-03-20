#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

bool allocateResource(char **res, char type, char units) {
	for (int i = 0; (*res)[i] != 0; i++) {
		if ((*res)[i] == type && (*res)[i + 1] == ' ') {
			(*res)[i + 2] = ((*res)[i + 2] - units + '0' >= '0' ? (*res)[i + 2] - units + '0' : '0');
			printf("Resource %c is now at %c\n", (*res)[i], (*res)[i + 2]);
			return true;
		}
	}
	return false;
}

int singleCharacter() {
	int character;
	character = getchar();
	while ('\n' != getchar())
		;
	return character;
}

int main(void) {
	int   resourseFile, fileSize;
	char *res;
	char  resNum, numRes;
	resourseFile = open("res.txt", O_RDWR);
	fileSize     = lseek(resourseFile, 0, SEEK_END);

	if (resourseFile == -1) {
		printf("File not found\n");
		return 1;
	}

	res = mmap((uintptr_t)0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, resourseFile, 0);

	if (res == MAP_FAILED) {
		printf("Memory map failed\n");
		return 1;
	}

	while (1) {
		printf("Allocate more resources (y/n)? ");
		if (singleCharacter() != 'y')
			exit(0);
		printf("Enter the resource number and number of resources needed: ");
		resNum = singleCharacter();
		numRes = singleCharacter();

		if (!allocateResource(&res, resNum, numRes))
			printf("Resource allocation failed\n");

		if (msync(res, fileSize, MS_SYNC) != 0) {
			printf("Could not synchronize file data\n");
			exit(1);
		}
	}

	return 0;
}
