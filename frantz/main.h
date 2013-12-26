/*
 * main.h
 *
 *  Created on: 26 déc. 2013
 *      Author: kevin
 */

#ifndef MAIN_H_
#define MAIN_H_

const int SIZE_ANNEAU = 16;
volatile struct Piece Anneau[SIZE_ANNEAU];
pthread_mutex_t lock;

#endif /* MAIN_H_ */
