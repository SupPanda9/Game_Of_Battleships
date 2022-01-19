#include <iostream>
#include "Game.h"
#include "Animations.h"
#include "Menu.h"
#include "Board.h"

const int MAX_PLAYER_NICKNAME_SIZE = 15;

void game(player &firstPlayer, player& secondPlayer) {
	board(firstPlayer);


}

void enterPlayers(player &firstPlayer, char *player) {

	std::cout << "Enter "<<player<<"'s nickname:" << std::endl;
	std::cout << "Note that it should be between 1 and 15 characters." << std::endl;

	std::cin.ignore();
	std::cin.get(firstPlayer.name, MAX_PLAYER_NICKNAME_SIZE);
}

void players(player &firstPlayer, player &secondPlayer) {
	menuEnding();

	char playerOne[] = { "first player" };
	char playerTwo[] = { "second player" };

	enterPlayers(firstPlayer,playerOne);
	enterPlayers(secondPlayer, playerTwo);
	

	clearConsole();
}

void checkForSameNickname(player &firstPlayer, player &secondPlayer) { //make it work more than once, dc and dcc are not valid! make them
	int i=0;
	bool diffNames = true;
	
	while (true) {
		while (firstPlayer.name[i] != '\0') {
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