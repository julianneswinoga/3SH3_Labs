#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int printRecursiveStats(char name[]) {
	struct stat    fileStat;
	struct group * grp;
	struct passwd *pwd;

	stat(name, &fileStat);

	printf(S_ISDIR(fileStat.st_mode) ? "d" : "-");
	printf(fileStat.st_mode & S_IRUSR ? "r" : "-");
	printf(fileStat.st_mode & S_IWUSR ? "w" : "-");
	printf(fileStat.st_mode & S_IXUSR ? "x" : "-");
	printf(fileStat.st_mode & S_IRGRP ? "r" : "-");
	printf(fileStat.st_mode & S_IWGRP ? "w" : "-");
	printf(fileStat.st_mode & S_IXGRP ? "x" : "-");
	printf(fileStat.st_mode & S_IROTH ? "r" : "-");
	printf(fileStat.st_mode & S_IWOTH ? "w" : "-");
	printf(fileStat.st_mode & S_IXOTH ? "x" : "-");

	printf(" Links: %lu", fileStat.st_nlink);

	printf(" (%ldB, %lubl)", fileStat.st_size, fileStat.st_blocks);
	printf(" inode: %lu", fileStat.st_ino);

	printf(" %s", (S_ISLNK(fileStat.st_mode)) ? "S" : "-");

	pwd = getpwuid(fileStat.st_uid);
	grp = getgrgid(fileStat.st_gid);
	printf(" %s:%s", pwd != NULL ? pwd->pw_name : "NULL", grp != NULL ? grp->gr_name : "NULL");

	printf(" %s", name);

	printf(" %s", ctime(&fileStat.st_mtime));

	if (S_ISDIR(fileStat.st_mode)) {
		DIR *          pDir;
		struct dirent *pDirent;

		printf("Entering directory %s\n", name);

		pDir = opendir(name);
		if (pDir == NULL) {
			printf("Cannot open directory %s\n", name);
			return 1;
		}

		while ((pDirent = readdir(pDir)) != NULL) {
			if (strcmp(pDirent->d_name, ".") != 0 && strcmp(pDirent->d_name, "..") != 0) {
				if (printRecursiveStats(pDirent->d_name) != 0) {
					printf("Error retieving stats for %s\n", pDirent->d_name);
					return 1;
				}
			}
		}
		printf("Exiting directory %s\n", name);
		closedir(pDir);
	}

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Need either a directory or a file\n");
		return 1;
	}

	return printRecursiveStats(argv[1]);
}
