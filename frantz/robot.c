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
	if ((compt == 0) && ((testOp[i](Anneau[pos],1)) ||(testOp[i](Anneau[pos],3)))) {
		printf("robot %d: prend piece: %d \n",i+1, Anneau[pos].numProduit);
		stock[0] = Anneau[pos];
		Anneau[pos] = newPiece(0, 0);
		compt++;
	}
	//on ne peut prendre qu'une piece deja prise
	else if (testPiece(Anneau[pos], stock[0].numProduit, stock[0].etat)) {
		printf("robot %d: prend piece: %d \n",i+1, Anneau[pos].numProduit);
		stock[compt] = Anneau[pos];
		Anneau[pos] = newPiece(0, 0);
		compt++;
	} else {
		printf("robot %d: piece %d incorrecte",i+1, Anneau[pos].numProduit);
	}
	*c = compt;
}

void poser(struct Piece piece, int index) {
	while (1) {
		pthread_mutex_lock(&lock);
		if (testPiece(Anneau[index], 0, 0)) {
			Anneau[index] = piece;
			pthread_mutex_unlock(&lock);
			return;
		}
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
}

void * Robot(int num) {
	int compt = 0;
	struct Piece stock[3];
	printf("Je suis le Robot n°% ",num+1);
	while (1) {

		pthread_mutex_lock(&lock);
		prendre(&compt, stock, num);//atention
		pthread_mutex_unlock(&lock);

		if (testOp[num](stock[0], compt)) {
			printf("lancement de l'op1");
			sleep(1);
			struct Piece tampom = Op[num](stock);
			if (!testPiece(tampom, 0, 0)) {
				poser(tampom, index[num]);//attention
				compt = 0;
			}
		}
		sleep(1);
	}
	pthread_exit(NULL );
}
