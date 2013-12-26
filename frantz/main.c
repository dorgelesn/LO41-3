/*
 * Main.c
 *
 *  Created on: 14 déc. 2013
 *      Author: kevin
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "piece.h"
#include "robot.h"
#include "main.h"

int main (void){
	int j = 0;
	int i;

	pthread_t thread1;
	int pid = getpid();
	//initialisation
	for(i =0; i<SIZE_ANNEAU;i++)
			{
				Anneau[i]= newPiece(i,0);
			}

	//simulation de rataion de l'anneau
	while(j<4)
	{
		struct Piece tampon1, tampon2;
	    pthread_mutex_lock(&lock);

		tampon1 = Anneau[0];
		for(i =0; i<SIZE_ANNEAU;i++)
		{
			tampon2 = Anneau[(i+1)%SIZE_ANNEAU];
			Anneau[(i+1)%SIZE_ANNEAU] = tampon1;
			tampon1 = tampon2;
		}

		//affichage de l'anneau
		for(i = 0; i<SIZE_ANNEAU;i++)
		{
			printf("Anneau %d: %d \n", i,Anneau[i].numProduit);
		}
	    pthread_mutex_unlock(&lock);

		printf("\n");
		j++;
	}

	return 0;
}

