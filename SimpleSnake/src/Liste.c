/*
 * Liste.c
 *
 *  Created on: 12.12.2022
 *      Author: student
 */

#include "Liste.h"
Liste* liste_erzeugen()
{
	Liste* liste_ptr = (Liste*) malloc(sizeof(Liste));
	liste_ptr->kopf_ptr = NULL;
	liste_ptr->laenge = 0;
	return liste_ptr;
}

void liste_einfuegen_kopf(Liste* liste_ptr, Element* element_ptr)
{
	element_ptr->nachfolger_ptr = liste_ptr->kopf_ptr;
	liste_ptr->kopf_ptr = element_ptr;
	liste_ptr->laenge++;
}

Element* liste_entferne_ende(Liste* liste_ptr)
{
	Element* element_ptr = liste_ptr->kopf_ptr;

	while(element_ptr != NULL)
	{
		if(element_ptr->nachfolger_ptr == NULL)
		{
			free(element_ptr->nachfolger_ptr);
			break;
		}
		element_ptr = element_ptr->nachfolger_ptr;
	}

	return element_ptr;
}

