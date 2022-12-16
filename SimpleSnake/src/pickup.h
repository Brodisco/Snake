/*
 * pickup.h
 *
 *  Created on: 16.12.2022
 *      Author: student
 */

#ifndef PICKUP_H_
#define PICKUP_H_

#include "Configuration.h"
#include "Console.h"
//#include "Spiel.h"
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

struct Pickup
{
	Liste *pickup_list;
	Liste *wurmhole_list_start;
	Liste *wurmhole_list_ende;

	clock_t last_time;
	long time_intervall;

};
typedef struct Pickup Pickup;



#endif /* PICKUP_H_ */
