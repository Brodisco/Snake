/*
 ============================================================================
 Name        : SimpleSnake.c
 Author      : Mario Wegmann
 Version     :
 Copyright   : Hochschule Augsburg
 ============================================================================
 */

// Informationen zu ncurses => https://de.wikibooks.org/wiki/Ncurses:_Grundlegendes#ncurses_und_I/O-Befehle_von_C
// Informationen zu ncurses => https://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap13-002.htm

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "Schlange.h"
#include "Console.h"
#include "Eingabe.h"
#include "Configuration.h"
#include "Spiel.h"
#include "PickUp.h"

int main(void) {
	//Startet ncurses und initialisiert es
	console_init();
	char quitCharacter = 'b';
	console_leeren();
	console_zeichne_startscreen();
	getchar();

	while (quitCharacter != 'q') {
		console_leeren();

		srand(time(0));

		//Zeichne den Spielfeldrand
		spiel_zeichne_rand();

		//Erzeugt eine Struktur zum Einlesen
		Eingabe* eingabe_ptr = eingabe_erzeugen();


		//Erzeugt ein Spiel mit zwei Schlangen und initialisiert es
		Spiel* spiel_ptr = spiel_erzeugen();

		refresh();
		while(spiel_ptr->run == 1)
		{
			//Einlesen der Eingabe
			eingabe_einlesen(eingabe_ptr);

			//Zeichne Schlange 1
			schlange_zeichne(spiel_ptr->s1_ptr, SPIELFELD_HINTERGRUND_FARBE);
			schlange_bewege(spiel_ptr->s1_ptr, eingabe_ptr->letzte_eingabe_spieler_1);
			schlange_zeichne(spiel_ptr->s1_ptr, SPIELER_1_FARBE);

			//Zeichne Schlange 2
			schlange_zeichne(spiel_ptr->s2_ptr, SPIELFELD_HINTERGRUND_FARBE);
			schlange_bewege(spiel_ptr->s2_ptr, eingabe_ptr->letzte_eingabe_spieler_2);
			schlange_zeichne(spiel_ptr->s2_ptr, SPIELER_2_FARBE);

			//Prüfe auf Kollission => Relevant für Spielende
			spiel_pruefe_kollission(spiel_ptr);

			//PickUps

			if(spiel_ptr->pickup_ptr == NULL) {
				// Aktuell kein PickUp
				spiel_ptr->pickup_ptr = pickUp_erzeugen();
				spiel_ptr->pickup_ptr->pos.x = rand()%SPIELFELD_XSIZE+SPIELFELD_OFFSET_X;
				spiel_ptr->pickup_ptr->pos.y = rand()%SPIELFELD_YSIZE+SPIELFELD_OFFSET_Y;
				pickUp_zeichne(spiel_ptr->pickup_ptr, FARBE_MAGENTA);
			}

			schlange_bearbeite_pickup(spiel_ptr->s1_ptr, spiel_ptr->pickup_ptr);
			schlange_bearbeite_pickup(spiel_ptr->s2_ptr, spiel_ptr->pickup_ptr);

			//Spielzeit erhöhen
			spiel_ptr->schritte++;

			refresh();
			//Pausieren des Main-Thread - Spielgeschwindigkeit
			usleep(SPIEL_GESCHWINDIGKEIT);
		}

		console_leeren();
		console_zeichne_endscreen();

		// Aufräumen
		//TODO Liste freigeben
		free(eingabe_ptr);
		free(spiel_ptr->pickup_ptr);

		//free(spiel_ptr->s2_ptr);
		free(spiel_ptr->s1_ptr);
		free(spiel_ptr->s2_ptr);
		free(spiel_ptr);

		// Warte auf Tastendruck
		quitCharacter = getchar();
	}

	endwin();

	return EXIT_SUCCESS;
}
