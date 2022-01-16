#include <iostream>
#include "Menu.h"
#include "Animations.h"
#include <fstream>
#include <string>
#include "Game.h"

void menu() {
	clearConsole();

	int option = 1;

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
	
	Submenu(option);
}

void changeOption(int &option) { 
	const int FIRST_MENU_NUMBER = 1, LAST_MENU_NUMBER=3;
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

void Submenu(int option) {
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
		game();
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


