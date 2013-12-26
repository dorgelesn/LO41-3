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
	//initialisation
	for(i =0; i<16;i++)
			{
				Anneau[i]= newPiece(i,0);
			}

	//simulation de rataion de l'anneau
	while(j<4)
	{
		struct Piece tampon1, tampon2;
	    pthread_mutex_lock(&lock);

		tampon1 = Anneau[0];
		for(i =0; i<16;i++)
		{
			tampon2 = Anneau[(i+1)%16];
			Anneau[(i+1)%16] = tampon1;
			tampon1 = tampon2;
		}

		//affichage de l'anneau
		for(i = 0; i<16;i++)
		{
			printf("Anneau %d: %d \n", i,Anneau[i].numProduit);
		}
	    pthread_mutex_unlock(&lock);

		printf("\n");
		j++;
	}

	return 0;
}

