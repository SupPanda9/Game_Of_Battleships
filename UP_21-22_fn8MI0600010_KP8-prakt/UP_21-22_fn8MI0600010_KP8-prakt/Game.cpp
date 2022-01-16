#include <iostream>
#include "Game.h"
#include "Animations.h"

const int MAX_PLAYER_NICKNAME_SIZE = 15;

void game() {
	player firstPlayer;
	player secondPlayer;

	players(firstPlayer,secondPlayer);

	checkForSameNickname(firstPlayer,secondPlayer);
}

void enterPlayers(player &firstPlayer, char *player) {
	std::cout << "Enter the "<<player<<"'s nickname:" << std::endl;
	std::cout << "Note that it should be between 1 and 15 characters." << std::endl;

	std::cin.ignore();
	std::cin.get(firstPlayer.name, MAX_PLAYER_NICKNAME_SIZE);
}

void players(player &firstPlayer, player &secondPlayer) {
	
	char playerOne[] = { "first player" };
	char playerTwo[] = { "second player" };

	enterPlayers(firstPlayer,playerOne);
	enterPlayers(secondPlayer, playerTwo);

	clearConsole();
}

void checkForSameNickname(player &firstPlayer, player &secondPlayer) {
	int i=0;
	bool diffNames = true;

	while (firstPlayer.name[i] != '\0') {
		if (firstPlayer.name[i] != secondPlayer.name[i]) {
			diffNames = false;
			break;
		}
		i++;
	}

	if (diffNames) {
		std::cout << "Enter different nicknames!" << std::endl;
		wait(SHORT_TIME);

		delete[] firstPlayer.name;
		delete[] secondPlayer.name;

		players(firstPlayer,secondPlayer);
	}
}