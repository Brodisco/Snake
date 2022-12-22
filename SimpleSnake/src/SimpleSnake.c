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

		// Zeichne den Spielfeldrand
		spiel_zeichne_rand();
		// Zeichne Anfangs Punktestand
		spiel_zeichne_spielstand(NULL);
		// Erzeugt eine Struktur zum Einlesen
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

			//PickUps

			if(spiel_ptr->pickup_ptr == NULL) {
				// Aktuell kein PickUp
				spiel_ptr->pickup_ptr = pickUp_erzeugen();
				Element* testElement_ptr = element_erzeugen();

				do {
				// Innerhalb des Spielfeds mit 1 Punkt abstand
				testElement_ptr->pos.x = rand()%(SPIELFELD_XSIZE-2)+SPIELFELD_OFFSET_X+2;
				testElement_ptr->pos.y = rand()%(SPIELFELD_YSIZE-2)+SPIELFELD_OFFSET_Y+2;
				} while (element_folge_pruefen(testElement_ptr, spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr) == 1 || element_folge_pruefen(testElement_ptr, spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr) == 1);
				spiel_ptr->pickup_ptr->pos.x = testElement_ptr->pos.x;
				spiel_ptr->pickup_ptr->pos.y = testElement_ptr->pos.y;
				free(testElement_ptr);
				pickUp_zeichne(spiel_ptr->pickup_ptr, SPIELER_2_FARBE/*FARBE_MAGENTA*/);
			}

			if(spiel_ptr->pickup_ptr != NULL) {
				spiel_ptr->pickup_ptr = schlange_bearbeite_pickup(spiel_ptr->s1_ptr, spiel_ptr->pickup_ptr);
			}
			if(spiel_ptr->pickup_ptr != NULL) {
				spiel_ptr->pickup_ptr = schlange_bearbeite_pickup(spiel_ptr->s2_ptr, spiel_ptr->pickup_ptr);
			}

			spiel_zeichne_spielstand(spiel_ptr);

			//Prüfe auf Kollission => Relevant für Spielende
						spiel_pruefe_kollission(spiel_ptr);

			//Spielzeit erhöhen
			spiel_ptr->schritte++;

			refresh();
			//Pausieren des Main-Thread - Spielgeschwindigkeit
			usleep(SPIEL_GESCHWINDIGKEIT);
		}

		console_leeren();

		console_zeichne_endscreen(spiel_ptr);
		spiel_zeichne_spielstand(spiel_ptr);

		refresh();

		// Aufräumen
		//TODO Liste freigeben
		free(eingabe_ptr);
		free(spiel_ptr->pickup_ptr);

		//free(spiel_ptr->s2_ptr);
		free(spiel_ptr->s1_ptr);
		free(spiel_ptr->s2_ptr);
		free(spiel_ptr);

		// Warte auf Tastendruck
		quitCharacter = 'a';
		while (quitCharacter != 'q' && quitCharacter != 'r') {
			quitCharacter = getchar();
		}

	}

	endwin();

	return EXIT_SUCCESS;
}
