//Juan David Torres A01702686
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>

// jmp_buf env1
// void handler(int sig){
// 	if (sig == SIGUSR1) {
// 		longjmp(env1, 1);
//   	} 
// }

void list(char* dir_name, int size, char* programfile);

int main(int argc, char* argv[]) {

	int pid,timeFlag, sizeFlag, time, size;
	// signal(SIGUSR1,handler);
    if (argc != 2 && argc!=4 && argc!=6) {
		fprintf(stderr, "usage: %s directory [-t seconds] [-q size]\n", argv[0] );
		return -1;
	}


	if (argc == 4 ) {
		if (strcmp(argv[2], "-t") == 0) {
			timeFlag = 1;
			printf("");
			time = atoi(argv[3]);
		} 
		else if (strcmp(argv[2], "-q") == 0) {
			sizeFlag = 1;
			printf("");
			size = atoi(argv[3]);
		}  
		else {
			fprintf(stderr, "usage: %s directory [-t seconds] [-q size]\n", argv[0]);
			return -4;
		}
	}
	if (argc == 6 ) {
		if (strcmp(argv[2], "-t") == 0) {
			timeFlag = 1;
			printf("");
			time = atoi(argv[3]);
			if (strcmp(argv[4], "-q") == 0){
				sizeFlag = 1;
				printf("");
				size = atoi(argv[5]);
			}else {
				fprintf(stderr, "usage: %s directory [-t seconds] [-q size]\n", argv[0]);
				return -4;
			}
		} 
		else if (strcmp(argv[2], "-q") == 0) {
			sizeFlag = 1;
			printf("");
			size = atoi(argv[3]);

			if (strcmp(argv[4], "-t") == 0){
				timeFlag = 1;
				printf("");
				time = atoi(argv[5]);
			}else {
				fprintf(stderr, "usage: %s directory [-t seconds] [-q size]\n", argv[0]);
				return -4;
			}
		}  
		else {
			fprintf(stderr, "usage: %s directory [-t seconds] [-q size]\n", argv[0]);
			return -4;
		}
	}
	if(sizeFlag==1){
		if(size<=0){
			fprintf(stderr, "%s: size must be greater than 0 KBytes\n", argv[0]);
			return -4;
		}
	}
	if(timeFlag==1){
		if(time<=0){
			fprintf(stderr, "%s: seconds must be greater than 0 seconds \n", argv[0]);
			return -4;
		}
	}

	if(sizeFlag!=1){
		size = 1;
	}
	if(timeFlag!=1){
		time = 60;
	}

	
	// while (1){
	// 	wait(time)
	// 	kill(pid,SIGUSR1)
	// }

	if ( (pid = fork()) < 0 ) {
		perror("fork");
		return -2;
	} else if (pid == 0) {
		// setjmp(env2);
		list(argv[1],size,argv[0]);
		while(1){
			sleep(time);
			list(argv[1],size,argv[0]);
		}
	} else {
		wait(NULL);
	}
	
	return 0;

}



void list(char* dir_name, int size, char *program) {
	char path[PATH_MAX + NAME_MAX + 1];
	char filename[PATH_MAX + NAME_MAX + 1];
	DIR *dir;
	struct dirent *direntry;
	struct stat info;
	


	if ( (dir = opendir(dir_name)) == NULL ) {
		perror(program);
		exit(-3);
	}


	
	while( (direntry = readdir(dir)) != NULL) {
		sprintf(filename, "%s/%s", dir_name, direntry->d_name);
		lstat(filename, &info);
		printf("directory= %s - size = %lli\n",dir_name,info.st_size/1000);
		if ((info.st_size/1000)>size)
		{
			fprintf(stderr,"the directory %s has exceeded size %i",dir_name,size);
		}
		
		// printf("directory: %s\n", dir_name);
		

	}
	
		rewinddir(dir);
		while ( (direntry = readdir(dir)) != NULL ) {
			if (strcmp(direntry->d_name, ".") != 0 &&
				strcmp(direntry->d_name, "..") != 0) {
				sprintf(path, "%s/%s", dir_name, direntry->d_name);
				lstat(path, &info);
				if ( (info.st_mode & S_IFMT) == S_IFDIR) {
					list(path, size, program);
				}
			}
		}
		closedir(dir);
	
	
		
}