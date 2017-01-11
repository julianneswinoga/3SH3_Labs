#include <stdio.h>
#include <sys/mman.h>

int main(void) {
	FILE *resourseFile;
	void *res;
	int len = 2048;
	resourseFile = fopen("res.txt", "w");
	res = mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, resourseFile, 0);
	fclose(resourseFile); // Close input file

	if (res == MAP_FAILED) {
		printf("Memory map failed\n");
		return 1;
	}

	return 0;
}
