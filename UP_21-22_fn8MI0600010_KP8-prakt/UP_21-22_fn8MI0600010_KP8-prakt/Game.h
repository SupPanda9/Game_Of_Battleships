#pragma once
#include "Menu.h"

struct point {
	char letter;
	int number;
};

const int MAX_PLAYER_NICKNAME_SIZE = 15;
const char TERMINATING_ZERO = '\0';

const char DESTROYED = 'X';
const char FOUND = 'F';
const char UNSUCCESSFUL_GUESS = 'U';

void players(player&, player&);

void enterPlayers(player &, char *);

void checkForSameNickname(player &, player &);

void nameVerification(player&, player&);

void game(player&, player&);

void turns(player&, player&, int&, int&);

void turnOption(player&, char&);

void guessPosition(player&, player&, point&, bool&, bool, int&);

bool isLastCellOfShip(player&, point&);