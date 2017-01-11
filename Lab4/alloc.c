#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

int main(void) {
	int resourseFile, pageSize;
	char *res;
	pageSize = getpagesize();
	resourseFile = open("res.txt", O_RDWR);

	if (resourseFile == -1) {
		printf("File not found\n");
		return 1;
	}

	res = mmap((uintptr_t)0, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, resourseFile, 0);

	if (res == MAP_FAILED) {
		printf("Memory map failed\n");
		return 1;
	}

	for (int i = 0; res[i] != 0; i++)
		printf(">%c\n", res[i]);

	return 0;
}
