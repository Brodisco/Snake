/*
 * spielstand.c
 *
 *  Created on: Dec 17, 2022
 *      Author: maximilian
 */
#include "Configuration.h"
#include "Console.h"
#include "Spiel.h"
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <math.h>
#include "spielstand.h"



Spielstand *inti_PixelGruppe(int x, int y)
{
	Spielstand *spielstand = (Spielstand*) malloc(sizeof(Spielstand));

	for (int i = 0; i < 10; i++)
	{
		spielstand->zahlen[i] = (Pixelgruppe*) malloc(sizeof(Pixelgruppe));
	}

	strcpy(spielstand->zahlen[0]->pixel[0], "111111");
	strcpy(spielstand->zahlen[0]->pixel[1], "110011");
	strcpy(spielstand->zahlen[0]->pixel[2], "110011");
	strcpy(spielstand->zahlen[0]->pixel[3], "110011");
	strcpy(spielstand->zahlen[0]->pixel[4], "111111");

	strcpy(spielstand->zahlen[1]->pixel[0], "001100");
	strcpy(spielstand->zahlen[1]->pixel[1], "001100");
	strcpy(spielstand->zahlen[1]->pixel[2], "001100");
	strcpy(spielstand->zahlen[1]->pixel[3], "001100");
	strcpy(spielstand->zahlen[1]->pixel[4], "001100");

	strcpy(spielstand->zahlen[2]->pixel[0], "111111");
	strcpy(spielstand->zahlen[2]->pixel[1], "000011");
	strcpy(spielstand->zahlen[2]->pixel[2], "111111");
	strcpy(spielstand->zahlen[2]->pixel[3], "110000");
	strcpy(spielstand->zahlen[2]->pixel[4], "111111");

	strcpy(spielstand->zahlen[3]->pixel[0], "111111");
	strcpy(spielstand->zahlen[3]->pixel[1], "000011");
	strcpy(spielstand->zahlen[3]->pixel[2], "111111");
	strcpy(spielstand->zahlen[3]->pixel[3], "000011");
	strcpy(spielstand->zahlen[3]->pixel[4], "111111");

	strcpy(spielstand->zahlen[4]->pixel[0], "110011");
	strcpy(spielstand->zahlen[4]->pixel[1], "110011");
	strcpy(spielstand->zahlen[4]->pixel[2], "111111");
	strcpy(spielstand->zahlen[4]->pixel[3], "000011");
	strcpy(spielstand->zahlen[4]->pixel[4], "000011");

	strcpy(spielstand->zahlen[5]->pixel[0], "111111");
	strcpy(spielstand->zahlen[5]->pixel[1], "110000");
	strcpy(spielstand->zahlen[5]->pixel[2], "111111");
	strcpy(spielstand->zahlen[5]->pixel[3], "000011");
	strcpy(spielstand->zahlen[5]->pixel[4], "111111");

	strcpy(spielstand->zahlen[6]->pixel[0], "111111");
	strcpy(spielstand->zahlen[6]->pixel[1], "110000");
	strcpy(spielstand->zahlen[6]->pixel[2], "111111");
	strcpy(spielstand->zahlen[6]->pixel[3], "110011");
	strcpy(spielstand->zahlen[6]->pixel[4], "111111");

	strcpy(spielstand->zahlen[7]->pixel[0], "111111");
	strcpy(spielstand->zahlen[7]->pixel[1], "000011");
	strcpy(spielstand->zahlen[7]->pixel[2], "000011");
	strcpy(spielstand->zahlen[7]->pixel[3], "000011");
	strcpy(spielstand->zahlen[7]->pixel[4], "000011");

	strcpy(spielstand->zahlen[8]->pixel[0], "111111");
	strcpy(spielstand->zahlen[8]->pixel[1], "110011");
	strcpy(spielstand->zahlen[8]->pixel[2], "111111");
	strcpy(spielstand->zahlen[8]->pixel[3], "110011");
	strcpy(spielstand->zahlen[8]->pixel[4], "111111");

	strcpy(spielstand->zahlen[9]->pixel[0], "111111");
	strcpy(spielstand->zahlen[9]->pixel[1], "110011");
	strcpy(spielstand->zahlen[9]->pixel[2], "111111");
	strcpy(spielstand->zahlen[9]->pixel[3], "000011");
	strcpy(spielstand->zahlen[9]->pixel[4], "111111");

	spielstand->x = x;
	spielstand->y = y;

	spielstand->spielstand_spieler1 = 0;
	spielstand->spielstand_spieler2 = 0;

	print_spielstand(spielstand);

	return spielstand;
}

void print_spielstand(Spielstand *spielstand)
{
	int local_spielstand[2];
	local_spielstand[0] = spielstand->spielstand_spieler1 - SPIEL_SCHLANGEN_LAENGE;
	local_spielstand[1] = spielstand->spielstand_spieler2 - SPIEL_SCHLANGEN_LAENGE;

	local_spielstand[0] = (local_spielstand[0] < 0) ? 0 : local_spielstand[0];
	local_spielstand[1] = (local_spielstand[1] < 0) ? 0 : local_spielstand[1];

	int start_x = spielstand->x;
	int start_y = spielstand->y;

	int digit = 0;
	int counter = 0;

	char spielstand_char[2][10];
	int spielstand_laenge = 0;

	for (int i = 0; i < 2; i++)
	{
		sprintf(spielstand_char[i], "%d", local_spielstand[i]);
		spielstand_laenge = strlen(spielstand_char[i]);

		for (int k = 0; k < spielstand_laenge; k++)
		{
			digit =  (char)spielstand_char[i][k] - '0';

			for (int y = 0; y < PIXEL_SIZE_Y; y++)
			{
				for (int x = 0; x < PIXEL_SIZE_X; x++)
				{
					if (spielstand->zahlen[digit]->pixel[y][x] == '1')
					{
						console_zeichne_punkt(start_x + x + (counter * PIXEL_SIZE_X + 1), start_y + y, ' ');
					}
				}
			}
			counter++;
		}
		counter++;
	}
}

void update_Spielstand(Spielstand *spielstand_ptr, Spiel *spiel_ptr)
{
	attron(COLOR_PAIR(SPIELFELD_HINTERGRUND_FARBE));
	print_spielstand(spielstand_ptr);

	int laenge_spieler1 = spiel_ptr->s1_ptr->positionen_ptr->laenge;
	int laenge_spieler2 = spiel_ptr->s2_ptr->positionen_ptr->laenge;


	if (laenge_spieler1 > SPIEL_SCHLANGEN_LAENGE + 1 && laenge_spieler1 > SPIEL_SCHLANGEN_LAENGE)
	{
		spielstand_ptr->spielstand_spieler1 = laenge_spieler1 - 1;
		spielstand_ptr->spielstand_spieler2 = laenge_spieler2 - 1;
	}

	attron(COLOR_PAIR(SPIELER_1_FARBE));
	print_spielstand(spielstand_ptr);
}

