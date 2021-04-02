
#include "header.h"

void pass_bridgeS(int id) {
	key_t key;
	int semid, i, shmid;
	
	if ((key = ftok("./null.txt", 120)) == (key_t) -1) {
		perror("ftok");
		exit(-1);
	}

	if ((semid = semget(key, 3, 0666)) < 0) {
        fprintf(stderr,"FALLO..\n");
		perror("semid");
		exit(-1);
	}
	
	if ( (shmid = shmget(key, sizeof(SharedVars), 0666)) < 0 ) {
		perror("shmid");
		exit(-1);
	} 
	
	SharedVars * sh;
	sh = (SharedVars*) shmat(shmid, (void*) 0, 0);
	srand( getpid() );
    while (1)
    {
		sleep(1);
		if(sh->actualSouth<5 && sh->actualNorth==0 && sh->intercalar==1 ){

			sem_wait(semid,MUTEX,1);
			sh->actualSouth++;
			if(sh->actualSouth==5){
				sh->intercalar=0;
			}
			sem_signal(semid,MUTEX,1);

            sem_signal(semid,PASSING,1);
            fprintf(stderr,"El granjero del sur %i esta pasando\n",id);
            sleep((rand() % 5) + 3);
            sem_signal(semid,PASSED,1);
            fprintf(stderr,"El granjero del sur %i ya paso\n\n",id);
            sem_wait(semid,MUTEX,1);
            sh->actualSouth--;
            sh->farmersSouth--;
            if(sh->farmersSouth==0){
				sh->intercalar=0;
			}
            sem_signal(semid,MUTEX,1);
            shmdt(sh);
            exit(0);
        }else if(sh->actualSouth==5|| sh->farmersSouth==0){
			sh->intercalar=0;
		}
        
        
    }
    
	


	
	exit(0);
}

void pass_bridgeN(int id) {
	key_t key;
	int semid, i, shmid;
	
	if ((key = ftok("./null.txt", 120)) == (key_t) -1) {
		perror("ftok");
		exit(-1);
	}

	if ((semid = semget(key, 3, 0666)) < 0) {
		perror("semid");
		exit(-1);
	}
	
	if ( (shmid = shmget(key, sizeof(SharedVars), 0666)) < 0 ) {
		perror("shmid");
		exit(-1);
	} 
	srand( getpid() );
	SharedVars * sh;
	sh = (SharedVars*) shmat(shmid, (void*) 0, 0);
    while (1)
    { 
        if(sh->actualNorth<5 && sh->actualSouth==0 && sh->intercalar==0 ){
            
            
			sem_wait(semid,MUTEX,1);
			sh->actualNorth++;
			if(sh->actualNorth==5){
				sh->intercalar=1;
			}
			sem_signal(semid,MUTEX,1);
            sem_signal(semid,PASSING,1);
            fprintf(stderr,"El granjero del norte %i esta pasando\n",id);
			sleep((rand() % 5) + 3);
            sem_signal(semid,PASSED,1);
            sem_wait(semid,MUTEX,1);
            sh->farmersNorth--;
			sh->actualNorth--;
            if(sh->farmersNorth==0){
				sh->intercalar=1;
			}
            fprintf(stderr,"El granjero del norte %i ya paso\n\n",id);
            
            sem_signal(semid,MUTEX,1);
            shmdt(sh);
            exit(0);
		}else if(sh->actualNorth == 5 || sh->farmersNorth==0)
		{
			sh->intercalar=1;
		}
		
        
        
    }
    
	
    exit(0);

	
}

int main(int argc, char *argv[]) {
	int i, pid, farmersN,farmersS;
    key_t key;
	int shmid;
	
	if (argc != 3) {
		fprintf(stderr,"usage: %s farmers_north farmers_south\n", argv[0]);
		return -1;
	}
    farmersN = atoi(argv[1]);
    farmersS = atoi(argv[2]);

    if (farmersN<0)
    {
        fprintf(stderr,"The number of farmers north has to be positive\n");
		return -1;
    }
    if (farmersS<0)
    {
        fprintf(stderr,"The number of farmers south has to be positive\n");
		return -1;
    }
	
	if ((key = ftok("./null.txt", 120)) == (key_t) -1) {
		perror("ftok");
		exit(-1);
	}
	
	if ( (shmid = shmget(key, sizeof(SharedVars), 0666)) < 0 ) {
		perror("shmid");
		exit(-1);
	} 
	
	SharedVars * sh;
	sh = (SharedVars*) shmat(shmid, (void*) 0, 0);
    sh->farmersNorth = farmersN;
    sh->farmersSouth = farmersS;
    
	//Va a generar 7 customers
	for (i = 0; i < farmersN; i++) {
		if ( (pid = fork()) < 0 ) {
			perror("fork");
			exit(-1);
		} else if (pid == 0) {
			pass_bridgeN(i);
		} else {
			// do nothing
		}
	}
	for (i = 0; i < farmersS; i++) {
		if ( (pid = fork()) < 0 ) {
			perror("fork");
			exit(-1);
		} else if (pid == 0) {
			pass_bridgeS(i);
		} else {
			// do nothing
		}
	}
	while (i > 0) {
		wait(NULL);
		i--;
	}
	shmdt(sh);
	return 0;
}