#include <iostream>
#include "Menu.h"
#include "Animations.h"

void menu() {
	const int LONG_TIME = 750000000;
	const int SHORT_TIME = 250000000;
	int option = 1;

	wait(SHORT_TIME);

	menuHeading();

	std::cout << "> INSTRUCTIONS <" << std::endl;
	std::cout << std::endl;
	std::cout << "  START GAME" << std::endl;
	std::cout << std::endl;
	std::cout << "  VIEW PREVIOUS RESULTS" << std::endl;
	std::cout << std::endl;

	changeOption(option);
	
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
			if (option == 3) {
				option = 1;
			}
			else option++;
			break;
		case 'u':
		case 'U':
			if (option == 1) {
				option = 3;
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

			break;

		}
	}
}