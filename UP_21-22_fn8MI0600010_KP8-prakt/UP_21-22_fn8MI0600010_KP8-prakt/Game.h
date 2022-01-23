/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Nikolay Nikolaev
* @idnumber 8MI0600010
* @compiler VC
*
* <declares signatures of functions used in "Game.cpp">
*
*/

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