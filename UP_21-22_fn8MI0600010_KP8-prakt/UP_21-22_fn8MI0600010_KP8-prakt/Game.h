#pragma once

struct player {
	char* name = new char[15];
};

void game();

void players(player&, player&);

void enterPlayers(player &, char *);

void checkForSameNickname(player &, player &);

void nameVerification(player&, player&);