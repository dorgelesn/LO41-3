/*
 * robot.c
 *
 *  Created on: 15 déc. 2013
 *      Author: kevin
 */

#include <stddef.h>
#include <pthread.h>

#include "piece.h"
#include "operation.h"
#include "main.h"

const int R1 = 2;

struct Piece prendre(int index)
{
    return Anneau[index];
}

void poser(struct Piece piece, int index)
{
    pthread_mutex_lock(&lock);
	Anneau[index] = piece;
    pthread_mutex_lock(&lock);

}

void Robot_1() {
	int compt = 0;
	struct Piece stock[3];

	while (1) {
		printf("Je suis le Robot n°1 ");

		pthread_mutex_lock(&lock);
		if(compt == 0)
		{
			stock[0] = prendre(R1);
		}
		//on ne peut prendre qu'une piece deja prise
		else if (testPiece(Anneau[R1], stock[0].numProduit, stock[0].etat))
		{
			stock[compt] = prendre(R1);
		}

	}
}
