/*
 * Liste.c
 *
 *  Created on: 12.12.2022
 *      Author: student
 */

#include "Liste.h"
Liste* liste_erzeugen()
{
	Liste *list = (Liste*) malloc(sizeof(Liste));
	list->kopf_ptr = NULL;
	list->schwanz_ptr = NULL;
	list->laenge = 0;
	return list;
}

void liste_einfuegen_kopf(Liste* liste_ptr, Element* element_ptr)
{
	element_ptr->nachfolger_ptr = liste_ptr->kopf_ptr;
	if (element_ptr->nachfolger_ptr == NULL)
	{
		liste_ptr->kopf_ptr = element_ptr;
		liste_ptr->schwanz_ptr = element_ptr;
		liste_ptr->laenge++;
	} else {
		liste_ptr->kopf_ptr = element_ptr;
		element_ptr->nachfolger_ptr->vorgänger_ptr = element_ptr;
		liste_ptr->laenge++;
	}
}

Element* liste_entferne_ende(Liste* liste_ptr)
{
	Element *element_ptr = liste_ptr->schwanz_ptr;
	liste_ptr->schwanz_ptr = element_ptr->nachfolger_ptr;
	element_ptr->vorgänger_ptr->nachfolger_ptr = NULL;
	return element_ptr;
}






