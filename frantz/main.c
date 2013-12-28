/*
 * Main.c
 *
 *  Created on: 14 déc. 2013
 *      Author: kevin
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "piece.h"
#include "operation.h"
#include "robot.h"
#include "main.h"

void initialisation() {
	testOp[0] = testOp1;
	testOp[1] = testOp2;
	testOp[2] = testOp3;
	testOp[3] = testOp4;
	testOp[4] = testOp5;
	testOp[5] = testOp6;

	Op[0] = op1;
	Op[1] = op2;
	Op[2] = op3;
	Op[3] = op4;
	Op[4] = op5;
	Op[5] = op6;

}
int main(void) {
	int j = 0;
	int i;

	initialisation();

	pthread_t thread[6];
	//pid_t pid = getpid();
	//initialisation
	for (i = 0; i < SIZE_ANNEAU; i++) {
		Anneau[i] = newPiece(4, 1);
	}

	//creation des threads
	for(i =0; i<6;i++)
	{
		pthread_create(&thread[i], NULL, Robot, i );
		usleep(2);
	}

	//simulation de rataion de l'anneau
	while (j < 1000) {
		struct Piece tampon1, tampon2;
		pthread_mutex_lock(&lock);

		tampon1 = Anneau[0];
		for (i = 0; i < SIZE_ANNEAU; i++) {
			tampon2 = Anneau[(i + 1) % SIZE_ANNEAU];
			Anneau[(i + 1) % SIZE_ANNEAU] = tampon1;
			tampon1 = tampon2;
		}

		//affichage de l'anneau
		for (i = 0; i < SIZE_ANNEAU; i++) {
			printf("Anneau %d: %d : %d \n", i, Anneau[i].numProduit,
					Anneau[i].etat);
		}
		pthread_mutex_unlock(&lock);
		usleep(20);

		printf("\n");
		j++;
	}

	return 0;
}

