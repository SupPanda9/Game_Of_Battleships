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
* <prints some fixed combinations of symbols and interacts with the look of the console>
*
*/

#include "Animations.h"
#include <iostream>
#include <string>

void opening() {
    wait(SHORT_TIME);

    spacing(FREE_LINES);

    heading();
    
    spacing(FREE_LINES);

    wait(LONG_TIME);
}

void clearConsole() { //I called the system, but made sure that it will work both on windows and linux
#ifdef _WIN32
    system("cls");

#elif __linux__
    system("clear");

#else
    for (int i = 0; i <= 200; i++) {
        cout << std::endl;
    }

#endif
}

void wait(int time) { //runs a cycle that will need some time to process
    for (int i = 0; i <= time; i++) {
    }
}

void pressAnyKeyToContinue() { //I called the system, but made sure that it will work both on windows and linux
#ifdef _WIN32
    system("pause");

#elif __linux__
    system("read");

#else
    cout << "Press any key to continue . . .";
    string n;
    cin >> n;

#endif
}

void spacing(int freeLines) { //leaves n-new lines, depending on freelines' value
    for (int i = 0; i < freeLines; i++) {
        std::cout << std::endl;
    }
}

void heading() {
    std::cout << "           ____          _    _    _                _      _              " << std::endl;
    std::cout << "          |  _ \\   __ _ | |  | |  | |   __    ___  | |__  (_) _ __   ___    " << std::endl;
    std::cout << "          |  _ \\  /  ` || __|| __|| |  / _ \\ / __| | '_ \\ | || '_ \\ / __| " << std::endl;
    std::cout << "          | |_) || (_| || |_ | |_ | |  | __/ \\__ \\ | | | || || |_) |\\__ \\ " << std::endl;
    std::cout << "          | ____/ \\__,_| \\__| \\__|| _| \\___| |___/ |_| |_||_|| .__/ |___/ " << std::endl;
    std::cout << "                                                             |_|          " << std::endl;
}

void menuHeading() {
    std::cout << "======================================================================" << std::endl;
    std::cout << "                                 MENU     " << std::endl;
    std::cout << "======================================================================" << std::endl;
    std::cout << "Use 'u' to navigate up and 'd' to navigate down through the options. \nPress 'c' or 'C' to choose. Don't forget to press enter after every command." << std::endl;
    std::cout << std::endl;
}

void menuEnding() {
    line();
    line();
    std::cout << std::endl;
}

void line() {
    std::cout << "======================================================================" << std::endl;
}

void horizontalLine() {
    std::cout << "---------------------------------------------" << std::endl;
}