/*
 * Schlange.c
 *
 *  Created on: 12.12.2022
 *      Author: Benjamin Klaric
 */
#include <stdlib.h>
#include <time.h>
#include "Configuration.h"
#include "Schlange.h"
#include "Console.h"
#include <ncurses.h>

/*
 * Initialisiert alle Attribute
 */
void schlange_init (Schlange* schlange_ptr)
{
	Liste* liste_ptr = liste_erzeugen();
	schlange_ptr->positionen_ptr = liste_ptr;
	schlange_ptr->punkte = 0;
	schlange_ptr->wachsen = 0;
}

Schlange* schlange_erzeugen()
{
	Schlange* schlange_ptr = (Schlange*) malloc(sizeof(Schlange));
	schlange_init(schlange_ptr);
	return schlange_ptr;
}


/*
 * Funktion bewegt die Schlange in die angegebene Richtung
 * */
void schlange_bewege (Schlange* schlange_ptr, int richtung)
{
	int x, y;

	//Element* element_ptr = element_erzeugen();
	Element* element_ptr = (Element*) malloc(sizeof(Element));
	Element* ende_ptr;

	x = schlange_ptr->positionen_ptr->kopf_ptr->pos.x;
	y = schlange_ptr->positionen_ptr->kopf_ptr->pos.y;

	switch (richtung)
	{
		case BEWEGUNG_HOCH:
			y--;
			break;
		case BEWEGUNG_RECHTS:
			x++;;
			break;
		case BEWEGUNG_RUNTER:
			y++;
			break;
		case BEWEGUNG_LINKS:
			x--;
			break;
		default:
			break;
	}
	element_ptr->pos.x = x;
	element_ptr->pos.y = y;

	if(schlange_ptr->wachsen > 0)
	{
		schlange_ptr->wachsen--;
	}
	else if(schlange_ptr->wachsen <= 0)
	{
		ende_ptr = liste_entferne_ende(schlange_ptr->positionen_ptr);
			if(ende_ptr != NULL)
			{
				free(ende_ptr);
			}
	}
	liste_einfuegen_kopf(schlange_ptr->positionen_ptr, element_ptr);
}

/*
 * Zeichnet die Schlange auf der Konsole
 */
void schlange_zeichne(Schlange* schlange_ptr, int farbe)
{
	attron(COLOR_PAIR(farbe));
	int x, y;
	Element* element_ptr = schlange_ptr->positionen_ptr->kopf_ptr;

	while(element_ptr != NULL)
	{
		x = element_ptr->pos.x;
		y = element_ptr->pos.y;
		console_zeichne_punkt(x, y, ' ');
		element_ptr = element_ptr->nachfolger_ptr;
	}
}
/*
 * Die Funktion verändert die Schlange in Abhängigkeit des eingesammelten Pickups.
 * Alles ist denkbar. Beschleunigung, Wurmloch oder ähnliches.
 */
void schlange_bearbeite_pickup(Schlange* schlange_ptr, char pickup)
{
	attron(COLOR_PAIR(SPIELFELD_RAND_FARBE));
	Element* element = element_erzeugen();
	srand(time(NULL));
	int min_x = SPIELFELD_OFFSET_X;
	int max_x = SPIELFELD_XSIZE;
	int min_y = SPIELFELD_OFFSET_Y;
	int max_y = SPIELFELD_YSIZE;

	element->pos.x = (rand()%(max_x - min_x + 1) + min_x);
	element->pos.y = (rand()%(max_y - min_y + 1) + min_y);

	console_zeichne_punkt(element->pos.x, element->pos.y, ' ');

	char snickers = element_folge_pruefen(schlange_ptr->positionen_ptr->kopf_ptr, element);

	if(snickers == 1)
	{
		schlange_ptr->wachsen++;
	}
}
/*
 * Die Funktion sollte nach jeder Bewegung aufgerufen werden und zum Beispiel den
 * Punktestand in Abhängigkeit der Länge der Schlange oder der Spieldauer erhöhen.
 */
void schlange_aktualisiere(Schlange* schlange_ptr)
{
	//Aufgabe 3f) OPTIONAL
	//TODO
}
