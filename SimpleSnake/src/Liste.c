/*
 * Liste.c
 *
 *  Created on: 12.12.2022
 *      Author: Mario Wegmann
 */

#include "Liste.h"
Liste* liste_erzeugen()
{
	//Aufgabe 2a)
	Liste* newList = (Liste*) malloc(sizeof(Liste));
	newList->kopf_ptr = NULL;
	newList->ende_ptr = NULL;
	newList->laenge = 0;

	return newList;
}

void liste_einfuegen_kopf(Liste* liste_ptr, Element* element_ptr)
{
	//Aufgabe 2b)
	if (liste_ptr->laenge == 0) {
		// Erstes Element in der Liste -> Ende der Liste setzen
		liste_ptr->ende_ptr = element_ptr;
	} else {
		// Es gibt schon Elemente -> Vorgänger vom alten Kopf setzen
		liste_ptr->kopf_ptr->vorgaenger_ptr = element_ptr;
	}

	element_ptr->nachfolger_ptr = liste_ptr->kopf_ptr;
	element_ptr->vorgaenger_ptr = NULL;

	liste_ptr->kopf_ptr = element_ptr;
	liste_ptr->laenge++;
}

Element* liste_entferne_ende(Liste* liste_ptr)
{
	//Aufgabe 2c)

	Element* letztesElement = liste_ptr->ende_ptr;
	letztesElement->vorgaenger_ptr->nachfolger_ptr = NULL;
	liste_ptr->ende_ptr = letztesElement->vorgaenger_ptr;
	liste_ptr->laenge--;

	return letztesElement;
}




