#include <iostream>
#include "Animations.h"
#include "Game.h"
#include "Menu.h"
#include "Board.h"

const int SMALL_SHIP_SIZE = 2;
const int MEDIUM_SHIP_SIZE = 3;
const int LARGE_SHIP_SIZE = 4;
const int CRUISER_SIZE = 6;

const int SMALL_SHIP_COUNT = 4;
const int MEDIUM_SHIP_COUNT = 3;
const int LARGE_SHIP_COUNT = 2;
const int CRUISER_COUNT = 1;

void board(player& player) {
	ship smallShip, mediumShip, largeShip, cruiser;

	smallShip.size = SMALL_SHIP_SIZE;
	smallShip.count = SMALL_SHIP_COUNT;

	mediumShip.size = MEDIUM_SHIP_SIZE;
	mediumShip.count = MEDIUM_SHIP_COUNT;

	largeShip.size = LARGE_SHIP_SIZE;
	largeShip.count = LARGE_SHIP_COUNT;

	cruiser.size = CRUISER_SIZE;
	cruiser.count = CRUISER_COUNT;

	placer shipPlacer;

	char shipSelect;

	menuEnding();

	int allShipsCount;
	int option;

	while (true) {
		menuEnding();
		std::cout << player.name << " is placing ships now!" << std::endl;
		
		allShipsCount = smallShip.count + mediumShip.count + largeShip.count + cruiser.count;
		if (allShipsCount==0) {
			break;
		}
		
		std::cout << "What do you want to do:" << std::endl;
		std::cout << "1. Place a new ship." << std::endl;
		std::cout << "2. Edit the position of an already placed ship." << std::endl;
		std::cout << "3. See your board." << std::endl;
		std::cin >> option;

		if (option == 1) {
			clearConsole();
			while (true) {
				std::cout << "Select a ship - s=small ship, m=medium ship, l=large ship, c=cruiser" << std::endl;
				std::cin >> shipSelect;

				if (toLowerCase(shipSelect) == 's' && smallShip.count == 0) {
					std::cout << "You don't have any more small ships to place! Please choose another!" << std::endl;
				}
				else if (toLowerCase(shipSelect) == 'm' && mediumShip.count == 0) {
					std::cout << "You don't have any more medium ships to place! Please choose another!" << std::endl;
				}
				else if (toLowerCase(shipSelect) == 'l' && largeShip.count == 0) {
					std::cout << "You don't have any more large ships to place! Please choose another!" << std::endl;
				}
				else if (toLowerCase(shipSelect) == 'c' && cruiser.count == 0) {
					std::cout << "You don't have any more cruisers to place! Please choose another!" << std::endl;
				}
				else {
					break;
				}
			}

			std::cout << "Enter coordinates in the format LN, where L stands for letter and\nN stands for number. L can be {A.to.J} and N can be {1.to.10}." << std::endl;
			std::cin >> shipPlacer.letter;
			std::cin >> shipPlacer.number;

			std::cout << "Type r,l,u,d to set the direction for the ship." << std::endl;
			std::cin >> shipPlacer.direction;

			int iterations = 0;

			switch (toLowerCase(shipSelect)) {
			case 's':
				iterations = SMALL_SHIP_SIZE;
				smallShip.count--;
				break;
			case 'm':
				iterations = MEDIUM_SHIP_SIZE;
				mediumShip.count--;
				break;
			case 'l':
				iterations = LARGE_SHIP_SIZE;
				largeShip.count--;
				break;
			case 'c':
				iterations = CRUISER_SIZE;
				cruiser.count--;
				break;
			}

			if (validPlace(shipSelect, shipPlacer, player)) {
				if (shipPlacer.direction == 'u') {
					for (int i = iterations - 1; i >= 0; i--) {
						player.board[i + shipPlacer.number - 1][interpretLetterAsArrayIndex(shipPlacer.letter)] = 'S';
					}
				}
				else if (shipPlacer.direction == 'd') {
					for (int i = 0; i <= iterations; i++) {
						player.board[i + shipPlacer.number - 1][interpretLetterAsArrayIndex(shipPlacer.letter)] = 'S';
					}
				}
				else if (shipPlacer.direction == 'l') {
					for (int i = iterations - 1; i >= 0; i--) {
						player.board[shipPlacer.number - 1][i + interpretLetterAsArrayIndex(shipPlacer.letter)] = 'S';
					}
				}
				else if (shipPlacer.direction == 'r') {
					for (int i = 0; i <= iterations; i++) {
						player.board[shipPlacer.number - 1][i + interpretLetterAsArrayIndex(shipPlacer.letter)] = 'S';
					}
				}
			}
		}
	}
}

int interpretLetterAsArrayIndex(char symbol) {
	switch (symbol) {
	case 'a':
	case 'A':
		return 0;
		break;
	case 'b':
	case 'B':
		return 1;
		break;
	case 'c':
	case 'C':
		return 2;
		break;
	case 'd':
	case 'D':
		return 3;
		break;
	case 'e':
	case 'E':
		return 4;
		break;
	case 'f':
	case 'F':
		return 5;
		break;
	case 'g':
	case 'G':
		return 6;
		break;
	case 'h':
	case 'H':
		return 7;
		break;
	case 'i':
	case 'I':
		return 8;
		break;
	case 'j':
	case 'J':
		return 9;
		break;
	default:
		return -1;
		break;
	}
}

void boardVisualiser() {

}

bool validPlace(char shipSelect, placer &shipPlacer, player &player) { //+ another variable which will be for positions next to other ships
	if (shipSelect=='s' && ((shipPlacer.number==1 && shipPlacer.direction == 'u') || (shipPlacer.number == 10 && shipPlacer.direction == 'd') ||
		((shipPlacer.letter == 'A' || shipPlacer.letter == 'a') && shipPlacer.direction == 'l') ||
		((shipPlacer.letter == 'J' || shipPlacer.letter == 'j') && shipPlacer.direction == 'r'))) {
		return false;
	}
	else if (shipSelect == 'm' && ((shipPlacer.number <= 2 && shipPlacer.direction == 'u') || (shipPlacer.number >= 9 && shipPlacer.direction == 'd') ||
		((shipPlacer.letter == 'A' || shipPlacer.letter == 'a' || shipPlacer.letter == 'B' || shipPlacer.letter == 'b') && shipPlacer.direction == 'l') ||
		((shipPlacer.letter == 'J' || shipPlacer.letter == 'j' || shipPlacer.letter == 'i' || shipPlacer.letter == 'I') && shipPlacer.direction == 'r'))) {
		return false;
	}
	else if (shipSelect == 'l' && ((shipPlacer.number <= 3 && shipPlacer.direction == 'u') || (shipPlacer.number >= 8 && shipPlacer.direction == 'd') ||
		(interpretLetterAsArrayIndex(shipPlacer.letter)<=2 && shipPlacer.direction == 'l') ||
		(interpretLetterAsArrayIndex(shipPlacer.letter)>=7 && shipPlacer.direction == 'r'))) {
		return false;
	}
	else if (shipSelect == 'c' && ((shipPlacer.number <= 5 && shipPlacer.direction == 'u') || (shipPlacer.number >= 6 && shipPlacer.direction == 'd') ||
		(interpretLetterAsArrayIndex(shipPlacer.letter) <= 4 && shipPlacer.direction == 'l') ||
		(interpretLetterAsArrayIndex(shipPlacer.letter) >= 5 && shipPlacer.direction == 'r'))) {
		return false;
	}
	/*else if () {
		return false;
	}*/
	else {
		return true;
	}
}

const char CAPITAL_A = 'A';
const char CAPITAL_Z = 'Z';
const int SMALL_TO_CAPITAL_DIFF = 32;

char toLowerCase(char symbol) {
	if (symbol >= CAPITAL_A && symbol < CAPITAL_Z) {
		symbol = symbol + SMALL_TO_CAPITAL_DIFF;
	}
	return symbol;
}