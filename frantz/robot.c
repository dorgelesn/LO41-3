/*
 * robot.c
 *
 *  Created on: 15 déc. 2013
 *      Author: kevin
 */

#include <stddef.h>
#include <pthread.h>
#include <time.h>

#include "piece.h"
#include "operation.h"
#include "main.h"

const int R1 = 2;

struct Piece prendre(int index) {
	struct Piece tampon = Anneau[index];
	Anneau[index] = newPiece(0, 0);
	return tampon;
}

void poser(struct Piece piece, int index) {
	while (1) {
		pthread_mutex_lock(&lock);
		if (testPiece(Anneau[index],0,0)) {
			Anneau[index] = piece;
			pthread_mutex_unlock(&lock);
			return;
		}
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
}

void * Robot_1(void *arg) {
	int compt = 0;
	struct Piece stock[3];
	printf("Je suis le Robot n°1 ");
	while (1) {

		pthread_mutex_lock(&lock);
		if (compt == 0) {
			printf("prend piece: %d \n", Anneau[R1].numProduit);
			stock[0] = prendre(R1);
			compt++;
		}
		//on ne peut prendre qu'une piece deja prise
		else if (testPiece(Anneau[R1], stock[0].numProduit, stock[0].etat)) {
			printf("prend piece: %d \n", Anneau[R1].numProduit);
			printf("a deja piece: %d \n", stock[0].numProduit);
			stock[compt] = prendre(R1);
			compt++;
		} else {
			printf("piece %d incorrecte", Anneau[R1].numProduit);
		}
		pthread_mutex_unlock(&lock);

		if (testOp1(stock[0], compt)) {
			printf("lancement de l'op1");
			sleep(1);
			struct Piece tampom = op1(stock);
			if (!testPiece(tampom, 0, 0)) {
				poser(tampom, R1);
				compt = 0;
			}
		}

		sleep(1);
	}
	pthread_exit(NULL );
}
