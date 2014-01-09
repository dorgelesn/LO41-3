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
		Demande[0] = 0;
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
	//on teste si on le cycle est en cours
	if (newCycle == 0) {
		//cycle en cour
		if ((prod[0] != aProd[0]) || (prod[1] != aProd[1])
				|| (prod[2] != aProd[2]) || (prod[3] != aProd[3]))
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
		//debut d'un nouveau cycle, on insert les composant
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
		int i;

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
	printf("\n debut calcluleprod ");
	ResteProd[0] = divP(Demande[0], 10, 3);
	ResteProd[1] = divP(Demande[1], 15, 3);
	ResteProd[2] = divP(Demande[2], 12, 1);
	ResteProd[3] = divP(Demande[3], 8, 2);

	int i;
	for(i=0;i<4;i++)
	{
		printf("resprod : %d \t demande: %d", ResteProd[i], Demande[i]);
	}
}

int finProd() {
	//test que la production demander est obtenu
	if ((Demande[0] <= prod[0]) && (Demande[1] <= prod[1])
			&& (Demande[2] <= prod[2]) && (Demande[3] <= prod[3])) {
		//test la fin du cycle
		if ((prod[0] % 10 == 0) && (prod[1] % 15 == 0) && (prod[2] % 12 == 0)
				&& (prod[3] % 8 == 0))
			return 0;
	}
	return 1;
}

int main(void) {
	int j = 0;
	int i;
	pthread_t thread[6];
	int nbRobot;

	int quit = 1;
	while (quit != 0) {
		int mode = 0;
		while ((mode < 1) || (mode > 2)) {
			printf("Selecttionnez un mode: \n");
			printf("\t - Mode Normale : 1 \n");
			printf("\t - Mode Dégrader : 2 \n");
			scanf("%d", &mode);
		}

		initialisation(mode);

		printf("Bonjour, nous allons lancer la production.");
		for (i = 0; i < 4; i++) {
			printf("\n Combien de produit %d faut-il produire :", i + 1);
			scanf("%d", &Demande[i]);
			printf(" \n vous demander %d produit %d",Demande[i],i+1);
		}
		calculeProd();

		//creation des threads
		if (mode == 1)
			nbRobot = 6;
		else
			nbRobot = 4;

		for (i = 0; i < nbRobot; i++) {
			pthread_create(&thread[i], NULL, Robot, i);
			usleep(2);
		}

		//simulation de rataion de l'anneau
		while (finProd()) {
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
			//printf("    -------tour %d-------    \n", j);
			for (i = 0; i < SIZE_ANNEAU; i++) {
			//	printf("Anneau %d: %d : %d \n", i, Anneau[i].numProduit,
			//			Anneau[i].etat);
			}
			pthread_mutex_unlock(&lockAnneau);
			usleep(30);

			j++;
		}
		int i;
		pthread_mutex_lock(&lockAnneau);
		for(i=0;i <nbRobot;i++)
			pthread_cancel(thread[i]);
		pthread_mutex_unlock(&lockAnneau);

		printf(
				"\n Il a était produit:\n - %d produit 1\n - %d produit 2\n - %d produit 3\n - %d produit 4\n",
				prod[0], prod[1], prod[2], prod[3]);

		printf("Voulez-vous relancer une production ou quitter ?\n");
		printf(" \t - Pour relancer la production : 1 \n");
		printf(" \t - Pour quitter : 0 \n");
		printf("votre choix :");
		scanf("%d", &quit);

	}
	return 0;
}

