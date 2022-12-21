/*
 * settings.c
 *
 *  Created on: 21.12.2022
 *      Author: maximilian
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "Configuration.h"
#include "pixelgruppe.h"
#include "Spiel.h"
#include "settings.h"
#include "Eingabe.h"
#include "Console.h"

void clearScreen(int farbe)
{
	attron(COLOR_PAIR(farbe));

	for (int y = 0; y < MAX_SCREEN_SIZE_Y; y++)
	{
		for (int x = 0; x < MAX_SCREEN_SIZE_X; x++)
		{
			console_zeichne_punkt(x, y, ' ');
		}
	}
}

void printSettingMenue(CharacterList *list, int farbe)
{
	printPixelString(list, "PICKUPS", 10, 10, farbe);
	printPixelString(list, "WURMHOLE", 10, 18, farbe);
	printPixelString(list, "START", 10, 26, farbe);
	printPixelString(list, "QUIT", 10, 34, farbe);
}

int settingsChooser(CharacterList *list, int farbe, int updown)
{
	static int pos = 10;

	printPixelString(list, "#", 2, pos, 4);

	//up
	if (updown == 1)
	{
		pos = (pos < 34) ? pos + 8 : pos;
	} else {
		pos = (pos > 10) ? pos - 8 : pos;
	}

	printPixelString(list, "#", 2, pos, 1);

	return pos;
}

int valueChooser(CharacterList *list, int farbe, int pos,  int defaultValue)
{
	char str[128];
	char input = 0;

	do
	{

		sprintf(str, "%d", defaultValue);
		printPixelString(list, str, 80, pos, farbe);

		input = getch();

		if (input == 'w')
		{
			defaultValue++;
		}
		else if(input == 's' && defaultValue > 0)
		{
			defaultValue--;
		}

		printPixelString(list, str, 80, pos, 4);

	}while(input!= 'm');




	return defaultValue;
}

void displaySettingsScreen(Spiel *spiel_ptr, CharacterList *list)
{
	clearScreen(SPIELFELD_HINTERGRUND_FARBE);
	printSettingMenue(list, 1);

	printPixelString(list, "SNAKE BY OSZI", 50, 1, SPIELER_1_FARBE);

	char input = 0;
	static int pos = 10;

	printPixelString(list, "#", 2, pos, 1);

	nodelay(stdscr, FALSE);



	do
	{
		input = getch();
		//mvprintw(5,5,"Taste: %c \n", input);

		if (input == 'w') pos = settingsChooser(list, 1, 0);
		else if (input == 's') pos = settingsChooser(list, 1, 1);

		if (pos == 10 && input == 'm') valueChooser(list, 1, pos, 10);
		if (pos == 18 && input == 'm') spiel_ptr->wormhole_ptr->maxWormhole = valueChooser(list, 1, pos, 1);
		if (pos == 26 && input == 'm') input = 'q';
		if (pos == 34 && input == 'm') exit(-1);

	}while(input != 'q');

	nodelay(stdscr, TRUE );

	clearScreen(SPIELFELD_HINTERGRUND_FARBE);


}
