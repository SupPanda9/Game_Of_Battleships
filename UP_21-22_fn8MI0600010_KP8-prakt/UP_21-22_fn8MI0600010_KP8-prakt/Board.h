#pragma once
#include "Menu.h"

struct ship {
	int size;
	int count;
};

struct placer {
	char letter;
	int number;
	char direction;
};

void fillBoard(player&);

void board(player&);

int interpretLetterAsArrayIndex(char);

void boardVisualiser(player&);

bool validPlace(char, placer&, player&);

char toLowerCase(char);

void placeShips(player&, ship&, ship&, ship&, ship&, placer&, char);

void occupyPosition(player&);

bool isItAnUnoccupiedPosition(player&, placer&, int);

void fillOccupiedBoardWZero(player&);

void editShipsPosition(player&, ship&, ship&, ship&, ship&, placer&, char); 

void removeShip(player&, ship&, ship&, ship&, ship&, char&);