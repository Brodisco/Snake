/*
 * Schlange.c
 *
 *  Created on: 12.12.2022
 *      Author: Mario Wegmann
 */
#include <stdlib.h>
#include "Configuration.h"
#include "Schlange.h"
#include "Console.h"

/*
 * Initialisiert alle Attribute
 */
void schlange_init (Schlange* schlange_ptr)
{
	//Aufgabe 3a)
	schlange_ptr->positionen_ptr = liste_erzeugen();
	schlange_ptr->punkte = 0;
	schlange_ptr->wachsen = 0;
}

Schlange* schlange_erzeugen()
{
	//Aufgabe 3b)
	Schlange* newSchlange = (Schlange*) malloc(sizeof(Schlange));
	schlange_init(newSchlange);

	return newSchlange;
}


/*
 * Funktion bewegt die Schlange in die angegebene Richtung
 * */
void schlange_bewege (Schlange* schlange_ptr, int richtung)
{
	//Aufgabe 3c)
	Element* alterKopf = schlange_ptr->positionen_ptr->kopf_ptr;
	if (schlange_ptr->wachsen > 0) {
		// Wir sind noch am wachsen
		schlange_ptr->wachsen--;
	} else if (schlange_ptr->wachsen == 0) {
		Element* entferntesEnde = liste_entferne_ende(schlange_ptr->positionen_ptr);
		free(entferntesEnde);
	}
	Element* neuerKopf = element_erzeugen();
	neuerKopf->pos.x = alterKopf->pos.x;
	neuerKopf->pos.y = alterKopf->pos.y;

	switch (richtung) {
		case BEWEGUNG_HOCH:
			neuerKopf->pos.y--;
			break;
		case BEWEGUNG_RUNTER:
			neuerKopf->pos.y++;
			break;
		case BEWEGUNG_LINKS:
			neuerKopf->pos.x--;
			break;
		case BEWEGUNG_RECHTS:
			neuerKopf->pos.x++;
			break;
	}
	liste_einfuegen_kopf(schlange_ptr->positionen_ptr, neuerKopf);
}


/*
 * Zeichnet die Schlange auf der Konsole
 */
void schlange_zeichne(Schlange* schlange_ptr, int farbe)
{
	//Aufgabe 3d)
	attron(COLOR_PAIR(farbe)); //Setzt die Farbe der Schrift und des Hintergrunds
	Element* aktuellesElement = schlange_ptr->positionen_ptr->kopf_ptr;
	while (aktuellesElement != NULL) {
		console_zeichne_punkt(aktuellesElement->pos.x, aktuellesElement->pos.y, ' ');
		aktuellesElement = aktuellesElement->nachfolger_ptr;
	}
}

/*
 * Die Funktion verändert die Schlange in Abhängigkeit des eingesammelten Pickups.
 * Alles ist denkbar. Beschleunigung, Wurmloch oder ähnliches.
 */
void schlange_bearbeite_pickup(Schlange* schlange_ptr, PickUp* pickup_ptr)
{
	//Aufgabe 3e) OPTIONAL
	if (schlange_ptr->positionen_ptr->kopf_ptr->pos.x == pickup_ptr->pos.x && schlange_ptr->positionen_ptr->kopf_ptr->pos.y == pickup_ptr->pos.y) {
		pickup_ptr->pos.x = rand()%SPIELFELD_XSIZE+SPIELFELD_OFFSET_X;
		pickup_ptr->pos.y = rand()%SPIELFELD_YSIZE+SPIELFELD_OFFSET_Y;
		pickUp_zeichne(pickup_ptr, FARBE_MAGENTA);
		schlange_ptr->wachsen = 2;
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
