/*
 * main.h
 *
 *  Created on: 26 déc. 2013
 *      Author: kevin
 */

#ifndef MAIN_H_


#define MAIN_H_
static const int SIZE_ANNEAU = 16;
volatile struct Piece Anneau[16];
pthread_mutex_t lockAnneau;

struct Piece PieceNull;

//tableau de pointeur de fonction de test d'opération réalisable
const int (*testOp[6]) (struct Piece piece, int compt);

//tableau de pointeur de fonction opération sur une ou un ensemble de piece
const struct Piece (*Op[6]) (struct Piece ressource[]);
//index ou sont possitionner les robot
static const int index[6] = {1,3,5,7,9,11};

//poduction total
static int prod[4] ;
//production totalise a la fin du cycle précédent
static int aProd[4] ;

//nombre de ressource primaire encore a inséré dans l'anneau
static int ResteProd[4];

//nombre de produit attendu en fin de production
static int Demande[4];
volatile int newCycle;

static int stade;
#endif /* MAIN_H_ */
