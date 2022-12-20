/*
 * PickUp.h
 *
 *  Created on: 19.12.2022
 *      Author: student
 */

#ifndef PICKUP_H_
#define PICKUP_H_

#include "Position.h"

struct PickUp
{
	Position pos;
	int type;
};
typedef struct PickUp PickUp;

PickUp* pickUp_erzeugen();
void pickUp_zeichne(PickUp* pickUp_ptr, int farbe);

#endif /* PICKUP_H_ */
