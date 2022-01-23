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
* <declares signatures of functions used in "Menu.cpp" and a struct type players>
*
*/

#pragma once

const int FIRST_MENU_NUMBER = 1, LAST_MENU_NUMBER = 3;
const int MAX_SIZE_NICKNAME = 15;
const int BOARD_SIZE = 11;
const int LAST_START_MENU_NUMBER = 2;

struct player {
	char* name = new char[MAX_SIZE_NICKNAME];
	int startOption = FIRST_MENU_NUMBER;
	char board[BOARD_SIZE - 1][BOARD_SIZE] = {};
	char occupiedBoard[BOARD_SIZE - 1][BOARD_SIZE] = {};
	char helpBoard[BOARD_SIZE - 1][BOARD_SIZE] = {};
};

void menu();

void changeOption(int &);

void submenu(int, player&, player&);

void startPreparation(player&, player&);

void startGameMenuOption(player&);

void startGameSubmenu(player&);
