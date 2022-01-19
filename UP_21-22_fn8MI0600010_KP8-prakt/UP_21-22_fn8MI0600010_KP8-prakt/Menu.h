#pragma once

const int FIRST_MENU_NUMBER = 1, LAST_MENU_NUMBER = 3;

const int MAX_SIZE_NICKNAME = 15;
const int BOARD_SIZE = 11;

struct player {
	char* name = new char[MAX_SIZE_NICKNAME];
	char board[BOARD_SIZE][BOARD_SIZE];
	char occupiedBoard[BOARD_SIZE][BOARD_SIZE]{{}};
};

void menu();

void changeOption(int &);

void submenu(int, player&, player&);

void startGameMenu(player&, player&);

void startGameMenuOption(int &);

void startGameSubmenu(int, player&, player&);

void startPreparation(player&, player&);