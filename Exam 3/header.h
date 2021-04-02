/*----------------------------------------------------------------

*

* Programación avanzada: Examen 3

* Fecha: 17-Sep-2020

* Autor: A01702686 Juan David Torres

*

*--------------------------------------------------------------*/
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define	PASSING 	0
#define	PASSED	1
#define MUTEX	2

typedef struct {
	
    int farmersNorth;
    int farmersSouth;
	int actualSouth;
	int actualNorth;
	int intercalar;
	//Si es 1 el anterior fue sur y si es 0 el anterior fue norte
	

} SharedVars;


int sem_wait(int semid, int sem_num, unsigned int val) {
	struct sembuf op;
	
	op.sem_num = sem_num;
	op.sem_op = -val;
	op.sem_flg = 0;
	return semop(semid, &op, 1);
}

int sem_signal(int semid, int sem_num, unsigned int val) {
	struct sembuf op;
	
	op.sem_num = sem_num;
	op.sem_op = val;
	op.sem_flg = 0;
	return semop(semid, &op, 1);
}

#endif