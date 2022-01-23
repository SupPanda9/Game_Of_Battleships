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
* <creates the boards with ships, checks their validity and prints them>
*
*/

#include <iostream>
#include "Animations.h"
#include "Game.h"
#include "Menu.h"
#include "Board.h"
#include <fstream>
#include <string>
#include <vector>

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

	fillBoard(player, 'b');

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
			menuEnding();

			std::cout << "Enter your ships " << player.name << ":" << std::endl;

			spacing(1);

			std::cout << "What do you want to do:" << std::endl;

			spacing(1);

			if (!tenShipsAvailable) {
				std::cout << "1. Place a new ship." << std::endl;
			}
			if (tenShipsAvailable) {
				std::cout << "1. Ready!" << std::endl;
			}
			std::cout << "2. Edit the position of an already placed ship." << std::endl;
			std::cout << "3. See your board." << std::endl;

			spacing(1);

			menuEnding();

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
			clearConsole();

			std::cout << "Your final board is:" << std::endl;
			
			spacing(1);

			boardVisualiser(player, 'b');
			pressAnyKeyToContinue();
			clearConsole();

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
			
			menuEnding();

			spacing(1);

			boardVisualiser(player, 'b');

			spacing(1);

			menuEnding();

			pressAnyKeyToContinue();
			clearConsole();
		}
	}
}

void fillBoard(player& player, char which) {
	for (int i = 0; i < BOARD_SIZE - 1; i++) {
		for (int j = 0; j < BOARD_SIZE - 1; j++) {
			if (which == 'b') {
				player.board[i][j] = SPACE;
			}
			else if (which == 'h') {
				player.helpBoard[i][j] = SPACE;
			}
		}
	}
}

void boardVisualiser(player& player, char whichBoard) {
	std::cout << "    ";

	for (int i = 0; i < BOARD_SIZE - 1; i++) { //printing the A,B,C... on top of the board
		std::cout << " " << char(CAPITAL_A + i) << " |";
	}

	std::cout << std::endl;
	horizontalLine();

	for (int i = 0; i < BOARD_SIZE - 1; i++) {
		if (i != BOARD_SIZE - 2) {
			std::cout << " " << i + 1 << " |"; //printing the numbers in the first column of the borad
		}
		else {
			std::cout << i + 1 << " |";
		}
		for (int j = 0; j < BOARD_SIZE - 1; j++) {
			if (whichBoard == 'b') {
				std::cout << " " << player.board[i][j] << " |"; //printing the board
			}
			if (whichBoard == 'h') {
				std::cout << " " << player.helpBoard[i][j] << " |";
			}
		}
		std::cout << std::endl;
		
		horizontalLine();
	}
}

void placeShips(player& player, ship& smallShip, ship& mediumShip, ship& largeShip, ship& cruiser, placer& shipPlacer, char shipSelect) {
	clearConsole();

	if (shipSelect == ZERO) {
		while (true) {
			while (true) {
				menuEnding();

				std::cout << "Select a ship - s=small ship, m=medium ship, l=large ship, c=cruiser" << std::endl;

				spacing(1);

				menuEnding();

				std::string select;
				std::cin >> select;

				shipSelect = select[0];

				if (toLowerCase(shipSelect) == 's' || toLowerCase(shipSelect) == 'm' || toLowerCase(shipSelect) == 'l' || toLowerCase(shipSelect) == 'c') {
					clearConsole();
					break;
				}
				else {
					clearConsole();
				}
			}

			if (toLowerCase(shipSelect) == 's' && smallShip.count == 0) {
				menuEnding();
				
				std::cout << "You don't have any more small ships to place! Please choose another!" << std::endl;
				
				menuEnding();
				
				pressAnyKeyToContinue();
				
				clearConsole();
			}
			else if (toLowerCase(shipSelect) == 'm' && mediumShip.count == 0) {
				menuEnding();
				
				std::cout << "You don't have any more medium ships to place! Please choose another!" << std::endl;
				
				menuEnding();
				
				pressAnyKeyToContinue();
				
				clearConsole();
			}
			else if (toLowerCase(shipSelect) == 'l' && largeShip.count == 0) {
				menuEnding();
				
				std::cout << "You don't have any more large ships to place! Please choose another!" << std::endl;
				
				menuEnding();
				
				pressAnyKeyToContinue();
				
				clearConsole();
			}
			else if (toLowerCase(shipSelect) == 'c' && cruiser.count == 0) {
				menuEnding();
				
				std::cout << "You don't have any more cruisers to place! Please choose another!" << std::endl;
				
				menuEnding();
				
				pressAnyKeyToContinue();
				
				clearConsole();
			}
			else {
				clearConsole();
				
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
	while (true) {
		menuEnding();
		
		std::cout << "Enter coordinates to place a ship in the format LN, where L stands for\nletter and N stands for number. L can be {A.to.J} and N can be {1.to.10}." << std::endl;
		
		spacing(1);
		
		menuEnding();
		
		std::string coordinates;
		std::cin >> coordinates;

		shipPlacer.letter = coordinates[0];

		if (coordinates[1] >= '1' && coordinates[1] <= '9') {
			switch (coordinates[1]) {
			case '1':
				if (coordinates[2] == '0') {
					shipPlacer.number = 10;
				}
				else {
					shipPlacer.number = 1;
				}
				break;
			case '2':
				shipPlacer.number = 2;
				break;
			case '3':
				shipPlacer.number = 3;
				break;
			case '4':
				shipPlacer.number = 4;
				break;
			case '5':
				shipPlacer.number = 5;
				break;
			case '6':
				shipPlacer.number = 6;
				break;
			case '7':
				shipPlacer.number = 7;
				break;
			case '8':
				shipPlacer.number = 8;
				break;
			case '9':
				shipPlacer.number = 9;
				break;
			default:
				break;
			}

			if (toLowerCase(shipPlacer.letter) >= SMALL_A && toLowerCase(shipPlacer.letter) <= SMALL_J && shipPlacer.number >= 1 && shipPlacer.number <= 10) {
				break;
			}
			else {
				menuEnding();
				
				std::cout << "Invalid input!" << std::endl;
				
				spacing(1);
				
				menuEnding();
				
				pressAnyKeyToContinue();
				
				clearConsole();
			}
		}
	}

	while (true) {
		std::cout << "Type r,l,u,d for right, left, up and down to set the direction for the ship." << std::endl;
		
		std::cin.ignore();
		std::cin >> shipPlacer.direction;

		if (toLowerCase(shipPlacer.direction) == DIRECTION_DOWN || toLowerCase(shipPlacer.direction) == DIRECTION_LEFT ||
			toLowerCase(shipPlacer.direction) == DIRECTION_RIGHT || toLowerCase(shipPlacer.direction) == DIRECTION_UP) {
			break;
		}
		else {
			std::cout << "Invalid input!" << std::endl;
		}
	}

	if (validPlace(shipSelect, shipPlacer, player) && isItAnUnoccupiedPosition(player, shipPlacer, iterations)) {
		if (shipPlacer.direction == 'u') {
			for (int i = 0; i < iterations && shipPlacer.number - i - 1 > 0; i++) {
				player.board[shipPlacer.number - i - 1][interpretLetterAsArrayIndex(shipPlacer.letter)] = SHIP;
			}
		}
		else if (shipPlacer.direction == 'd') {
			for (int i = 0; i < iterations && shipPlacer.number + i - 1 < 10; i++) { //exclude warning
				player.board[i + shipPlacer.number - 1][interpretLetterAsArrayIndex(shipPlacer.letter)] = SHIP;
			}
		}
		else if (shipPlacer.direction == 'l') {
			for (int i = 0; i < iterations; i++) {
				player.board[shipPlacer.number - 1][interpretLetterAsArrayIndex(shipPlacer.letter) - i] = SHIP;
			}
		}
		else if (shipPlacer.direction == 'r') {
			for (int i = 0; i < iterations; i++) {
				player.board[shipPlacer.number - 1][i + interpretLetterAsArrayIndex(shipPlacer.letter)] = SHIP;
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
		shipSelect = ZERO;
	}
	else {
		std::cout << "Invalid position!" << std::endl;
		
		pressAnyKeyToContinue();
		
		placeShips(player, smallShip, mediumShip, largeShip, cruiser, shipPlacer, shipSelect);
		return;
	}
	clearConsole();
}

bool validPlace(char shipSelect, placer& shipPlacer, player& player) { //+ another variable which will be for positions next to other ships
	if (shipSelect == 's' && ((shipPlacer.number == 1 && shipPlacer.direction == 'u') || (shipPlacer.number == 10 && shipPlacer.direction == 'd') ||
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
		(interpretLetterAsArrayIndex(shipPlacer.letter) <= 2 && shipPlacer.direction == 'l') ||
		(interpretLetterAsArrayIndex(shipPlacer.letter) >= 7 && shipPlacer.direction == 'r'))) {
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
	return true;
}

void occupyPosition(player& player) {
	for (int i = 0; i < BOARD_SIZE - 1; i++) { //check board for invalid places due to bordering a ship
		for (int j = 0; j < BOARD_SIZE - 1; j++) {
			if (player.board[i][j] == SHIP) {
				player.occupiedBoard[i][j] = OCCUPIED; //O stands for occupied

				if (j != 0) {
					player.occupiedBoard[i][j - 1] = OCCUPIED;
				}
				if (i != 0) {
					player.occupiedBoard[i - 1][j] = OCCUPIED;
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

char toLowerCase(char& symbol) {
	if (symbol >= CAPITAL_A && symbol <= CAPITAL_Z) {
		symbol = symbol + SMALL_TO_CAPITAL_DIFF;
	}
	return symbol;
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
	int removerNumber=0;
	int countDeletions = 1;

	while (true) {
		std::cout << "Enter coordinates for ship removal in the format LN, where L stands for\nletter and N stands for number. L can be {A.to.J} and N can be {1.to.10}." << std::endl;
		
		std::string coordinates;
		std::cin >> coordinates;

		removerLetter = coordinates[0];

		if (coordinates[1] >= '1' && coordinates[1] <= '9') {
			switch (coordinates[1]) {
			case '1':
				if (coordinates[2] == '0') {
					removerNumber = 10;
				}
				else {
					removerNumber = 1;
				}
				break;
			case '2':
				removerNumber = 2;
				break;
			case '3':
				removerNumber = 3;
				break;
			case '4':
				removerNumber = 4;
				break;
			case '5':
				removerNumber = 5;
				break;
			case '6':
				removerNumber = 6;
				break;
			case '7':
				removerNumber = 7;
				break;
			case '8':
				removerNumber = 8;
				break;
			case '9':
				removerNumber = 9;
				break;
			default:
				break;
			}

			if (toLowerCase(removerLetter) < SMALL_A || toLowerCase(removerLetter) > SMALL_J || removerNumber < 1 || removerNumber > 10) {
				std::cout << "Invalid coordinates" << std::endl;

				pressAnyKeyToContinue();
			}
			else if (player.board[removerNumber - 1][interpretLetterAsArrayIndex(removerLetter)] == SHIP) {
				break;
			}
			else {
				std::cout << "There isn't a ship there!" << std::endl;
				
				pressAnyKeyToContinue();
			}
		}
	}

	removerNumber -= 1; //to make it as an index of array

	int iterator;

	player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter)] = SPACE;

	if (removerNumber - 1 >= 0 && player.board[removerNumber - 1][interpretLetterAsArrayIndex(removerLetter)] == SHIP) { //up
		iterator = 1;

		while (true) {
			if (player.board[removerNumber - iterator][interpretLetterAsArrayIndex(removerLetter)] == SPACE) {
				break;
			}

			player.board[removerNumber - iterator][interpretLetterAsArrayIndex(removerLetter)] = SPACE;
			
			countDeletions++;

			if (removerNumber - iterator == 0) {
				break;
			}

			iterator++;
		}
	}
	if (removerNumber + 1 <= 9 && player.board[removerNumber + 1][interpretLetterAsArrayIndex(removerLetter)] == SHIP) { //down
		iterator = 1;

		while (true) {
			if (player.board[removerNumber + iterator][interpretLetterAsArrayIndex(removerLetter)] == SPACE) {
				break;
			}

			player.board[removerNumber + iterator][interpretLetterAsArrayIndex(removerLetter)] = SPACE;
			countDeletions++;

			if ((removerNumber + iterator) == 9) {
				break;
			}

			iterator++;
		}
	}
	if (interpretLetterAsArrayIndex(removerLetter) - 1 >= 0 && player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter) - 1] == SHIP) { //left
		iterator = 1;

		while (true) {
			if (player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter) - iterator] == SPACE) {
				break;
			}

			player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter) - iterator] = SPACE;

			countDeletions++;

			if ((interpretLetterAsArrayIndex(removerLetter) - iterator) == 0) {
				break;
			}

			iterator++;
		}
	}
	if (interpretLetterAsArrayIndex(removerLetter) + 1 <= 9 && player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter) + 1] == SHIP) { //right
		iterator = 1;

		while (true) {
			if (player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter) + iterator] == SPACE) {
				break;
			}

			player.board[removerNumber][interpretLetterAsArrayIndex(removerLetter) + iterator] = SPACE;
			
			countDeletions++;

			if ((interpretLetterAsArrayIndex(removerLetter) + iterator) == 9) {
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

void boardFromFile(player& player) {
	std::fstream file;
	std::string boardInput;

	std::vector<std::string> lines;
	std::string line;

	std::cout << player.name << " enter your file in this format 'name'!" << std::endl;
	getline(std::cin, boardInput);

	boardInput += ".txt";

	file.open(boardInput, std::ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			if (line.size() != BOARD_SIZE - 1) {
				std::cout << "Your file is not in the correct format!" << std::endl;
				
				file.close();
				
				boardFromFile(player);
				return;
			}
			for (int i = 0; i < BOARD_SIZE - 1; i++) {
				if (line[i] != 'S' && line[i] != 'E') {
					std::cout << "Your file doesn't fit the criteria to be consisted of only 'E' and 'S'." << std::endl;
				
					boardFromFile(player);
					return;
				}
			}
			lines.push_back(line);
		}

		for (int i = 0; i < BOARD_SIZE - 1; i++) {
			for (int j = 0; j < BOARD_SIZE - 1; j++) {
				if (lines[i][j] == 'E') {
					player.board[i][j] = SPACE;
				}
				else {
					player.board[i][j] = lines[i][j];
				}
			}
		}

		if (!isFileBoardPossible(player)) {
			std::cout << "Your file doesn't fit the criteria to have the right amount of ships." << std::endl;
			
			file.close();
			
			boardFromFile(player);
			
			return;
		}
		file.close();
	}
	else {
		boardFromFile(player);
		return;
	}
	clearConsole();
	
	boardVisualiser(player, 'b');
	
	pressAnyKeyToContinue();
	
	clearConsole();
}

bool isFileBoardPossible(player& player) {
	int areThereEnoughShips = 0;
	for (int i = 0; i < BOARD_SIZE - 1; i++) {
		for (int j = 0; j < BOARD_SIZE - 1; j++) {
			if (player.board[i][j] == SHIP) {
				areThereEnoughShips++;
			}
		}
	}
	if (areThereEnoughShips == ALL_SHIPS_PLACES) {
		return true;
	}
	else {
		return false;
	}
}