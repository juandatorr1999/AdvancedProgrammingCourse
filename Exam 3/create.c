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
	int semid, i, shmid;

	if (argc != 1) {
        
		fprintf(stderr,"usage: %s \n", argv[0]);
		return -1;
	}

    if ((key = ftok("./null.txt", 120)) == (key_t) -1) {
        
		perror(argv[0]);
		return -1;
	}

	if ((semid = semget(key, 3, 0666 | IPC_CREAT)) < 0) {
        
		perror(argv[0]);
		return -1;
	}

    semctl(semid, PASSING, SETVAL, 0);
	semctl(semid, PASSED, SETVAL, 0);

	semctl(semid, MUTEX, SETVAL, 1);
    if ( (shmid = shmget(key, sizeof(SharedVars), 0666 | IPC_CREAT)) < 0 ) {
		semctl(semid, 0, IPC_RMID, 0);
		perror("shmid");
		return -1;
	} 	
	
	SharedVars * sh;
	sh = (SharedVars*) shmat(shmid, (void*) 0, 0);
	sh->actualNorth=0;
	sh->actualSouth=0;
	sh->intercalar = 0;
	shmdt(sh);

    fprintf(stderr,"Semaphore created...\n");

    return 0;
}