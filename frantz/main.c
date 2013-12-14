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

volatile int Anneau[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

int main (void)
{
	int j = 0;
	while(j<4)
	{
		int tampon1, tampon2;
		int i;
		tampon1 = Anneau[0];
		for(i =0; i<16;i++)
		{
			tampon2 = Anneau[(i+1)%16];
			Anneau[(i+1)%16] = tampon1;
			tampon1 = tampon2;
		}


		for(i = 0; i<16;i++)
		{
			printf("Anneau %d: %d \n", i,Anneau[i]);
		}
		printf("\n");
		j++;
	}

	return 0;
}

