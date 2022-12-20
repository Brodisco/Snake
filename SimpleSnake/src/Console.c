/*
 *  Console.c
 *
 *  Created on: 12.12.2022
 *      Author: Mario Wegmann
 */

#include "Console.h"
#include <ncurses.h>
#include "Configuration.h"
#include "Bitmap.h"

//Initialisiert ncurses
void console_init()
{
	initscr();				/* Starte curses  		  */
	clear();
	noecho();				// Eingaben werden nicht angezeigt
	cbreak();
	nodelay(stdscr, TRUE);	// Keine Pufferung von getch()
	curs_set(0);			// Verstecke Cursor
	start_color();			// Aktiviere Farbunterstützung

	//Initialisiere Farben
	init_pair(SPIELER_1_FARBE, COLOR_RED, COLOR_GREEN);
	init_pair(SPIELER_2_FARBE, COLOR_RED, COLOR_RED);
	init_pair(SPIELFELD_RAND_FARBE, COLOR_RED, COLOR_BLUE);
	init_pair(SPIELFELD_HINTERGRUND_FARBE, COLOR_RED, COLOR_BLACK);
	attrset(COLOR_PAIR(SPIELFELD_HINTERGRUND_FARBE));

	if (!has_colors())
	{
		printw("Keine Farbunterstützung!!!!!");
	}
	console_leeren();
	console_cursor_verstecken();
}

void console_zeichne_startscreen() {
	int color = 0;
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 104; x++) {
			color = splashScreen[x+104*y];
			switch (color) {
				case 1:
					attron(COLOR_PAIR(SPIELER_1_FARBE));
					console_zeichne_punkt(x, y, ' ');
					break;
				case 2:
					attron(COLOR_PAIR(SPIELER_2_FARBE));
					console_zeichne_punkt(x, y, ' ');
					break;
				case 3:
					attron(COLOR_PAIR(SPIELFELD_RAND_FARBE));
					console_zeichne_punkt(x, y, ' ');
					break;

				case 4:
					attron(COLOR_PAIR(SPIELER_1_FARBE));
					console_zeichne_punkt(x, y, ' ');
					break;

				default:
					break;
			}
		}
	}
	/*

	printw("    /^\\/^\\\n");
	printw("  _|__|  O|\n");
	printw("\\/     /~     \\_/ \\\n");
	printw("\\____|__________/  \\\n");
	printw(" \\_______      \\\n");
	printw("         `\\     \\                 \\\n");
	printw("           |     |                  \\\n");
	printw("          /      /                    \\\n");
	printw("         /     /                       \\\n");
	printw("       /      /                         \\ \\\n");
	printw("      /     /                            \\  \\\n");
	printw("    /     /             _----_            \\   \\\n");
	printw("   /     /           _-~      ~-_         |   |\n");
	printw("  (      (        _-~    _--_    ~-_     _/   |\n");
	printw("   \\      ~-____-~    _-~    ~-_    ~-_-~    /\n");
	printw("     ~-_           _-~          ~-_       _-\n");
	printw("        ~--______-~                ~-___-\n");
	printw("\n");
	printw("Spieler 1: W A S D Spieler 2: I J K L\n");
	printw("\n");
	printw("Beliebige Taste druecken zum Starten!");*/

	refresh();
}

void console_zeichne_endscreen() {
	int color = 0;
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 104; x++) {
			color = gameOverScreen[x+104*y];
			switch (color) {
				case 1:
					attron(COLOR_PAIR(SPIELER_1_FARBE));
					console_zeichne_punkt(x, y, ' ');
					break;
				case 2:
					attron(COLOR_PAIR(SPIELER_2_FARBE));
					console_zeichne_punkt(x, y, ' ');
					break;
				case 3:
					attron(COLOR_PAIR(SPIELFELD_RAND_FARBE));
					console_zeichne_punkt(x, y, ' ');
					break;

				case 4:
					attron(COLOR_PAIR(SPIELER_1_FARBE));
					console_zeichne_punkt(x, y, ' ');
					break;

				default:
					break;
			}
		}
	}
	refresh();
}


//Leere Terminal
void console_leeren()
{
	clear();
}

//Verstecke Cursor
void console_cursor_verstecken()
{
	curs_set(0);			// Verstecke Cursor
}

//Zeigt den Cursor
void console_cursor_zeigen()
{
	curs_set(1);			// Zeige Cursor
}

//Gebe Zeichen c an Position x, y aus
void console_zeichne_punkt(int x, int y, char c)
{
	mvaddch(y, x, c);
}

//Positioniere Cursor an Position x,y
void console_cursor_bewegen(int x, int y)
{
	move(y,x);
}


