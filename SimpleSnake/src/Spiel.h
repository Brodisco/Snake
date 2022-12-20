/*
 * Spiel.h
 *
 *  Created on: 12.12.2022
 *      Author: student
 */

#ifndef SPIEL_H_
#define SPIEL_H_

#include "Schlange.h"
#include "pickup.h"
#include "wormhole.h"

struct Spiel
{
	Schlange* s1_ptr;
	Schlange* s2_ptr;
	Pickup *pickup_ptr;
	Wormhole *wormhole_ptr;

	char run;
	int schritte;
};
typedef struct Spiel Spiel;

Spiel* spiel_erzeugen();
void spiel_init(Spiel* spiel_ptr);
void spiel_zeichne_rand();
void spiel_zeichne_spielstand();
void spiel_pruefe_kollission(Spiel* spiel_ptr);


Pickup *init_pickup();
void plaziere_Pickup(Spiel *spiel_ptr);
void print_Pickup(Spiel *spiel_ptr, int farbe);
void handle_pickup_conflict(Spiel *spiel_ptr);



#endif /* SPIEL_H_ */
