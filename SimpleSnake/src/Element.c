/*
 * Element.c
 *
 *  Created on: 12.12.2022
 *      Author: student
 */
#include "Element.h"
Element* element_erzeugen()
{
	//Aufgabe 1a)
	Element* newElement = (Element*) malloc(sizeof(Element));

	newElement->nachfolger_ptr = NULL;
	newElement->nachfolger_ptr = NULL;
	newElement->pos.x = 0;
	newElement->pos.y = 0;

	return newElement;
}
/* Prüfe, ob e1 mit einem seiner Nachfolger übereinstimmt */
char element_folge_pruefen (Element* pruef_ptr, Element* e_ptr)
{
	//Aufgabe 1b)
	Element* check_e_ptr = e_ptr;
	char result = 0;
	while(check_e_ptr != NULL) {
		if((pruef_ptr->pos.x == check_e_ptr->pos.x) && (pruef_ptr->pos.y == check_e_ptr->pos.y)) {
			result = 1;
			break;
		}
		check_e_ptr = check_e_ptr->nachfolger_ptr;
	}

	return result;
}
