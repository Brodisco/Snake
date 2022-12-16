/*
 * Element.h
 *
 *  Created on: 12.12.2022
 *      Author: Mario Wegmann
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "Position.h"
#include <stdlib.h>
struct Element
{
	Position pos;
	struct Element* nachfolger_ptr;
	struct Element* vorgaenger_ptr;
};
typedef struct Element Element;

Element* element_erzeugen();
char element_folge_pruefen (Element* pruef_ptr, Element* e_ptr);

#endif /* ELEMENT_H_ */
