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
pthread_mutex_t lock;

struct Piece PieceNull;

const int (*testOp[6]) (struct Piece piece, int compt);
const struct Piece (*Op[6]) (struct Piece ressource[]);
static const int index[6] = {1,3,5,7,9,11};

static int prod[4] ;
static int aProd[4] ;

static int C[4];
volatile int newCycle;
static int stade;
#endif /* MAIN_H_ */
