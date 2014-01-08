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

void initialisation(int mode) {
	if (mode == 1) {
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
	} else {
		testOp[0] = testOpD1;
		testOp[1] = testOpD2;
		testOp[2] = testOpD3;
		testOp[3] = testOpD4;

		Op[0] = opD1;
		Op[1] = opD2;
		Op[2] = opD3;
		Op[3] = opD4;
	}
	int i;
	for (i = 0; i < 4; i++) {
		prod[i] = 0;
		aProd[i] = -1;
	}

	newCycle = 0;

	PieceNull.etat = 0;
	PieceNull.numProduit = 0;

}

void sortie() {
	if (testPiece(Anneau[SIZE_ANNEAU - 1], 1, 5)) {
		Anneau[SIZE_ANNEAU - 1] = PieceNull;
		prod[0]++;
	} else if (testPiece(Anneau[SIZE_ANNEAU - 1], 2, 5)) {
		Anneau[SIZE_ANNEAU - 1] = PieceNull;
		prod[1]++;
	} else if (testPiece(Anneau[SIZE_ANNEAU - 1], 3, 6)) {
		Anneau[SIZE_ANNEAU - 1] = PieceNull;
		prod[2]++;
	} else if (testPiece(Anneau[SIZE_ANNEAU - 1], 4, 4)) {
		Anneau[SIZE_ANNEAU - 1] = PieceNull;
		prod[3]++;
	}
}

void deposer(struct Piece piece) {
	if (testPiece(Anneau[0], 0, 0))
		Anneau[0] = piece;
}

void entrer() {
	if (newCycle == 0) {
		if ((prod[0] != aProd[0]) && (prod[1] != aProd[1])
				&& (prod[2] != aProd[2]) && (prod[3] != aProd[3]))
			if ((prod[0] % 10 == 0) && (prod[1] % 15 == 0)
					&& (prod[2] % 12 == 0) && (prod[3] % 8 == 0)) {
				newCycle = 1;
				stade = 1;
				aProd[0] = prod[0];
				aProd[1] = prod[1];
				aProd[2] = prod[2];
				aProd[3] = prod[3];
			}
	}
	if (newCycle == 1) {
		if ((stade <= 3) && (ResteProd[0] > 0)) {
			deposer(newPiece(1, 1));
			ResteProd[0]--;
		} else if ((stade > 3) && (stade <= 6) && (ResteProd[1] > 0)) {
			deposer(newPiece(2, 1));
			ResteProd[1]--;
		} else if ((stade == 7) && (ResteProd[2] > 0)) {
			deposer(newPiece(3, 1));
			ResteProd[2]--;
		} else if ((stade > 7) && (ResteProd[3] > 0)) {
			deposer(newPiece(4, 1));
			ResteProd[3]--;
		}
		stade++;
		if (stade == 10)
			newCycle = 0;
	}

}

int divP(int q, int d, int multip) {
	if (q % d == 0)
		return (q / d) * multip;
	else
		return ((q / d) + 1) * multip;
}

void calculeProd() {
	ResteProd[0] = divP(Demande[0], 10, 3);
	ResteProd[1] = divP(Demande[1], 15, 3);
	ResteProd[2] = divP(Demande[2], 12, 1);
	ResteProd[3] = divP(Demande[3], 8, 2);
}

int main(void) {
	int j = 0;
	int i;

	int mode = 0;
	while ((mode < 1) || (mode > 2)) {
		printf("Selecttionnez un mode: \n");
		printf("\t - Mode Normale : 1 \n");
		printf("\t - Mode Dégrader : 2 \n");
		scanf("%d", &mode);
	}
	initialisation(mode);

	printf("Bonjour, nous allons lancer la production.");
	for (i = 1; i < 5; i++) {
		printf("\n Combien de produit %d faut-il produire :", i);
		scanf("%d", &Demande[i]);
	}
	calculeProd();

	pthread_t thread[6];

	//creation des threads
	int nbRobot;
	if (mode == 1)
		nbRobot = 6;
	else nbRobot = 4;
	for (i = 0; i < nbRobot; i++) {
		pthread_create(&thread[i], NULL, Robot, i);
		usleep(2);
	}

	//simulation de rataion de l'anneau
	while (j < 1000) {
		struct Piece tampon1, tampon2;
		pthread_mutex_lock(&lockAnneau);

		entrer();
		sortie();

		tampon1 = Anneau[0];
		for (i = 0; i < SIZE_ANNEAU; i++) {
			tampon2 = Anneau[(i + 1) % SIZE_ANNEAU];
			Anneau[(i + 1) % SIZE_ANNEAU] = tampon1;
			tampon1 = tampon2;
		}

		//affichage de l'anneau
		printf("    -------tour %d-------    \n", j);
		for (i = 0; i < SIZE_ANNEAU; i++) {
			printf("Anneau %d: %d : %d \n", i, Anneau[i].numProduit,
					Anneau[i].etat);
		}
		pthread_mutex_unlock(&lockAnneau);
		usleep(100);

		printf("\n");
		j++;
	}
	//wait(NULL);

	printf(
			"\n Il a était produit:\n - %d produit 1\n - %d produit 2\n - %d produit 3\n - %d produit 4\n",
			prod[0], prod[1], prod[2], prod[3]);
	printf("\n newcycle : %d", newCycle);
	return 0;
}

