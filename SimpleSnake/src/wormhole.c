/*
 * wormhole.c
 *
 *  Created on: Dec 20, 2022
 *      Author: maximilian
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Configuration.h"
#include "Console.h"
#include "wormhole.h"
#include "pickup.h"
#include "Spiel.h"

WormholeList *createWormholeList(void)
{
	WormholeList *wormhole = (WormholeList*) malloc(sizeof(WormholeList));

	if (wormhole == NULL)
	{
		fprintf(stderr, "WormholeList konnte nicht erzeugt werden! \n");
		return NULL;
	}

	wormhole->head = NULL;
	wormhole->tail = NULL;

	return wormhole;
}

WormholeElement *createWormholeElement()
{
	WormholeElement *element = (WormholeElement*) malloc(sizeof(WormholeElement));

	if (element == NULL)
	{
		fprintf(stderr, "WormholeElement konnte nicht erstellt werden! \n");
		return NULL;
	}

	element->next = NULL;
	element->prev = NULL;

	return element;
}

void pushWormholeElement(WormholeList *list, WormholeElement *element)
{
	element->next = list->head;
	if (element->next == NULL)
	{
		list->head = element;
		list->tail = element;
		list->leangh++;
	} else {
		list->head = element;
		element->next->prev = element;
		list->leangh++;
	}
}

WormholeElement *checkSnakeWormholeCollision(Schlange *snake_ptr, Wormhole *wormhole_ptr)
{
	WormholeElement *wormhole = wormhole_ptr->wormholeList_ptr->head;
	int snakeX = snake_ptr->positionen_ptr->kopf_ptr->pos.x;
	int snakeY = snake_ptr->positionen_ptr->kopf_ptr->pos.y;

	while(wormhole != NULL)
	{
		if ( (snakeX == wormhole->x1 && snakeY == wormhole->y1) || (snakeX == wormhole->x2 && snakeY == wormhole->y2))
		{
			return wormhole;
		}
		wormhole = wormhole->next;
	}

	return NULL;
}


Wormhole *initWormhole()
{
	Wormhole *wormhole = (Wormhole*) malloc(sizeof(Wormhole));
	if (wormhole == NULL)
	{
		fprintf(stderr, "Wormhole konnte nicht erzeugt werden! \n");
		return NULL;
	}

	WormholeList *wormholeList = createWormholeList();
	wormhole->wormholeList_ptr = wormholeList;
	wormhole->last_time = clock();
	wormhole->time_intervall = 50000;

	return wormhole;
}

void sparnRandomWormholeElement(Spiel *spiel_ptr)
{
	if((clock() - spiel_ptr->wormhole_ptr->last_time) >= spiel_ptr->wormhole_ptr->time_intervall)
	{

		WormholeElement *wormhole = createWormholeElement();
		do
		{

			wormhole->x1 = SPIELFELD_OFFSET_X + 1 + rand() % (SPIELFELD_XSIZE - 1);
			wormhole->y1 = SPIELFELD_OFFSET_Y + 1 + rand() % (SPIELFELD_YSIZE - 1);
			wormhole->x2 = SPIELFELD_OFFSET_X + 1 + rand() % (SPIELFELD_XSIZE - 1);
			wormhole->y2 = SPIELFELD_OFFSET_Y + 1 + rand() % (SPIELFELD_YSIZE - 1);
		}while(wormhole->x1 != wormhole->x2 && wormhole->y1 != wormhole->y2);

		pushWormholeElement(spiel_ptr->wormhole_ptr->wormholeList_ptr, wormhole);

		spiel_ptr->wormhole_ptr->last_time = clock();
	}
}

void printWormhole(Spiel *spiel_ptr, int farbe)
{
	WormholeElement *wormhole = spiel_ptr->wormhole_ptr->wormholeList_ptr->head;

	attron(COLOR_PAIR(farbe));

	while(wormhole != NULL)
	{
		console_zeichne_punkt(wormhole->x1, wormhole->y1, ' ');
		console_zeichne_punkt(wormhole->x2, wormhole->y2, ' ');

		wormhole = wormhole->next;
	}
}

