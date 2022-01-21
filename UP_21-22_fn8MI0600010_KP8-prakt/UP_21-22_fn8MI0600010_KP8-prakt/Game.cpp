#include <iostream>
#include "Game.h"
#include "Animations.h"
#include "Menu.h"
#include "Board.h"

void game(player &firstPlayer, player& secondPlayer) {
	menuEnding();

	std::cout << "Use u to navigate up and d to navigate down through the options. \nPress c/C to choose. Don't forget to press enter after every command." << std::endl;
	std::cout << std::endl;
	std::cout << "> MAKE YOUR CONFIGURATION NOW <" << std::endl;
	std::cout << std::endl;
	std::cout << "  USE A PREMADE CONFIGURATION" << std::endl;
	std::cout << std::endl;

	startGameMenuOption(firstPlayer);
	startGameSubmenu(firstPlayer);
	
	menuEnding();

	std::cout << "Use u to navigate up and d to navigate down through the options. \nPress c/C to choose. Don't forget to press enter after every command." << std::endl;
	std::cout << std::endl;
	std::cout << "> MAKE YOUR CONFIGURATION NOW <" << std::endl;
	std::cout << std::endl;
	std::cout << "  USE A PREMADE CONFIGURATION" << std::endl;
	std::cout << std::endl;

	startGameMenuOption(secondPlayer);
	startGameSubmenu(secondPlayer);

	turns(firstPlayer, secondPlayer);

}

void players(player &firstPlayer, player &secondPlayer) {
	menuEnding();

	char playerOne[] = { "first player" };
	char playerTwo[] = { "second player" };

	enterPlayers(firstPlayer,playerOne);
	enterPlayers(secondPlayer, playerTwo);
	
	clearConsole();
}

void enterPlayers(player& player, char* whichPlayer) {

	std::cout << "Enter " << whichPlayer << "'s nickname:" << std::endl;
	std::cout << "Note that it should be between 1 and 15 characters." << std::endl;

	std::cin.ignore();
	std::cin.get(player.name, MAX_PLAYER_NICKNAME_SIZE);
}

void checkForSameNickname(player &firstPlayer, player &secondPlayer) { //make it work more than once, dc and dcc are not valid! make them (done(maybe X) ))
	int i=0;
	bool diffNames = true;
	
	while (true) {
		while (firstPlayer.name[i] != TERMINATING_ZERO || secondPlayer.name[i]!=TERMINATING_ZERO) {
			if (firstPlayer.name[i] != secondPlayer.name[i]) {
				diffNames = false;
				break;
			}
			i++;
		}
		
		if (!diffNames) {
			break;
		}
		
		if (diffNames) {
			menuEnding();

			std::cout << "Enter different nicknames!" << std::endl;
			wait(SHORT_TIME);

			delete[] firstPlayer.name;  
			delete[] secondPlayer.name;
			
			pressAnyKeyToContinue();
			
			clearConsole();
			
			players(firstPlayer, secondPlayer);

			menuEnding();
		}
	}
}

void nameVerification(player &firstPlayer, player &secondPlayer) {
	menuEnding();
	
	std::cout << "First player's name is " << firstPlayer.name << " and second player's name is " << secondPlayer.name << "!" << std::endl;
	std::cout << "Is this your final choice:" << std::endl;
	std::cout << "Press any key for yes and 'n' for no and enter after that." << std::endl;
	std::cout << std::endl;

	char yesNo;

	std::cin >> yesNo;

	if (yesNo == 'n' || yesNo == 'N') {
		clearConsole();

		delete[] firstPlayer.name;
		delete[] secondPlayer.name;
		
		startPreparation(firstPlayer,secondPlayer);
	}
}

void turns(player& firstPlayer, player& secondPlayer) {
	char option;
	bool firstPlayerTurn = true;

	point firstPoint; 
	point secondPoint;

	bool firstTurn1=true, firstTurn2=false;

	while (true) {
		if (firstPlayerTurn) {
			std::cout << "It is " << firstPlayer.name << "'s turn!" << std::endl;
			wait(SHORT_TIME);
			
			while (true) {
				turnOption(firstPlayer, option);
				
				if (option == '1') {
					menuEnding();

					std::cout << "Your ships = S, your destroyed ships = X." << std::endl;
					boardVisualiser(firstPlayer, 'b');

					std::cout << "Ships of " << secondPlayer.name << " you have found = F, places where you've guessed unsuccessfully = U." << std::endl;
					boardVisualiser(firstPlayer, 'h');
				}
				else if (option == '2') {
					guessPosition(firstPlayer, secondPlayer, firstPoint, firstPlayerTurn, firstTurn1);
					firstTurn1 = false;
					break;
				}
			}
		}
		else {
			std::cout << "It is " << secondPlayer.name << "'s turn!" << std::endl;
			wait(SHORT_TIME);

			while (true) {
				turnOption(secondPlayer, option);
				
				if (option == '1') {
					menuEnding();

					std::cout << "Your ships = S, your destroyed ships = X." << std::endl;
					boardVisualiser(secondPlayer, 'b');

					std::cout << "Ships of " << firstPlayer.name << " you have found = F, places where you've guessed unsuccessfully = U." << std::endl;
					boardVisualiser(firstPlayer, 'h');
				}
				else if (option == '2') {
					guessPosition(secondPlayer, firstPlayer, secondPoint, firstPlayerTurn, firstTurn2);
					firstTurn2 = false;
					break;
				}
			}
		}
	}
}

void turnOption(player& player, char& option) {
	while (true) {
		menuEnding();

		std::cout << "It is " << player.name << "'s turn!" << std::endl;

		std::cout << "What do you want to do:" << std::endl;
		
		std::cout << "1. See your boards!" << std::endl;
		std::cout << "2. Guess." << std::endl;

		std::cin.ignore();
		std::cin >> option;

		if (option == '1' || option == '2') {
			break;
		}
		else {
			clearConsole();
		}
	}
}

void guessPosition(player& firstPlayer, player& secondPlayer, point& point, bool& firstPlayerTurn, bool firstTurn) {
	char option, direction;

	while (true) {
		std::cout << "Choose how to guess position of ship:" << std::endl;
		std::cout << "1. By entering coordinates." << std::endl;
		
		if (!firstTurn) {
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

	if (option == '1') {
		while (true) {
			std::cout << "Enter coordinates in the format LN, where L stands for letter and\nN stands for number. L can be {A.to.J} and N can be {1.to.10}, to make a guess." << std::endl;
			std::cin.ignore();
			std::cin >> point.letter;
			std::cin >> point.number;

			if (toLowerCase(point.letter) >= SMALL_A && toLowerCase(point.letter) <= SMALL_J && point.number >= 1 && point.number <= 10) {
				break;
			}
			else {
				std::cout << "Invalid input!" << std::endl;
			}
			clearConsole();
		}
	}
	else {
		while (true) {
			std::cout << "Enter direction u, d, l or r, standing for up, down, left and right from your last guess." << std::endl;
			std::cin.ignore();
			std::cin >> direction;

			if (toLowerCase(direction) == DIRECTION_UP || toLowerCase(direction) == DIRECTION_DOWN ||
				toLowerCase(direction) == DIRECTION_RIGHT || toLowerCase(direction) == DIRECTION_LEFT) {
				break;
			}
			else if ((direction == DIRECTION_UP && point.number == 0) ||
				(direction == DIRECTION_DOWN && point.number == 9) ||
				(direction == DIRECTION_RIGHT && interpretLetterAsArrayIndex(point.letter) == 9) ||
				(direction == DIRECTION_LEFT && interpretLetterAsArrayIndex(point.letter) == 0)) {
				std::cout << "Invalid direction." << std::endl;
			}
			else {
				std::cout << "Invalid input!" << std::endl;
			}
			clearConsole();
		}
	}
	
	if (option == '2') {
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

	if (option == '1') {
		point.number -= 1; // making it arrayable 
		toLowerCase(point.letter);
	}

	if (secondPlayer.board[point.number][interpretLetterAsArrayIndex(point.letter)] == SHIP) {
		secondPlayer.board[point.number][interpretLetterAsArrayIndex(point.letter)] = DESTROYED;
		firstPlayer.helpBoard[point.number][interpretLetterAsArrayIndex(point.letter)] = FOUND;

		if (isLastCellOfShip(secondPlayer, point)) {
			std::cout << "You destroyed a whole ship!" << std::endl;
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

		firstPlayerTurn = !firstPlayerTurn;
	}
	clearConsole();
}

bool isLastCellOfShip(player& secondPlayer, point& point) {
	char direction='h';
	
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
	
	if (direction == 'h') {
		while (true) {
			if (interpretLetterAsArrayIndex(point.letter) - iterator < 0) {
				break;
			}
			if (secondPlayer.board[point.number][interpretLetterAsArrayIndex(point.letter)-iterator] == SPACE) {
				break;
			}
			if (secondPlayer.board[point.number][interpretLetterAsArrayIndex(point.letter)-iterator] == SHIP) {
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