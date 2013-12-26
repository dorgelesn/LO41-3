/*
 * operation.c
 *
 *  Created on: 15 déc. 2013
 *      Author: kevin
 */

#include "operation.h"
#include "piece.h"
#include <stdlib.h>

struct Piece op1(struct Piece ressource[]) {
	switch (ressource[0].numProduit) {
	case (1): {
		//on vérifie qu'on n'a 3 C1
		if ((testPiece(ressource[0], 1, 1)) &&
				(testPiece(ressource[1], 1, 1)) &&
				(testPiece(ressource[2], 1, 1)))
			return newPiece(1, 2);
		else
			break;
	}
	case (2): {
		//si on a un produit2 interédiaire a l'etat 3 on passe a l'etat 4
		if (testPiece(ressource[0], 2, 3))
			return newPiece(2, 4);
		else
			break;
	}
	case (3): {
		//on vérifie qu'on n'a 1 C3
		if (testPiece(ressource[0], 3, 2))
			return newPiece(3, 3);
		//si on a un produit3 interédiaire a l'etat 4 on passe a l'etat 5
		else if (testPiece(ressource[0], 3, 4))
			return newPiece(3, 5);
		else
			break;
	}
	case (4): {
		//si on a un produit4 interédiaire a l'etat 3 on passe a l'etat 4
		if (testPiece(ressource[0], 4, 3))
			return newPiece(4, 4);
		else
			break;
	}
	default:
		break;
	}

	return newPiece(0,0) ;
}

struct Piece op2(struct Piece ressource[]) {
	switch (ressource[0].numProduit) {
	case (1): {
		if (testPiece(ressource[0], 1, 2))
			return newPiece(1, 3);
		else
			break;
	}
	case (2): {
		if ((testPiece(ressource[0], 2, 1)) && (testPiece(ressource[1], 2, 1))
				&& (testPiece(ressource[2], 2, 1)))
			return newPiece(2, 2);
		else
			break;
	}
	default:
		break;
	}
	return newPiece(0, 0) ;
}

struct Piece op3(struct Piece ressource[]) {
	switch (ressource[0].numProduit) {
	case (1): {
		if (testPiece(ressource[0], 1, 3))
			return newPiece(1, 4);
		else
			break;
	}
	case (3): {
		if (testPiece(ressource[0], 3, 1))
			return newPiece(3, 2);
		else if (testPiece(ressource[0], 3, 5))
			return newPiece(3, 6);
		else
			break;
	}
	case (4): {
		if (testPiece(ressource[0], 4, 3))
			return newPiece(4, 4);
		else
			break;
		default:
		break;
	}
	}
	return newPiece(0,0);
}

	struct Piece op4(struct Piece ressource[]) {
		switch (ressource[0].numProduit) {
		case (2): {
			if (testPiece(ressource[0], 2, 2))
				return newPiece(2, 3);
			else
				break;
		}
		case (4): {
			if ((testPiece(ressource[0], 4, 1))
					&& (testPiece(ressource[1], 4, 1)))
				return newPiece(4, 2);
			else
				break;
		}
		default:
			break;
		}
		return newPiece(0,0);
	}

	struct Piece op5(struct Piece ressource[]) {
		switch (ressource[0].numProduit) {
		case (1): {
			//on vérifie qu'on n'a 3 C1
			if (testPiece(ressource[2], 1, 4))
				return newPiece(1, 5);
			else
				break;
		}
		case (3): {
			if (testPiece(ressource[0], 3, 3))
				return newPiece(3, 4);
			else
				break;
		}
		default:
			break;
		}
		return newPiece(0,0);
	}

	struct Piece op6(struct Piece ressource[]) {
		switch (ressource[0].numProduit) {
		case (2): {
			if (testPiece(ressource[0], 2, 4))
				return newPiece(2, 5);
			else
				break;
		}
		case (4): {
			if (testPiece(ressource[0], 4, 2))
				return newPiece(4, 3);
			else
				break;
		}
		default:
			break;
		}
		return newPiece(0,0);
	}
