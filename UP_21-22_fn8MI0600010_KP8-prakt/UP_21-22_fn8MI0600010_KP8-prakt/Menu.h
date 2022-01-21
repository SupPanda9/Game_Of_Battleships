#pragma once

const int FIRST_MENU_NUMBER = 1, LAST_MENU_NUMBER = 3;

const int MAX_SIZE_NICKNAME = 15;
const int BOARD_SIZE = 11;

const int LAST_START_MENU_NUMBER = 2;

struct player {
	char* name = new char[MAX_SIZE_NICKNAME];
	int startOption=FIRST_MENU_NUMBER;
	char board[BOARD_SIZE-1][BOARD_SIZE] = {};
	char occupiedBoard[BOARD_SIZE-1][BOARD_SIZE] = {};
	char helpBoard[BOARD_SIZE-1][BOARD_SIZE] = {};
};

void menu();

void changeOption(int &);

void submenu(int, player&, player&);

void startGameMenuOption(player&);

void startGameSubmenu(player&);

void startPreparation(player&, player&);