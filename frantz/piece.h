/*
 * piece.h
 *
 *  Created on: 14 déc. 2013
 *      Author: kevin
 */

#ifndef PIECE_H_
#define PIECE_H_

typedef struct Piece {
	int numProduit;
	int etat;
};

struct Piece newPiece(int numProduit, int etat);

#endif /* PIECE_H_ */
