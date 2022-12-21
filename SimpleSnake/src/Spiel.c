/*
 * Spiel.c
 *
 *  Created on: 12.12.2022
 *      Author: Mario Wegmann
 */
#include "Configuration.h"
#include "Console.h"
#include "Spiel.h"
#include <stdlib.h>
#include <ncurses.h>

void spiel_init(Spiel* spiel_ptr)
{
	//Aufgabe 4a)
	// Spieler 1
	spiel_ptr->s1_ptr = schlange_erzeugen();

	Element* kopfS1 = element_erzeugen();
	kopfS1->pos.x = SPIELER_1_XPOS;
	kopfS1->pos.y = SPIELER_YPOS;

	liste_einfuegen_kopf(spiel_ptr->s1_ptr->positionen_ptr, kopfS1);

	spiel_ptr->s1_ptr->wachsen = SPIEL_SCHLANGEN_LAENGE;

	// Spieler 2
	spiel_ptr->s2_ptr = schlange_erzeugen();

	Element* kopfS2 = element_erzeugen();
	kopfS2->pos.x = SPIELER_2_XPOS;
	kopfS2->pos.y = SPIELER_YPOS;

	liste_einfuegen_kopf(spiel_ptr->s2_ptr->positionen_ptr, kopfS2);

	spiel_ptr->s2_ptr->wachsen = SPIEL_SCHLANGEN_LAENGE;

	spiel_ptr->pickup_ptr = NULL;

	spiel_ptr->run = 1;
}

Spiel* spiel_erzeugen()
{
	//Aufgabe 4b)
	Spiel* neuesSpiel = (Spiel*) malloc(sizeof(Spiel));
	spiel_init(neuesSpiel);

	return neuesSpiel;
}

void spiel_zeichne_rand()
{
	//Aufgabe 4c)
	attron(COLOR_PAIR(SPIELFELD_RAND_FARBE));

	// Oben zeichnen
	for (int x = SPIELFELD_OFFSET_X; x <= SPIELFELD_XSIZE + SPIELFELD_OFFSET_X + 1; x++) {
		console_zeichne_punkt(x, SPIELFELD_OFFSET_Y, ' ');
	}
	// Rechts zeichnen
	for (int y = SPIELFELD_OFFSET_Y+1; y <= SPIELFELD_YSIZE + SPIELFELD_OFFSET_Y; y++) {
		console_zeichne_punkt(SPIELFELD_OFFSET_X + SPIELFELD_XSIZE + 1, y, ' ');
	}
	// Unten zeichnen
	for (int x = SPIELFELD_OFFSET_X; x <= SPIELFELD_XSIZE + SPIELFELD_OFFSET_X + 1; x++) {
		console_zeichne_punkt(x, SPIELFELD_OFFSET_Y+SPIELFELD_YSIZE+1, ' ');
	}
	// Links zeichnen
	for (int y = SPIELFELD_OFFSET_Y+1; y <= SPIELFELD_YSIZE + SPIELFELD_OFFSET_Y; y++) {
		console_zeichne_punkt(SPIELFELD_OFFSET_X, y, ' ');
	}
}

void spiel_pruefe_kollission(Spiel* spiel_ptr)
{
	//Aufgabe 4d)
	/*
	1) Schlange 1 Schlange 2 beißt
	2) Schlange 1 sich selbst beißt
	3) Schlange 1 in den Rand beißt
	4) Schlange 2 Schlange 1 beißt
	5) Schlange 2 sich selbst beißt
	6) Schlange 2 in den Rand beißt
	*/

	char ergebnis = 0;

	// 1) Schlange 1 Schlange 2 beißt
	if (element_folge_pruefen(spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr, spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr) == 1) {
		spiel_ptr->s1_ptr->punkte = 0;
		ergebnis += 1;
	}

	//2) Schlange 1 sich selbst beißt
	if (element_folge_pruefen(spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr, spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr->nachfolger_ptr) == 1) {
		spiel_ptr->s1_ptr->punkte = 0;
		ergebnis += 1;
	}

	// 3) Schlange 1 in den Rand beißt
	int s1x = spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr->pos.x;
	int s1y = spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr->pos.y;
	// 3a) Linker oder Rechter Rand
	if (s1x <= SPIELFELD_OFFSET_X + 1 || s1x >= (SPIELFELD_OFFSET_X + SPIELFELD_XSIZE)) {
		spiel_ptr->s1_ptr->punkte = 0;
		ergebnis += 1;
	}
	// 3b) Linker oder Rechter Rand
	if (s1y <= SPIELFELD_OFFSET_Y + 1 || s1y >= (SPIELFELD_OFFSET_Y + SPIELFELD_YSIZE)) {
		spiel_ptr->s1_ptr->punkte = 0;
		ergebnis += 1;
	}

	// 4) Schlange 2 Schlange 1 beißt
	if (element_folge_pruefen(spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr, spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr) == 1) {
		spiel_ptr->s2_ptr->punkte = 0;
		ergebnis += 1;
	}

	// 5) Schlange 2 sich selbst beißt
	if (element_folge_pruefen(spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr, spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr->nachfolger_ptr) == 1) {
		spiel_ptr->s2_ptr->punkte = 0;
		ergebnis += 1;
	}

	// 6) Schlange 2 in den Rand beißt
	int s2x = spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr->pos.x;
	int s2y = spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr->pos.y;
	// 6a) Linker oder Rechter Rand
	if (s2x <= SPIELFELD_OFFSET_X + 1 || s2x >= (SPIELFELD_OFFSET_X + SPIELFELD_XSIZE)) {
		spiel_ptr->s2_ptr->punkte = 0;
		ergebnis += 1;
	}
	// 6b) Linker oder Rechter Rand
	if (s2y <= SPIELFELD_OFFSET_Y + 1 || s2y >= (SPIELFELD_OFFSET_Y + SPIELFELD_YSIZE)) {
		spiel_ptr->s2_ptr->punkte = 0;
		ergebnis += 1;
	}
	if (ergebnis >= 1) {
		spiel_ptr->run = 0;
	}
}

void spiel_zeichne_zahl(int zahl, int x_pos, int y_pos, int farbe) {
	int numberfont[] = {
			0,1,1,0,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			0,1,1,0,
			0,0,1,0,
			0,1,1,0,
			1,0,1,0,
			0,0,1,0,
			0,0,1,0,
			0,0,1,0,
			0,0,1,0,
			0,1,1,0,
			1,0,0,1,
			0,0,0,1,
			0,0,1,0,
			0,1,0,0,
			1,0,0,0,
			1,1,1,1,
			0,1,1,0,
			1,0,0,1,
			0,0,0,1,
			0,0,1,0,
			0,0,0,1,
			1,0,0,1,
			0,1,1,0,
			1,0,0,1,
			1,0,0,1,
			1,0,0,1,
			1,1,1,1,
			0,0,0,1,
			0,0,0,1,
			0,0,0,1,
			1,1,1,1,
			1,0,0,0,
			1,0,0,0,
			1,1,1,0,
			0,0,0,1,
			1,0,0,1,
			0,1,1,0,
			0,1,1,0,
			1,0,0,1,
			1,0,0,0,
			1,1,1,0,
			1,0,0,1,
			1,0,0,1,
			0,1,1,0,
			1,1,1,1,
			0,0,0,1,
			0,0,0,1,
			0,0,1,0,
			0,0,1,0,
			0,1,0,0,
			0,1,0,0,
			0,1,1,0,
			1,0,0,1,
			1,0,0,1,
			0,1,1,0,
			1,0,0,1,
			1,0,0,1,
			0,1,1,0,
			0,1,1,0,
			1,0,0,1,
			1,0,0,1,
			0,1,1,0,
			0,0,0,1,
			1,0,0,1,
			0,1,1,0,
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1,
			1,1,1,1
	};
	// 0: 00 - 27
	// 1: 28 - 55

	int offset = zahl * 28;


	for (int y = 0; y < 7; y++) {
		for (int x = 0; x < 4; x++) {
			if (numberfont[x+4*y+offset] == 1) {
				attron(COLOR_PAIR(farbe));
				console_zeichne_punkt(x+x_pos, y+y_pos, ' ');
			}
		}
	}
}

void spiel_zeichne_spielstand(Spiel* spiel_ptr) {
 	//Aufgabe 4e)     OPTIONAL
	if (spiel_ptr == NULL) {
		// Initialisierung des Spiels
		spiel_zeichne_zahl(0, 31, 1, SPIELER_1_FARBE);
		spiel_zeichne_zahl(0, 37, 1, SPIELER_1_FARBE);
		spiel_zeichne_zahl(0, 43, 1, SPIELER_1_FARBE);
		spiel_zeichne_zahl(10, 49, 1, SPIELFELD_RAND_FARBE);
		spiel_zeichne_zahl(0, 55, 1, SPIELER_2_FARBE);
		spiel_zeichne_zahl(0, 61, 1, SPIELER_2_FARBE);
		spiel_zeichne_zahl(0, 67, 1, SPIELER_2_FARBE);
	} else {
		// Neuer Punktestand ...
		// Schlange 1
		// Alten Stand löschen
		spiel_zeichne_zahl(11, 31, 1, SPIELFELD_HINTERGRUND_FARBE);
		spiel_zeichne_zahl(11, 37, 1, SPIELFELD_HINTERGRUND_FARBE);
		spiel_zeichne_zahl(11, 43, 1, SPIELFELD_HINTERGRUND_FARBE);

		int punkte = spiel_ptr->s1_ptr->punkte;
		// Neuen Spielstand zeichnen
		spiel_zeichne_zahl(punkte%10, 43, 1, SPIELER_1_FARBE);
		punkte = punkte/10;
		spiel_zeichne_zahl(punkte%10, 37, 1, SPIELER_1_FARBE);
		punkte = punkte/10;
		spiel_zeichne_zahl(punkte%10, 31, 1, SPIELER_1_FARBE);

		//bei Schlange 2
		// Alten Stand löschen
		spiel_zeichne_zahl(11, 55, 1, SPIELFELD_HINTERGRUND_FARBE);
		spiel_zeichne_zahl(11, 61, 1, SPIELFELD_HINTERGRUND_FARBE);
		spiel_zeichne_zahl(11, 67, 1, SPIELFELD_HINTERGRUND_FARBE);

		punkte = spiel_ptr->s2_ptr->punkte;
		// Neuen Spielstand zeichnen
		spiel_zeichne_zahl(punkte%10, 67, 1, SPIELER_2_FARBE);
		punkte = punkte/10;
		spiel_zeichne_zahl(punkte%10, 61, 1, SPIELER_2_FARBE);
		punkte = punkte/10;
		spiel_zeichne_zahl(punkte%10, 55, 1, SPIELER_2_FARBE);

		// Doppelpunkte zeichnen
		spiel_zeichne_zahl(10, 49, 1, SPIELFELD_RAND_FARBE);
	}
}

