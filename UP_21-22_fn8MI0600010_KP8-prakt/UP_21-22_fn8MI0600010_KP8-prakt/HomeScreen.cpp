#include "HomeScreen.h"
#include <iostream>
#include "Animations.h"
#include "Menu.h"
#include "Game.h"

void homeScreen() {
	opening();

	pressAnyKeyToContinue();

	clearConsole();

	menu();
}