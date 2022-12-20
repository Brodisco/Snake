/*
 * PickUp.c
 *
 *  Created on: 19.12.2022
 *      Author: student
 */

#include <ncurses.h>
#include <stdlib.h>
#include "Configuration.h"
#include "Console.h"
#include "PickUp.h"


PickUp* pickUp_erzeugen() {
	PickUp* newPickup = (PickUp*) malloc(sizeof(PickUp));

	newPickup->pos.x = 0;
	newPickup->pos.y = 0;
	newPickup->type = 0;

	return newPickup;
}

void pickUp_zeichne(PickUp* pickUp_ptr, int farbe) {
	attron(COLOR_PAIR(farbe));
	console_zeichne_punkt(pickUp_ptr->pos.x, pickUp_ptr->pos.y, ' ');



}
