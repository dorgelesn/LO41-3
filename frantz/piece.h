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
}Piece;

// permet de crée un élément Piece définit par les paramteres
struct Piece newPiece(int numProduit, int etat);

// renvoie 1 si la piece a les caractéristique donnée en paramètre
// sinon renvoie 0
int testPiece(struct Piece piece, int numProduit, int etat);

// renvoie 1 si la piece a le bon etat
// sinon renvoie 0
int testEtatPiece(struct Piece piece, int etat);

#endif /* PIECE_H_ */
