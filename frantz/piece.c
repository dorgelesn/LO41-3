/*
 * piece.c
 *
 *  Created on: 15 déc. 2013
 *      Author: kevin
 */

#include "piece.h"

struct Piece newPiece(int numProduit, int etat)
{
	struct Piece piece;
	piece.etat = etat;
	piece.numProduit = numProduit;
	return piece;
}

int testPiece(struct Piece piece, int numProduit, int etat)
{
	if((piece.numProduit == numProduit ) & (piece.etat == etat))
			return 1;
	else return 0;
}
