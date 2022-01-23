#pragma once
#include "Menu.h"

const int SMALL_SHIP_SIZE = 2;
const int MEDIUM_SHIP_SIZE = 3;
const int LARGE_SHIP_SIZE = 4;
const int CRUISER_SIZE = 6;

const int ALL_SHIPS_COUNT = 10;
const int SMALL_SHIP_COUNT = 4;
const int MEDIUM_SHIP_COUNT = 3;
const int LARGE_SHIP_COUNT = 2;
const int CRUISER_COUNT = 1;

const char CAPITAL_A = 'A';
const char CAPITAL_Z = 'Z';
const char SMALL_A = 'a';
const char SMALL_J = 'j';
const char SMALL_Z = 'z';

const int SMALL_TO_CAPITAL_DIFF = 32;

const char DIRECTION_UP = 'u';
const char DIRECTION_DOWN = 'd';
const char DIRECTION_LEFT = 'l';
const char DIRECTION_RIGHT = 'r';

const char OCCUPIED = 'O';
const char SHIP = 'S';
const char SPACE = ' ';
const char ZERO = '0';

struct ship {
	int size;
	int count;
};

struct placer {
	char letter;
	int number;
	char direction;
};

void board(player&);

void boardFromFile(player&);

void fillBoard(player&, char);

int interpretLetterAsArrayIndex(char);

void boardVisualiser(player&, char);

bool validPlace(char, placer&, player&);

char toLowerCase(char&);

void placeShips(player&, ship&, ship&, ship&, ship&, placer&, char);

void occupyPosition(player&);

bool isItAnUnoccupiedPosition(player&, placer&, int);

void fillOccupiedBoardWZero(player&);

void editShipsPosition(player&, ship&, ship&, ship&, ship&, placer&, char); 

void removeShip(player&, ship&, ship&, ship&, ship&, char&);