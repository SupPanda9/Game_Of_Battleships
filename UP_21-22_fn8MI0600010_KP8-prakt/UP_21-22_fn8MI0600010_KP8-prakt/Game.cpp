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
* <enters two users and runs the game turn by turn until one of them becomes a winner>
*
*/

#include <iostream>
#include "Game.h"
#include "Animations.h"
#include "Menu.h"
#include "Board.h"
#include <fstream>
#include "HomeScreen.h"
#include <string>


void game(player &firstPlayer, player& secondPlayer) {
	int countDestroyedShips1 = 0;
	int countDestroyedShips2 = 0;

	std::fstream scoreBoard;

	menuEnding();

	std::cout << firstPlayer.name << " it's your turn! Pick:" << std::endl;

	spacing(1);

	std::cout << "Use 'u' to navigate up and 'd' to navigate down through the options. \nPress 'c' or 'C' to choose. Don't forget to press enter after every\ncommand." << std::endl;
	std::cout << std::endl;
	std::cout << "> MAKE YOUR CONFIGURATION NOW <" << std::endl;
	std::cout << std::endl;
	std::cout << "  USE A PREMADE CONFIGURATION" << std::endl;
	std::cout << std::endl;
	
	menuEnding();

	startGameMenuOption(firstPlayer); //asks the first player how to enter ships 
	startGameSubmenu(firstPlayer);
	
	menuEnding();

	std::cout << secondPlayer.name << " it's your turn! Pick:" << std::endl;

	spacing(1);

	std::cout << "Use 'u' to navigate up and 'd' to navigate down through the options. \nPress 'c' or 'C' to choose. Don't forget to press enter after every\ncommand." << std::endl;
	std::cout << std::endl;
	std::cout << "> MAKE YOUR CONFIGURATION NOW <" << std::endl;
	std::cout << std::endl;
	std::cout << "  USE A PREMADE CONFIGURATION" << std::endl;
	std::cout << std::endl;

	menuEnding();

	startGameMenuOption(secondPlayer); //how to enter ships second player
	startGameSubmenu(secondPlayer);

	fillBoard(firstPlayer, 'h'); //fills board with empty spaces (for design reasons)
	fillBoard(secondPlayer, 'h');

	turns(firstPlayer, secondPlayer, countDestroyedShips1, countDestroyedShips2); //starts the game
	
	if (countDestroyedShips1 == 10) { //means that the first player has found all of the second players' ships
		std::cout << firstPlayer.name << " WON!" << std::endl;
		
		scoreBoard.open("scoreBoard.txt", std::ios::app); //gives the information to the scoreboard
		if (scoreBoard.is_open()) {
			scoreBoard << firstPlayer.name << " WON against " << secondPlayer.name << std::endl;
			scoreBoard.close();
		}
		delete[] firstPlayer.name; //frees the memory of the dynamic arrays
		delete[] secondPlayer.name;
	}
	else if (countDestroyedShips2 == 10) {
		std::cout << secondPlayer.name << " WON!" << std::endl;
		
		scoreBoard.open("scoreBoard.txt", std::ios::app);

		if (scoreBoard.is_open()) {
			scoreBoard << secondPlayer.name << " WON against " << firstPlayer.name << std::endl;
			scoreBoard.close();
		}
		
		delete[] firstPlayer.name;
		delete[] secondPlayer.name;
	}
	while (true) {
		std::cout << "Would like to play again? Press y+enter for yes and n+enter for no." << std::endl;

		std::string yesNo;

		std::cin >> yesNo;

		if (toLowerCase(yesNo[0]) == 'y') { //starts the game again
			homeScreen();
		}
		else if (toLowerCase(yesNo[0]) == 'n') { //ends the game
			pressAnyKeyToContinue();
			break;
		}
		else {
			std::cout << "Enter again!" << std::endl; //if we didn't enter y or n
		}
	}
}

void players(player &firstPlayer, player &secondPlayer) {
	char playerOne[] = { "first player" };
	char playerTwo[] = { "second player" };

	enterPlayers(firstPlayer, playerOne);
	enterPlayers(secondPlayer, playerTwo);
	
	clearConsole();
}

void enterPlayers(player& player, char* whichPlayer) {
	std::string name;

	menuEnding();
	
	std::cout << "Enter " << whichPlayer << "'s nickname:" << std::endl;
	std::cout << "Note that it should be between 1 and 15 characters." << std::endl;
	
	spacing(1);
	
	menuEnding();
	
	std::cin >> name;
	
	int iterator = 0;

	while (name[iterator] != TERMINATING_ZERO && iterator != MAX_PLAYER_NICKNAME_SIZE) { //enters name for the player
		player.name[iterator] = name[iterator];
		iterator++;
	}
	player.name[iterator] = TERMINATING_ZERO;
}

void checkForSameNickname(player &firstPlayer, player &secondPlayer) {
	int i = 0;
	bool diffNames = true;
	
	while (true) {
		while (firstPlayer.name[i] != TERMINATING_ZERO || secondPlayer.name[i]!=TERMINATING_ZERO) { 
			if (firstPlayer.name[i] != secondPlayer.name[i]) { //if we find one letter that is not the same, then the names are not the same
				diffNames = false;
				break;
			}
			i++;
		}
		
		if (!diffNames) { //breaks if the names are different 
			break;
		}
		
		if (diffNames) { //asks to enter different names
			menuEnding();

			std::cout << "Enter different nicknames!" << std::endl;

			spacing(1);

			menuEnding();

			wait(SHORT_TIME);
			
			pressAnyKeyToContinue();
			
			clearConsole();
			
			startPreparation(firstPlayer, secondPlayer);
		}
	}
}

void nameVerification(player &firstPlayer, player &secondPlayer) {
	menuEnding();
	
	std::cout << "First player's name is " << firstPlayer.name << " and second player's name is " << secondPlayer.name << "!" << std::endl;
	std::cout << "Is this your final choice:" << std::endl;
	std::cout << "Press any key for yes or 'n' for no and enter after that." << std::endl;
	std::cout << std::endl;
	
	menuEnding();

	std::string yesNo;
	std::cin >> yesNo;

	if (toLowerCase(yesNo[0]) == 'n') { //if n is given, we want to enter names again
		clearConsole();
		
		startPreparation(firstPlayer, secondPlayer); //restarting the process of entering names
		return;
	}
}

void turns(player& firstPlayer, player& secondPlayer, int& countDestroyedShips1, int& countDestroyedShips2) {
	char option;
	bool firstPlayerTurn = true;

	point firstPoint; 
	point secondPoint;

	bool firstTurn1=true, firstTurn2=true;

	while (true) {
		if (countDestroyedShips1 == 10 || countDestroyedShips2 == 10) { //if someone has destroyed all ships of the other player, the game ends
			break;
		}
		if (firstPlayerTurn) {
			std::cout << "It is " << firstPlayer.name << "'s turn!" << std::endl;
			wait(SHORT_TIME);
			
			while (true) {
				turnOption(firstPlayer, option);
				
				if (option == '1') {
					menuEnding();

					std::cout << "Your ships = S, your destroyed ships = X." << std::endl; //shows the boards of the first player
					boardVisualiser(firstPlayer, 'b');
					
					pressAnyKeyToContinue();

					std::cout << "Ships of " << secondPlayer.name << " you have found = F, places where you've guessed unsuccessfully = U." << std::endl;
					boardVisualiser(firstPlayer, 'h');

					pressAnyKeyToContinue();
					clearConsole();
				}
				else if (option == '2') {
					guessPosition(firstPlayer, secondPlayer, firstPoint, firstPlayerTurn, firstTurn1, countDestroyedShips1); //proceeds to guessing
					
					firstTurn1 = false;
					
					break;
				}
			}
		}
		else { //the same but for the second player
			std::cout << "It is " << secondPlayer.name << "'s turn!" << std::endl;
			wait(SHORT_TIME);

			while (true) {
				turnOption(secondPlayer, option);
				
				if (option == '1') {
					menuEnding();

					std::cout << "Your ships = S, your destroyed ships = X." << std::endl;
					boardVisualiser(secondPlayer, 'b');

					pressAnyKeyToContinue();

					std::cout << "Ships of " << firstPlayer.name << " you have found = F, places where you've guessed unsuccessfully = U." << std::endl;
					boardVisualiser(secondPlayer, 'h');

					pressAnyKeyToContinue();
					clearConsole();
				}
				else if (option == '2') {
					guessPosition(secondPlayer, firstPlayer, secondPoint, firstPlayerTurn, firstTurn2, countDestroyedShips2);

					firstTurn2 = false;

					break;
				}
			}
		}
	}
}

void turnOption(player& player, char& option) { //asks the player in turn what he/she wants to do
	while (true) {
		menuEnding();

		std::cout << "It is " << player.name << "'s turn!" << std::endl;

		std::cout << "What do you want to do:" << std::endl;
		
		std::cout << "1. See your boards!" << std::endl;
		std::cout << "2. Guess." << std::endl;

		std::cin >> option;

		if (option == '1' || option == '2') {
			break;
		}
		else {
			clearConsole();
		}
	}
}

void guessPosition(player& firstPlayer, player& secondPlayer, point& point, bool& firstPlayerTurn, bool firstTurn, int& countDestroyedShips) {
	char option, direction;
	
	//how to guess position
	while (true) {
		std::cout << "Choose how to guess position of ship:" << std::endl;
		std::cout << "1. By entering coordinates." << std::endl;
		
		if (!firstTurn) { // only available after the first turn
			std::cout << "2. By setting direction from last guess." << std::endl;
		}
		
		std::cin.ignore();
		std::cin >> option;
		
		if (option == '1' || (option == '2' && !firstTurn)) {
			break;
		}
		else {
			std::cout << "Invalid input!" << std::endl;
		}
	}
	
	if (option == '1') { //first option guessing
		while (true) {
			std::cout << "Enter coordinates in the format LN, where L stands for letter and\nN stands for number. L can be {A.to.J} and N can be {1.to.10}, to make a guess." << std::endl;
			
			std::string coordinates;
			std::cin >> coordinates;

			point.letter = coordinates[0];

			if (coordinates[1] >= '1' && coordinates[1] <= '9') { //making the char to number
				switch (coordinates[1]) {
				case '1':
					if (coordinates[2] == '0') {
						point.number = 10;
					}
					else {
						point.number = 1;
					}
					break;
				case '2':
					point.number = 2;
					break;
				case '3':
					point.number = 3;
					break;
				case '4':
					point.number = 4;
					break;
				case '5':
					point.number = 5;
					break;
				case '6':
					point.number = 6;
					break;
				case '7':
					point.number = 7;
					break;
				case '8':
					point.number = 8;
					break;
				case '9':
					point.number = 9;
					break;
				default:
					break;
				}

				if (toLowerCase(point.letter) >= SMALL_A && toLowerCase(point.letter) <= SMALL_J && point.number >= 1 && point.number <= 10) { //checks wheteher they are in the given range
					if (firstPlayer.helpBoard[point.number - 1][interpretLetterAsArrayIndex(point.letter)] == UNSUCCESSFUL_GUESS ||
						firstPlayer.helpBoard[point.number - 1][interpretLetterAsArrayIndex(point.letter)] == FOUND) {
						std::cout << "You've already guessed on this position!" << std::endl;

						pressAnyKeyToContinue();
					}
					else {
						break;
					}
				}
				else {
					std::cout << "Invalid input!" << std::endl;
					
					pressAnyKeyToContinue();
				}
				clearConsole();
			}
		}
	}
	else {
		while (true) {
			std::cout << "Enter direction u, d, l or r, standing for up, down, left and right from your last guess. Press b to go back.(" << point.letter << "," << point.number+1 <<")"<< std::endl;
			
			std::cin.ignore();
			std::cin >> direction;
			
			if (direction == 'b') {
				guessPosition(firstPlayer, secondPlayer, point, firstPlayerTurn, firstTurn, countDestroyedShips); //returns to the choosing of guessing option
				return;
			}
			if ((direction == DIRECTION_UP && point.number == 0) ||
				(direction == DIRECTION_DOWN && point.number == 9) ||
				(direction == DIRECTION_RIGHT && interpretLetterAsArrayIndex(point.letter) == 9) ||
				(direction == DIRECTION_LEFT && interpretLetterAsArrayIndex(point.letter) == 0)) { //checks if the direction is possible (it is not going outside of the board)
				std::cout << "Invalid direction." << std::endl;
				
				pressAnyKeyToContinue();
			}
			else if ((direction==DIRECTION_UP && (firstPlayer.helpBoard[point.number - 1][interpretLetterAsArrayIndex(point.letter)] == UNSUCCESSFUL_GUESS ||
				firstPlayer.helpBoard[point.number - 1][interpretLetterAsArrayIndex(point.letter)] == FOUND)) ||
				(direction == DIRECTION_DOWN && (firstPlayer.helpBoard[point.number + 1][interpretLetterAsArrayIndex(point.letter)] == UNSUCCESSFUL_GUESS ||
					firstPlayer.helpBoard[point.number + 1][interpretLetterAsArrayIndex(point.letter)] == FOUND)) || 
				(direction == DIRECTION_LEFT && (firstPlayer.helpBoard[point.number][interpretLetterAsArrayIndex(point.letter)-1] == UNSUCCESSFUL_GUESS ||
						firstPlayer.helpBoard[point.number][interpretLetterAsArrayIndex(point.letter)-1] == FOUND)) ||
				(direction == DIRECTION_RIGHT && (firstPlayer.helpBoard[point.number][interpretLetterAsArrayIndex(point.letter)+1] == UNSUCCESSFUL_GUESS ||
					firstPlayer.helpBoard[point.number][interpretLetterAsArrayIndex(point.letter)+1] == FOUND))) { //checks if we already tried to guess on this position
				std::cout << "You've already guessed on this position!" << std::endl;
			
				pressAnyKeyToContinue();
			}
			else if (toLowerCase(direction) == DIRECTION_UP || toLowerCase(direction) == DIRECTION_DOWN ||
				toLowerCase(direction) == DIRECTION_RIGHT || toLowerCase(direction) == DIRECTION_LEFT) { //checks for valid data in the range
				break;
			}
			else {
				std::cout << "Invalid input!" << std::endl;
				
				pressAnyKeyToContinue();
			}
			clearConsole();
		}
	}
	
	if (option == '2') { //changes the coordinates for the second variant
		switch (direction) {
		case DIRECTION_UP:
			point.number --;
			break;
		case DIRECTION_DOWN:
			point.number ++;
			break;
		case DIRECTION_RIGHT:
			toLowerCase(point.letter);
			point.letter++;
			break;
		case DIRECTION_LEFT:
			toLowerCase(point.letter);
			point.letter--;
			break;
		}
	}

	if (option == '1') { //if it's the first variant, makes number from 0 to 9
		point.number -= 1; // making it arrayable 
		toLowerCase(point.letter);
	}

	if (secondPlayer.board[point.number][interpretLetterAsArrayIndex(point.letter)] == SHIP) { //checks if there is a ship on the given position
		secondPlayer.board[point.number][interpretLetterAsArrayIndex(point.letter)] = DESTROYED;
		firstPlayer.helpBoard[point.number][interpretLetterAsArrayIndex(point.letter)] = FOUND;

		if (isLastCellOfShip(secondPlayer, point)) { //checks if we destroyed the last remaining cell of the ship
			std::cout << "You destroyed a whole ship!" << std::endl;
			
			countDestroyedShips++;
		}
		else {
			std::cout << "You found a ship!" << std::endl;
		}
		std::cout << "It's your turn again!" << std::endl;

		pressAnyKeyToContinue();
	}
	else {
		std::cout << "Your guess was unsuccessful!" << std::endl;

		firstPlayer.helpBoard[point.number][interpretLetterAsArrayIndex(point.letter)] = UNSUCCESSFUL_GUESS;

		pressAnyKeyToContinue();

		firstPlayerTurn = !firstPlayerTurn; //gives the turn to the other player
	}
	clearConsole();
}

bool isLastCellOfShip(player& secondPlayer, point& point) {
	char direction = 'h';
	
	if (point.number - 1 >= 0 && point.number + 1 <= 9) { //check if ship is horizontally or vertically placed
		if (secondPlayer.board[point.number - 1][interpretLetterAsArrayIndex(point.letter)] == SPACE &&
			secondPlayer.board[point.number + 1][interpretLetterAsArrayIndex(point.letter)] == SPACE) {
			direction = 'h';
		}
		else {
			direction = 'v';
		}
	}
	else if (point.number == 9) {
		if (secondPlayer.board[point.number - 1][interpretLetterAsArrayIndex(point.letter)] == SPACE) {
			direction = 'h';
		}
		else {
			direction = 'v';
		}
	}
	else if (point.number == 0) {
		if (secondPlayer.board[point.number + 1][interpretLetterAsArrayIndex(point.letter)] == SPACE) {
			direction = 'h';
		}
		else {
			direction = 'v';
		}
	}

	int iterator = 1;

	if (direction == 'h') { //checks each case for horizontal placing by fnding the first cell of the ship and checking onwards
		while (true) {
			if (interpretLetterAsArrayIndex(point.letter) - iterator < 0) {
				break;
			}
			if (secondPlayer.board[point.number][interpretLetterAsArrayIndex(point.letter) - iterator] == SPACE) {
				break;
			}
			if (secondPlayer.board[point.number][interpretLetterAsArrayIndex(point.letter) - iterator] == SHIP) {
				return false;
			}
			iterator++;
		}
		iterator = 1;

		while (true) {
			if (interpretLetterAsArrayIndex(point.letter) + iterator > 9) {
				break;
			}
			if (secondPlayer.board[point.number][interpretLetterAsArrayIndex(point.letter) + iterator] == SPACE) {
				break;
			}
			if (secondPlayer.board[point.number][interpretLetterAsArrayIndex(point.letter) + iterator] == SHIP) {
				return false;
			}
			iterator++;
		}
		return true;
	}
	else {
		while (true) {
			if (point.number - iterator < 0) {
				break;
			}
			if( secondPlayer.board[point.number - iterator][interpretLetterAsArrayIndex(point.letter)] == SPACE) {
				break;
			}
			if (secondPlayer.board[point.number - iterator][interpretLetterAsArrayIndex(point.letter)] == SHIP) {
				return false;
			}
			iterator++;
		}
		iterator = 1;
		while (true) {
			if (point.number + iterator > 9) {
				break;
			}
			if(secondPlayer.board[point.number + iterator][interpretLetterAsArrayIndex(point.letter)] == SPACE) {
				break;
			}
			if (secondPlayer.board[point.number + iterator][interpretLetterAsArrayIndex(point.letter)] == SHIP) {
				return false;
			}
			iterator++;
		}
		return true;
	}
}