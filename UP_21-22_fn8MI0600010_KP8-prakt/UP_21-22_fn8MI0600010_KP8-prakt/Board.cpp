#include <iostream>
#include "Animations.h"
#include "Game.h"
#include "Menu.h"
#include "Board.h"

const int SMALL_SHIP_SIZE = 2;
const int MEDIUM_SHIP_SIZE = 3;
const int LARGE_SHIP_SIZE = 4;
const int CRUISER_SIZE = 6;

const int ALL_SHIPS_COUNT = 10;
const int SMALL_SHIP_COUNT = 4;
const int MEDIUM_SHIP_COUNT = 3;
const int LARGE_SHIP_COUNT = 2;
const int CRUISER_COUNT = 1;

const char CAPITAL_A = 'A';
const char CAPITAL_Z = 'Z';
const char SMALL_A = 'a';
const char SMALL_Z = 'z';

const int SMALL_TO_CAPITAL_DIFF = 32;

const char DIRECTON_UP = 'u';
const char DIRECTION_DOWN = 'd';
const char DIRECTION_LEFT = 'l';
const char DIRECTON_RIGHT = 'r';

const char OCCUPIED = 'O';
const char SHIP = 'S';
const char SPACE = ' ';
const char ZERO = '0';

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

	fillBoard(player);

	menuEnding();

	int allShipsCount;
	char option;
	
	bool tenShipsAvailable = false;

	char shipSelect = SPACE;

	while (true) {
		allShipsCount = smallShip.count + mediumShip.count + largeShip.count + cruiser.count;

		if (allShipsCount == 0) {
			tenShipsAvailable = true;
		}

		while (true) {
			std::cout << "Enter your ships " << player.name << ":" << std::endl;

			std::cout << "What do you want to do:" << std::endl;
			if (!tenShipsAvailable) {
				std::cout << "1. Place a new ship." << std::endl;
			}
			if (tenShipsAvailable) {
				std::cout << "1. Ready!" << std::endl;
			}
			std::cout << "2. Edit the position of an already placed ship." << std::endl;
			std::cout << "3. See your board." << std::endl;

			std::cin.ignore();
			std::cin >> option;

			if (option == '1' || option == '2' || option == '3') {
				break;
			}
			else {
				clearConsole();
			}
		}

		if (option == '1' && !tenShipsAvailable) {
			placeShips(player, smallShip, mediumShip, largeShip, cruiser, shipPlacer, '0');
		}
		else if (option == '1' && tenShipsAvailable) {
			std::cout << "Your final board is:" << std::endl;
			boardVisualiser(player);
			break;
		}
		else if (option == '2') {
			if (allShipsCount == ALL_SHIPS_COUNT) {
				std::cout << "You still haven't placed any ships!" << std::endl;
			}
			else {
				editShipsPosition(player, smallShip, mediumShip, largeShip, cruiser, shipPlacer, shipSelect);
			}
		}
		else if (option == '3') {
			clearConsole();
			boardVisualiser(player);
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

void boardVisualiser(player& player) {
	std::cout << "    ";

	for (int i = 0; i <BOARD_SIZE-1; i++) { //printing the A,B,C... on top of the board
		std::cout << " " << char(CAPITAL_A + i) << " |";
	}

	std::cout << std::endl;
	horizontalLine();
	
	for (int i = 0; i < BOARD_SIZE-1; i++) { 
		if (i != BOARD_SIZE - 2) {
			std::cout << " " << i + 1 << " |"; //printing the numbers in the first column of the borad
		}
		else {
			std::cout << i + 1 << " |";
		}
		for (int j = 0; j < BOARD_SIZE-1; j++) {
			std::cout << " " << player.board[i][j] << " |"; //printing the board
		}
		std::cout << std::endl;
		horizontalLine();
	}
	pressAnyKeyToContinue();
	clearConsole();
}

void placeShips(player& player, ship& smallShip, ship& mediumShip, ship& largeShip, ship& cruiser, placer& shipPlacer, char shipSelect) {
	clearConsole();
	
	if (shipSelect == ZERO) {
		while (true) {
			menuEnding();

			while (true) {
				std::cout << "Select a ship - s=small ship, m=medium ship, l=large ship, c=cruiser" << std::endl;

				std::cin.ignore();
				std::cin >> shipSelect;

				if (toLowerCase(shipSelect) == 's' || toLowerCase(shipSelect) == 'm' || toLowerCase(shipSelect) == 'l' || toLowerCase(shipSelect) == 'c') {
					break;
				}
				else {
					clearConsole();
				}
			}

			if (toLowerCase(shipSelect) == 's' && smallShip.count == 0) {
				std::cout << "You don't have any more small ships to place! Please choose another!" << std::endl;
				pressAnyKeyToContinue();
				clearConsole();
			}
			else if (toLowerCase(shipSelect) == 'm' && mediumShip.count == 0) {
				std::cout << "You don't have any more medium ships to place! Please choose another!" << std::endl;
				pressAnyKeyToContinue();
				clearConsole();
			}
			else if (toLowerCase(shipSelect) == 'l' && largeShip.count == 0) {
				std::cout << "You don't have any more large ships to place! Please choose another!" << std::endl;
				pressAnyKeyToContinue();
				clearConsole();
			}
			else if (toLowerCase(shipSelect) == 'c' && cruiser.count == 0) {
				std::cout << "You don't have any more cruisers to place! Please choose another!" << std::endl;
				pressAnyKeyToContinue();
				clearConsole();
			}
			else {  //?
				break;
			}
		}
	}
	int iterations = 0;

	switch (toLowerCase(shipSelect)) {
	case 's':
		iterations = SMALL_SHIP_SIZE;
		break;
	case 'm':
		iterations = MEDIUM_SHIP_SIZE;
		break;
	case 'l':
		iterations = LARGE_SHIP_SIZE;
		break;
	case 'c':
		iterations = CRUISER_SIZE;
		break;
	}
	
	//entering ships on position LN

	std::cout << "Enter coordinates to place a ship in the format LN, where L stands for\nletter and N stands for number. L can be {A.to.J} and N can be {1.to.10}." << std::endl;
	std::cin.ignore();
	std::cin >> shipPlacer.letter;
	std::cin >> shipPlacer.number; //remove the exceptions especially when giving char to int and get values until 

	std::cout << "Type r,l,u,d for right, left, up and down to set the direction for the ship." << std::endl;
	std::cin >> shipPlacer.direction;

	if (validPlace(shipSelect, shipPlacer, player) && isItAnUnoccupiedPosition(player, shipPlacer, iterations)) {
		if (shipPlacer.direction == 'u') {
			for (int i = 0; i < iterations; i++) {
				player.board[shipPlacer.number - i-1][interpretLetterAsArrayIndex(shipPlacer.letter)] = SHIP;
			}
		}
		else if (shipPlacer.direction == 'd') {
			for (int i = 0; i < iterations; i++) {
				player.board[i + shipPlacer.number-1][interpretLetterAsArrayIndex(shipPlacer.letter)] = SHIP;
			}
		}
		else if (shipPlacer.direction == 'l') {
			for (int i = 0; i < iterations; i++) {
				player.board[shipPlacer.number-1][interpretLetterAsArrayIndex(shipPlacer.letter) - i] = SHIP;
			}
		}
		else if (shipPlacer.direction == 'r') {
			for (int i = 0; i < iterations; i++) {
				player.board[shipPlacer.number-1][i + interpretLetterAsArrayIndex(shipPlacer.letter)] = SHIP;
			}
		}

		occupyPosition(player);

		switch (toLowerCase(shipSelect)) {
		case 's':
			smallShip.count--;
			break;
		case 'm':
			mediumShip.count--;
			break;
		case 'l':
			largeShip.count--;
			break;
		case 'c':
			cruiser.count--;
			break;
		}
	}
	else {
		std::cout << "Invalid position!" << std::endl;
		pressAnyKeyToContinue();
	}
	clearConsole();
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
	else {
		return true;
	}
}

bool isItAnUnoccupiedPosition(player& player, placer& shipPlacer, int iterations) { //checks if any of the places where a ship will be added is occupied (has a ship on or next to it)
	if (shipPlacer.direction == 'u') {
		for (int i = 0; i < iterations; i++) {
			if (player.occupiedBoard[shipPlacer.number - i - 1][interpretLetterAsArrayIndex(shipPlacer.letter)] == OCCUPIED) {
				return false;
			}
		}
	}
	else if (shipPlacer.direction == 'd') {
		for (int i = 0; i < iterations; i++) {
			if (player.occupiedBoard[i + shipPlacer.number - 1][interpretLetterAsArrayIndex(shipPlacer.letter)] == OCCUPIED) {
				return false;
			}
		}
	}
	else if (shipPlacer.direction == 'l') {
		for (int i = 0; i < iterations; i++) {
			if (player.occupiedBoard[shipPlacer.number - 1][interpretLetterAsArrayIndex(shipPlacer.letter) - i] == OCCUPIED) {
				return false;
			}
		}
	}
	else if (shipPlacer.direction == 'r') {
		for (int i = 0; i < iterations; i++) {
			if (player.occupiedBoard[shipPlacer.number - 1][i + interpretLetterAsArrayIndex(shipPlacer.letter)] == OCCUPIED) {
				return false;
			}
		}
	}
	else {
		return true;
	}
}

char toLowerCase(char symbol) {
	if (symbol >= CAPITAL_A && symbol <= CAPITAL_Z) {
		symbol = symbol + SMALL_TO_CAPITAL_DIFF;
	}
	return symbol;
}

void fillBoard(player& player) {
	for (int i = 0; i < BOARD_SIZE - 1; i++) {
		for (int j = 0; j < BOARD_SIZE - 1; j++) {
			player.board[i][j] = SPACE;
		}
	}
}

void occupyPosition(player& player) {
	for (int i = 0; i < BOARD_SIZE - 1; i++) { //check board for invalid places due to bordering a ship
		for (int j = 0; j < BOARD_SIZE-1; j++) {
			if (player.board[i][j] == SHIP) {
				player.occupiedBoard[i][j] = OCCUPIED; //O stands for occupied
				
				if (j != 0) {
					player.occupiedBoard[i][j - 1] = OCCUPIED;
				}
				if (i != 0) {
					player.occupiedBoard[i-1][j] = OCCUPIED;
				}
				if (i != 0 && j != 0) {
					player.occupiedBoard[i - 1][j - 1] = OCCUPIED;
				}
				if (j != 9) {
					player.occupiedBoard[i][j + 1] = OCCUPIED;
				}
				if (i != 9) {
					player.occupiedBoard[i + 1][j] = OCCUPIED;
				}
				if (i != 9 && j != 9) {
					player.occupiedBoard[i + 1][j + 1] = OCCUPIED;
				}
				if (j != 0 && i != 9) {
					player.occupiedBoard[i + 1][j - 1] = OCCUPIED;
				}
				if (j != 9 && i != 0) {
					player.occupiedBoard[i - 1][j + 1] = OCCUPIED;
				}
			}
		}
	} 
}

void editShipsPosition(player& player, ship& smallShip, ship& mediumShip, ship& largeShip, ship& cruiser, placer& shipPlacer, char shipSelect) {
	removeShip(player, smallShip, mediumShip, largeShip, cruiser, shipSelect);

	fillOccupiedBoardWZero(player);
	occupyPosition(player);

	placeShips(player, smallShip, mediumShip, largeShip, cruiser, shipPlacer, shipSelect);
}

void fillOccupiedBoardWZero(player& player) {
	for (int i = 0; i < BOARD_SIZE - 1; i++) {
		for (int j = 0; j < BOARD_SIZE - 1; j++) {
			player.occupiedBoard[i][j] = ZERO;
		}
	}
}

void removeShip(player& player, ship& smallShip, ship& mediumShip, ship& largeShip, ship& cruiser, char& shipSelect) {
	char removerLetter;
	int removerNumber;
	int countDeletions = 1;

	while (true) {
		std::cout << "Enter coordinates for ship removal in the format LN, where L stands for\nletter and N stands for number. L can be {A.to.J} and N can be {1.to.10}." << std::endl;
		std::cin.ignore();
		std::cin >> removerLetter;
		std::cin >> removerNumber;

		if (player.board[removerNumber-1][interpretLetterAsArrayIndex(removerLetter)] == SHIP) {
			break;
		}
	}

	removerNumber -= 1;
	int iterator;

	player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter)] = SPACE;

	if (removerNumber != 0 && player.board[removerNumber-1][interpretLetterAsArrayIndex(removerLetter)] == SHIP) { //u
		iterator = 1;
		
		while (true) {
			if (player.board[removerNumber - iterator][interpretLetterAsArrayIndex(removerLetter)] == SPACE) {
				break;
			}
			
			player.board[removerNumber - iterator][interpretLetterAsArrayIndex(removerLetter)] = SPACE;
			countDeletions++;

			if (removerNumber - iterator - 1==0) {
				break;
			}

			iterator++;
		}
	}
	if (removerNumber != 10 && player.board[removerNumber +1][interpretLetterAsArrayIndex(removerLetter)] == SHIP) { //d
		iterator = 1;

		while (true) {
			if (player.board[removerNumber + iterator][interpretLetterAsArrayIndex(removerLetter)] == SPACE) {
				break;
			}
			
			player.board[removerNumber + iterator][interpretLetterAsArrayIndex(removerLetter)] = SPACE;
			countDeletions++;

			if ((removerNumber + iterator + 1) == 10) {
				break;
			}

			iterator++;
		}
	}
	if (interpretLetterAsArrayIndex(removerLetter) != 0 && player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter)-1] == SHIP) { //l
		iterator = 1;

		while (true) {
			if (player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter) - iterator] == SPACE) {
				break;
			}
			
			player.board[removerNumber - 1 - iterator][interpretLetterAsArrayIndex(removerLetter)] = SPACE;
			countDeletions++;

			if ((interpretLetterAsArrayIndex(removerLetter) - iterator - 1) == 0) {
				break;
			}

			iterator ++;
		}
	}
	if (removerNumber != 10 && player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter)+1] == SHIP) {
		iterator = 1;

		while (true) {
			if (player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter)+1] == SPACE) {
				break;
			}
			
			player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter)+1] = SPACE;
			countDeletions++;

			if ((interpretLetterAsArrayIndex(removerLetter) + iterator + 1) == 10) {
				break;
			}

			iterator++;
		}
	}

	switch (countDeletions) {
	case SMALL_SHIP_SIZE:
		smallShip.count++;
		shipSelect = 's';
		break;
	case MEDIUM_SHIP_SIZE:
		mediumShip.count++;
		shipSelect = 'm';
		break;
	case LARGE_SHIP_SIZE:
		largeShip.count++;
		shipSelect = 'l';
		break;
	case CRUISER_SIZE:
		cruiser.count++;
		shipSelect = 'c';
		break;
	}
}