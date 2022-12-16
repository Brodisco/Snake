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
	spiel_ptr->s1_ptr = schlange_erzeugen();
	spiel_ptr->s2_ptr = schlange_erzeugen();

	Element* e_ptr1 = element_erzeugen();
	Element* e_ptr2 = element_erzeugen();

	liste_einfuegen_kopf(spiel_ptr->s1_ptr->positionen_ptr, e_ptr1);
	liste_einfuegen_kopf(spiel_ptr->s2_ptr->positionen_ptr, e_ptr2);

	spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr->pos.x = SPIELER_1_XPOS;
	spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr->pos.y = SPIELER_YPOS;
	spiel_ptr->s1_ptr->wachsen = SPIEL_SCHLANGEN_LAENGE;

	spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr->pos.x = SPIELER_2_XPOS;
	spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr->pos.y = SPIELER_YPOS;
	spiel_ptr->s2_ptr->wachsen = SPIEL_SCHLANGEN_LAENGE;

	spiel_ptr->run = 1;
}

Spiel* spiel_erzeugen()
{
	Spiel* spiel_ptr = (Spiel*) malloc(sizeof(Spiel));
	spiel_init(spiel_ptr);
	return spiel_ptr;
}

void spiel_zeichne_rand()
{
	attron(COLOR_PAIR(SPIELFELD_RAND_FARBE));
	for(int x = SPIELFELD_OFFSET_X; x <= SPIELFELD_XSIZE; x++)
	{
		for(int y = SPIELFELD_OFFSET_Y; y <= SPIELFELD_YSIZE; y++)
		{
			if((x == SPIELFELD_OFFSET_X) || (y == SPIELFELD_OFFSET_Y) || (x == SPIELFELD_XSIZE) || (y == SPIELFELD_YSIZE))
			{
				console_zeichne_punkt(x, y, ' ');
			}
		}
	}

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

