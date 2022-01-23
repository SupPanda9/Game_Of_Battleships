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
* <starts and loops the game>
*
*/

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