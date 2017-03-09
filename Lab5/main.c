#include <grp.h>
#include <pwd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void printStats(char name[]) {
	struct stat    fileStat;
	struct group * grp;
	struct passwd *pwd;

	stat(name, &fileStat);

	printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

	printf(" Links: %lu", fileStat.st_nlink);

	printf(" (%ldB, %lubl)", fileStat.st_size, fileStat.st_blocks);
	printf(" inode: %lu", fileStat.st_ino);

	printf(" %s", (S_ISLNK(fileStat.st_mode)) ? "S" : "-");

	pwd = getpwuid(fileStat.st_uid);
	grp = getgrgid(fileStat.st_gid);
	printf(" %s:%s", pwd != NULL ? pwd->pw_name : "NULL", grp != NULL ? grp->gr_name : "NULL");

	printf(" %s", name);

	printf(" %s", ctime(&fileStat.st_mtime));
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Need either a directory or a file\n");
		return 1;
	}

	printStats(argv[1]);

	return 0;
}
