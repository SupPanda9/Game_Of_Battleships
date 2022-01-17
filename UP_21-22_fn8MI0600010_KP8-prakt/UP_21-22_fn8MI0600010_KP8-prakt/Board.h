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

void board(player&);

int interpretLetterAsArrayIndex(char);

void boardVisualiser();

bool validPlace(char, placer&, player&);

char toLowerCase(char symbol);