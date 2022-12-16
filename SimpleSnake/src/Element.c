/*
 * Element.c
 *
 *  Created on: 12.12.2022
 *      Author: student
 */
#include "Element.h"
Element* element_erzeugen()
{
	Element* element = (Element*) malloc(sizeof(Element));
	element->nachfolger_ptr = NULL;
	element->pos.x = 0;
	element->pos.y = 0;
	return element;
}
/* Prüfe, ob e1 mit einem seiner Nachfolger übereinstimmt */
char element_folge_pruefen (Element* pruef_ptr, Element* e_ptr)
{
	char Ergebnis = 0;
	Element* e_ptrneu = e_ptr;
	while(!(e_ptr->nachfolger_ptr == NULL))
	{
		if((pruef_ptr->pos.x == e_ptrneu->pos.x) && (pruef_ptr->pos.x == e_ptrneu->pos.y))
		{
			Ergebnis = 1;
			break;
		}
		e_ptrneu = e_ptrneu->nachfolger_ptr;
	}
	return Ergebnis;
}

