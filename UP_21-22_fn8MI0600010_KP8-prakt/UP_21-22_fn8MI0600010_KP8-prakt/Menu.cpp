#include <iostream>
#include "Menu.h"
#include "Animations.h"
#include <fstream>
#include <string>
#include "Game.h"

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
		std::cin>>symbol;

		if (symbol == 'C' || symbol == 'c') {
			break;
		}

		switch (symbol) {
		case 'd':
		case 'D':
			if (option == LAST_MENU_NUMBER) {
				option = FIRST_MENU_NUMBER;
			}
			else option++;
			break;
		case 'u':
		case 'U':
			if (option == FIRST_MENU_NUMBER) {
				option = LAST_MENU_NUMBER;
			}
			else option--;
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

		}
	}
}

void submenu(int option, player& firstPlayer, player& secondPlayer) {
	std::fstream instructions;
	std::fstream scoreBoard;

	switch (option) {
	case 1:
		clearConsole();

		instructions.open("instructions.txt", std::ios::in); //make it a function
		if (instructions.is_open()) {
			std::string line;
			while (getline(instructions, line)) {
				std::cout << line << std::endl;
			}
			instructions.close();
		}
		std::cout << std::endl;
		
		pressAnyKeyToContinue();

		menu();
		break;
	case 2:
		clearConsole();
		startPreparation(firstPlayer,secondPlayer);
		break;
	case 3:
		clearConsole();

		scoreBoard.open("scoreBoard.txt", std::ios::in); //make it a function
		if (scoreBoard.is_open()) {
			std::string line;
			while (getline(scoreBoard, line)) {
				std::cout << line << std::endl;
			}
			scoreBoard.close();
		}
		std::cout << std::endl;

		pressAnyKeyToContinue();

		menu();
		break;

	default:
		menu();
		break;
	}
}

void startGameMenu(player& firstPlayer, player& secondPlayer) {
	int startOption = FIRST_MENU_NUMBER;

	startGameMenuOption(startOption);

	startGameSubmenu(startOption,firstPlayer,secondPlayer);
}

const int LAST_START_MENU_NUMBER = 2;

void startGameMenuOption(int &startOption) {
	while (true) {
		char symbol;
		std::cin >> symbol;

		if (symbol == 'C' || symbol == 'c') {
			break;
		}

		switch (symbol) {
		case 'd':
		case 'D':
			if (startOption == LAST_START_MENU_NUMBER) {
				startOption = FIRST_MENU_NUMBER;
			}
			else {
				startOption++;
			}
			break;
		case 'u':
		case 'U':
			if (startOption == FIRST_MENU_NUMBER) {
				startOption = LAST_START_MENU_NUMBER;
			}
			else {
				startOption--;
			}
			break;
			break;
		default:
			break;
		}

		switch (startOption) {
		case 1:
			clearConsole();

			menuEnding();

			std::cout << "Use 'u' to navigate up and 'd' to navigate down through the options. \nPress 'c' or 'C' to choose. Don't forget to press enter after every command." << std::endl;
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
			std::cout << "Use 'u' to navigate up and 'd' to navigate down through the options. \nPress 'c' or 'C' to choose. Don't forget to press enter after every command." << std::endl;
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
}

void startGameSubmenu(int startOption, player& firstPlayer, player& secondPlayer) {

	switch (startOption) {
	case 1:
		clearConsole();
		game(firstPlayer, secondPlayer);
		break;
	case 2:
		clearConsole();
		std::cout << "Enter your file name" << std::endl;
	default:
		break;
	}
}

void startPreparation(player& firstPlayer, player& secondPlayer) {
	players(firstPlayer, secondPlayer);

	checkForSameNickname(firstPlayer, secondPlayer);

	nameVerification(firstPlayer, secondPlayer);

	clearConsole();

	menuEnding();

	std::cout << "Use u to navigate up and d to navigate down through the options. \nPress c/C to choose. Don't forget to press enter after every command." << std::endl;
	std::cout << std::endl;
	std::cout << "> MAKE YOUR CONFIGURATION NOW <" << std::endl;
	std::cout << std::endl;
	std::cout << "  USE A PREMADE CONFIGURATION" << std::endl;
	std::cout << std::endl;

	menuEnding();

	startGameMenu(firstPlayer, secondPlayer);
}