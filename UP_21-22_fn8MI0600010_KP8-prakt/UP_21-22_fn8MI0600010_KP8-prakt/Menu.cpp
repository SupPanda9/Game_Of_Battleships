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

void changeOption(int &option) { //changes the options on the first menu screen
	while (true) {
		char symbol;

		std::cin >> symbol;

		if (symbol == 'C' || symbol == 'c') {
			std::cin.ignore();

			break;
		}

		switch (symbol) { //changes the value of option, based on the given key (d or u)
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

		switch (option) { //changes the shown selected option
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

void submenu(int option, player& firstPlayer, player& secondPlayer) { //gets information from changeOption and proceeds to the next stage of the game 
	std::fstream instructions;
	std::fstream scoreBoard;

	bool thereIsText = false;

	switch (option) {
	case 1:
		clearConsole();

		instructions.open("instructions.txt", std::ios::in);
		if (instructions.is_open()) { //prints the content of instructions.txt
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

		startPreparation(firstPlayer, secondPlayer); //continues to game
		
		break;
	case 3:
		clearConsole();

		scoreBoard.open("scoreBoard.txt", std::ios::in); //prints the contents of scoreBoard
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
		
		if (thereIsText) { //if there is text in the file, we will be given an option to delete it
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

void startPreparation(player& firstPlayer, player& secondPlayer) { //starts the game
	players(firstPlayer, secondPlayer); //enters players

	checkForSameNickname(firstPlayer, secondPlayer); //asks players to change their nicknames if they are the same

	nameVerification(firstPlayer, secondPlayer); //asks players if they would like to change their nicknames

	clearConsole();

	game(firstPlayer, secondPlayer); //starts the real game
}

void startGameMenuOption(player& player) { //asks whether the player would like to enter his board from the console or upload a premade file, works similarly to changeOption
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
		clearConsole(); //enter board from the console

		board(player);
		
		break;
	case 2:
		clearConsole();
		
		boardFromFile(player); //enter board from a file
		
		break;
	default:
		break;
	}
}