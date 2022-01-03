#include "HomeScreen.h"
#include <iostream>
#include "Animations.h"
#include "Menu.h"

void homeScreen() {
	opening();

	pressAnyKeyToContinue();

	clearConsole();

	menu();
}