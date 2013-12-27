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

#endif /* MAIN_H_ */
