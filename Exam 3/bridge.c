/*----------------------------------------------------------------

*

* Programación avanzada: Examen 3

* Fecha: 17-Sep-2020

* Autor: A01702686 Juan David Torres

*

*--------------------------------------------------------------*/

#include "header.h"

int main(int argc, char *argv[]) {
	key_t key;
	int semid, i, shmid, finished;

	if (argc != 1) {
		fprintf(stderr,"usage: %s\n", argv[0]);
		return -1;
	}

	if ((key = ftok("./null.txt", 120)) == (key_t) -1) {
        fprintf(stderr,"ERORR");
		perror(argv[0]);
		return -1;
	}

	if ((semid = semget(key, 3, 0666)) < 0) {
		perror(argv[0]);
		return -1;
	}

    if ( (shmid = shmget(key, sizeof(SharedVars), 0666)) < 0 ) {
		perror("shmid");
		return -1;
	} 
	
	SharedVars * sh;
	sh = (SharedVars*) shmat(shmid, (void*) 0, 0);
    while(1){
		
		
		sem_wait(semid,PASSING,1);
		fprintf(stderr,"Esta pasando un granjero por el puente\n");
		sem_wait(semid,PASSED,1);
        fprintf(stderr,"Ya paso el granjero\n\n");

	}
		
		
		
	
	

    shmdt(sh);
	
	semctl(semid, 0, IPC_RMID, 0);
	shmctl(shmid, IPC_RMID, 0);
	return 0;

}

