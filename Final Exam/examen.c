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
int main(int argc, char* argv[]) {

    
    if (argc != 2 && argc!=4 && argc!=6) {
		fprintf(stderr, "usage: %s \n", argv[0] );
		return -1;
	}
}