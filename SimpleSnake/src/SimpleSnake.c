/*
 ============================================================================
 Name        : SimpleSnake.c
 Author      : StudentT
 Version     :
 Copyright   : Hochschule Augsburg
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// Informationen zu ncurses => https://de.wikibooks.org/wiki/Ncurses:_Grundlegendes#ncurses_und_I/O-Befehle_von_C
// Informationen zu ncurses => https://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap13-002.htm

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "Schlange.h"
#include "Console.h"
#include "Eingabe.h"
#include "Configuration.h"
#include "pickup.h"
#include "Spiel.h"
#include "spielstand.h"
#include "pixelgruppe.h"


int main(void) {
	//Startet ncurses und initialisiert es
	console_init();

	//Zeichne den Spielfeldrand
	spiel_zeichne_rand();

	//Erzeugt eine Struktur zum Einlesen
	Eingabe* eingabe_ptr = eingabe_erzeugen();

	//Erzeugt ein Spiel mit zwei Schlangen und initialisiert es
	Spiel* spiel_ptr = spiel_erzeugen();

	Spielstand *spielstand_ptr = inti_PixelGruppe(5, 1);

	init_pickup(spiel_ptr);

	CharacterList *pixelList = initPixelGroup();
	printPixelString(pixelList, "SNAKE BY OSZI", 100, 1, SPIELER_1_FARBE);

	refresh();
	getchar();

	while(spiel_ptr->run == 1)
	{

		update_Spielstand(spielstand_ptr, spiel_ptr, pixelList);
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

		print_Pickup(spiel_ptr->pickup_ptr, SPIELFELD_HINTERGRUND_FARBE);
		plaziere_Pickup(spiel_ptr);
		print_Pickup(spiel_ptr->pickup_ptr, SPIELER_1_FARBE);



		//Prüfe auf Kollission => Relevant für Spielende
		spiel_pruefe_kollission(spiel_ptr);

		handle_pickup_conflict(spiel_ptr);





		//Spielzeit erhöhen
		spiel_ptr->schritte++;

		refresh();
		//Pausieren des Main-Thread - Spielgeschwindigkeit
		usleep(SPIEL_GESCHWINDIGKEIT);
	}

	//Warte auf Tastendruck
	getchar();
	endwin();

	return EXIT_SUCCESS;
}
