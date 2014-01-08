/*
 * operation.h
 *
 *  Created on: 15 déc. 2013
 *      Author: kevin
 */

#include <stdio.h>
#include <stdlib.h>
#include "piece.h"

#ifndef OPERATION_H_
#define OPERATION_H_

struct Piece op1(struct Piece ressource[]);
struct Piece op2(struct Piece ressource[]);
struct Piece op3(struct Piece ressource[]);
struct Piece op4(struct Piece ressource[]);
struct Piece op5(struct Piece ressource[]);
struct Piece op6(struct Piece ressource[]);

struct Piece opD1(struct Piece ressource[]);
struct Piece opD2(struct Piece ressource[]);
struct Piece opD3(struct Piece ressource[]);
struct Piece opD4(struct Piece ressource[]);

// renvoie 1 si la piece peut etre envoyer dans l'operation correspondante
// sinon renvoie 0
int testOp1(struct Piece piece, int compt);
int testOp2(struct Piece piece, int compt);
int testOp3(struct Piece piece, int compt);
int testOp4(struct Piece piece, int compt);
int testOp5(struct Piece piece, int compt);
int testOp6(struct Piece piece, int compt);

int testOpD1(struct Piece piece, int compt);
int testOpD2(struct Piece piece, int compt);
int testOpD3(struct Piece piece, int compt);
int testOpD4(struct Piece piece, int compt);

#endif /* OPERATION_H_ */
