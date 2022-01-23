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
* <implements menu controls that redirect to the right function, responsible for the given option>
*
*/

#include <iostream>
#include "Menu.h"
#include "Animations.h"
#include <fstream>
#include <string>
#include "Game.h"
#include "Board.h"

void menu() {
	struct player firstPlayer;
	struct player secondPlayer;

	clearConsole();

	int option = FIRST_MENU_NUMBER;

	wait(SHORT_TIME);

	menuHeading();

	std::cout << "> INSTRUCTIONS <" << std::endl;
	std::cout << std::endl;
	std::cout << "  START GAME" << std::endl;
	std::cout << std::endl;
	std::cout << "  VIEW PREVIOUS RESULTS" << std::endl;
	std::cout << std::endl;

	menuEnding();

	changeOption(option);
	
	submenu(option, firstPlayer, secondPlayer);
}

void changeOption(int &option) { 
	while (true) {
		char symbol;

		std::cin >> symbol;

		if (symbol == 'C' || symbol == 'c') {
			std::cin.ignore();

			break;
		}

		switch (symbol) {
		case 'd':
		case 'D':
			if (option == LAST_MENU_NUMBER) {
				option = FIRST_MENU_NUMBER;
			}
			else {
				option++;
			}
			break;
		case 'u':
		case 'U':
			if (option == FIRST_MENU_NUMBER) {
				option = LAST_MENU_NUMBER;
			}
			else {
				option--;
			}
			break;
		default:
			break;
		}

		switch (option) {
		case 1:
			clearConsole();

			menuHeading();

			std::cout << "> INSTRUCTIONS <" << std::endl;
			std::cout << std::endl;
			std::cout << "  START GAME" << std::endl;
			std::cout << std::endl;
			std::cout << "  VIEW PREVIOUS RESULTS" << std::endl;
			std::cout << std::endl;

			menuEnding();

			break;
		case 2:
			clearConsole();

			menuHeading();

			std::cout << "  INSTRUCTIONS" << std::endl;
			std::cout << std::endl;
			std::cout << "> START GAME <" << std::endl;
			std::cout << std::endl;
			std::cout << "  VIEW PREVIOUS RESULTS" << std::endl;
			std::cout << std::endl;

			menuEnding();

			break;
		case 3:
			clearConsole();

			menuHeading();

			std::cout << "  INSTRUCTIONS" << std::endl;
			std::cout << std::endl;
			std::cout << "  START GAME" << std::endl;
			std::cout << std::endl;
			std::cout << "> VIEW PREVIOUS RESULTS <" << std::endl;
			std::cout << std::endl;

			menuEnding();

			break;
		default:
			break;
		}
	}
}

void submenu(int option, player& firstPlayer, player& secondPlayer) {
	std::fstream instructions;
	std::fstream scoreBoard;

	bool thereIsText = false;

	switch (option) {
	case 1:
		clearConsole();

		instructions.open("instructions.txt", std::ios::in);
		if (instructions.is_open()) {
			std::string line;

			while (getline(instructions, line)) {
				std::cout << line << std::endl;
			}
			instructions.close();
		}
		else {
			std::cout << "Nothing found!" << std::endl;
		}
		std::cout << std::endl;
		
		pressAnyKeyToContinue();

		menu();

		break;
	case 2:
		clearConsole();

		startPreparation(firstPlayer, secondPlayer);
		
		break;
	case 3:
		clearConsole();

		scoreBoard.open("scoreBoard.txt", std::ios::in);
		if (scoreBoard.is_open()) {
			std::string line;
			while (getline(scoreBoard, line)) {
				if (line.size() == 0) {
					break;
				}
				thereIsText = true;
				
				std::cout << line << std::endl;
			}
			scoreBoard.close();
		}
		else {
			std::cout << "No records found!" << std::endl;
			
			pressAnyKeyToContinue();
		}
		
		if (thereIsText) {
			std::string yesNo;

			std::cout << "Do you wish to delete records? Press y(yes) or any symbol for no." << std::endl;
			
			std::cin >> yesNo;

			if (yesNo[0] == 'y') {
				scoreBoard.open("scoreBoard.txt", std::ios::out | std::ios::trunc);
				scoreBoard.close();
			}
		}
		else {
			std::cout << "No records found!" << std::endl;
		}
		pressAnyKeyToContinue();
		
		menu();

		break;
	default:
		menu();

		break;
	}
}

void startPreparation(player& firstPlayer, player& secondPlayer) {
	players(firstPlayer, secondPlayer);

	checkForSameNickname(firstPlayer, secondPlayer);

	nameVerification(firstPlayer, secondPlayer);

	clearConsole();

	game(firstPlayer, secondPlayer);
}

void startGameMenuOption(player& player) {
	while (true) {
		char symbol;

		std::cin >> symbol;

		if (symbol == 'C' || symbol == 'c') {
			break;
		}

		switch (symbol) {
		case 'd':
		case 'D':
			if (player.startOption == LAST_START_MENU_NUMBER) {
				player.startOption = FIRST_MENU_NUMBER;
			}
			else {
				player.startOption++;
			}
			break;
		case 'u':
		case 'U':
			if (player.startOption == FIRST_MENU_NUMBER) {
				player.startOption = LAST_START_MENU_NUMBER;
			}
			else {
				player.startOption--;
			}
			break;
		default:
			break;
		}

		switch (player.startOption) {
		case 1:
			clearConsole();

			menuEnding();

			std::cout << player.name << " it's your turn! Pick:" << std::endl;

			spacing(1);

			std::cout << "Use 'u' to navigate up and 'd' to navigate down through the options. \nPress 'c' or 'C' to choose. Don't forget to press enter after every\ncommand." << std::endl;
			std::cout << std::endl;
			std::cout << "> MAKE YOUR CONFIGURATION NOW <" << std::endl;
			std::cout << std::endl;
			std::cout << "  USE A PREMADE CONFIGURATION" << std::endl;
			std::cout << std::endl;
			
			menuEnding();

			break;
		case 2:
			clearConsole();

			menuEnding();

			std::cout << player.name << " it's your turn! Pick:" << std::endl;

			spacing(1);

			std::cout << "Use 'u' to navigate up and 'd' to navigate down through the options. \nPress 'c' or 'C' to choose. Don't forget to press enter after every\ncommand." << std::endl;
			std::cout << std::endl;
			std::cout << "  MAKE YOUR CONFIGURATION NOW" << std::endl;
			std::cout << std::endl;
			std::cout << "> USE A PREMADE CONFIGURATION <" << std::endl;
			std::cout << std::endl;
			
			menuEnding();

			break;
		default:
			break;
		}
	}
	std::cin.ignore();
}

void startGameSubmenu(player& player) {
	switch (player.startOption) {
	case 1:
		clearConsole();

		board(player);
		
		break;
	case 2:
		clearConsole();
		
		boardFromFile(player);
		
		break;
	default:
		break;
	}
}