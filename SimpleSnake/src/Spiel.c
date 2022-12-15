/*
 * Spiel.c
 *
 *  Created on: 12.12.2022
 *      Author: student
 */
#include "Configuration.h"
#include "Console.h"
#include "Spiel.h"
#include <stdlib.h>
#include <ncurses.h>

void spiel_init(Spiel* spiel_ptr)
{
	//Aufgabe 4a)
	// Spieler 1
	spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr->pos.x = SPIELER_1_XPOS;
	spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr->pos.y = SPIELER_YPOS;
	spiel_ptr->s1_ptr->wachsen = SPIEL_SCHLANGEN_LAENGE;

	// Spieler 2
	spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr->pos.x = SPIELER_2_XPOS;
	spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr->pos.y = SPIELER_YPOS;
	spiel_ptr->s2_ptr->wachsen = SPIEL_SCHLANGEN_LAENGE;

	spiel_ptr->run = 1;
}

Spiel* spiel_erzeugen()
{
	//Aufgabe 4b)
	//TODO
	return NULL;
}

void spiel_zeichne_rand()
{
	//Aufgabe 4c)
	//TODO
}

void spiel_pruefe_kollission(Spiel* spiel_ptr)
{
	//Aufgabe 4d)
	//TODO
}

void spiel_zeichne_spielstand()
{
	//Aufgabe 4e)     OPTIONAL
	//TODO
}

