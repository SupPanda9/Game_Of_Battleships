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

void startGameMenuOption(player& player) {
	while (true) {
		menuEnding();
		
		std::cout << player.name << " it's your turn! Pick:" << std::endl;
		
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

			std::cout << "Use 'u' to navigate up and 'd' to navigate down through the options. \nPress 'c' or 'C' to choose. Don't forget to press enter after every command." << std::endl;
			std::cout << std::endl;
			std::cout << "> MAKE YOUR CONFIGURATION NOW <" << std::endl;
			std::cout << std::endl;
			std::cout << "  USE A PREMADE CONFIGURATION" << std::endl;
			std::cout << std::endl;
			

			break;
		case 2:
			clearConsole();

			menuEnding();

			std::cout << player.name << " it's your turn! Pick:" << std::endl;

			std::cout << "Use 'u' to navigate up and 'd' to navigate down through the options. \nPress 'c' or 'C' to choose. Don't forget to press enter after every command." << std::endl;
			std::cout << std::endl;
			std::cout << "  MAKE YOUR CONFIGURATION NOW" << std::endl;
			std::cout << std::endl;
			std::cout << "> USE A PREMADE CONFIGURATION <" << std::endl;
			std::cout << std::endl;

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
	default:
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