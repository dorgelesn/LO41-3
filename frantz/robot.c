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

void prendre(int *c, struct Piece *stock, int i) {
	int compt = *c;
	int pos = index[i];
	if ((compt == 0)
			&& ((testOp[i](Anneau[pos], 1)) || (testOp[i](Anneau[pos], 2))
					|| (testOp[i](Anneau[pos], 3)))) {
		printf("robot %d: prend piece: %d \n", i + 1, Anneau[pos].numProduit);
		stock[0] = Anneau[pos];
		Anneau[pos] = PieceNull;
		compt++;
	}
	//on ne peut prendre qu'une piece deja prise
	else if (testPiece(Anneau[pos], stock[0].numProduit, stock[0].etat)) {
		printf("robot %d: prend piece: %d \n", i + 1, Anneau[pos].numProduit);
		stock[compt] = Anneau[pos];
		Anneau[pos] = PieceNull;
		compt++;
	} else {
		printf("robot %d: piece %d incorrecte \n", i + 1,
				Anneau[pos].numProduit);
	}
	*c = compt;
}

void poser(struct Piece piece, int index) {

	int compt;
	if (testPiece(piece, 1, 5))
		compt = 10;
	else if (testPiece(piece, 2, 5))
		compt = 15;
	else if (testPiece(piece, 3, 6))
		compt = 12;
	else if (testPiece(piece, 4, 4))
		compt = 8;
	else
		compt = 1;

	while (1) {

		pthread_mutex_lock(&lock);
		if (testPiece(Anneau[index], 0, 0)) {
			Anneau[index] = piece;
			compt--;

			pthread_mutex_unlock(&lock);
			if (compt == 0)
				return;
		}
		pthread_mutex_unlock(&lock);
		usleep(10);
	}
}

void * Robot(int num) {
	int compt = 0;
	struct Piece stock[3];
	while (1) {

		if ((compt == 1) && (testPiece(stock[0], 0, 0))) {
			printf("robot %d: rejet piece erreur", num + 1);
			compt = 0;
		}
		pthread_mutex_lock(&lock);
		prendre(&compt, stock, num); //attention
		pthread_mutex_unlock(&lock);

		if (testOp[num](stock[0], compt)) {
			printf("lancement de l'op %d \n", num + 1);
			usleep(10);
			struct Piece tampom = Op[num](stock);
			if (!testPiece(tampom, 0, 0)) {
				poser(tampom, index[num]); //attention
				compt = 0;
			}
		}
		usleep(11);
	}
	pthread_exit(NULL );
}
