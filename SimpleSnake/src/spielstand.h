/*
 * spielstand.h
 *
 *  Created on: Dec 17, 2022
 *      Author: maximilian
 */

#include "Spiel.h"

#ifndef SPIELSTAND_H_
#define SPIELSTAND_H_

#define PIXEL_SIZE_X 7
#define PIXEL_SIZE_Y 5

struct Pixelgruppe
{
	char pixel[PIXEL_SIZE_Y][PIXEL_SIZE_X];
};
typedef struct Pixelgruppe Pixelgruppe;

struct Spielstand
{
	int spielstand_spieler1;
	int spielstand_spieler2;

	int x;
	int y;

	struct Pixelgruppe *zahlen[10];
};
typedef struct Spielstand Spielstand;

Spielstand *inti_PixelGruppe(int x, int y);
void print_spielstand(Spielstand *spielstand);
void update_Spielstand(Spielstand *spielstand_ptr, Spiel *spiel_ptr);


#endif /* SPIELSTAND_H_ */
