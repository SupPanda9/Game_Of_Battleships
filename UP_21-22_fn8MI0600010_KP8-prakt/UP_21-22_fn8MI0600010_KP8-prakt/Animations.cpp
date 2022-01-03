#include "Animations.h"
#include <iostream>
#include <string>

void opening() {
    const int FREE_LINES = 5;
    const int LONG_TIME = 750000000;
    const int SHORT_TIME = 250000000;

    wait(SHORT_TIME);

    spacing(FREE_LINES);

    heading();
    
    spacing(FREE_LINES);

    wait(LONG_TIME);

}

void clearConsole() {
#ifdef _WIN32
    system("cls");

#elif __linux__
    system("clear");

#else
    for (int i = 0; i <= 1000; i++) {
        cout << std::endl;
    }

#endif
}

void wait(int time) {
    for (int i = 0; i <= time; i++) {
    }
}

void pressAnyKeyToContinue() {
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

void spacing(int freeLines) {
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
    std::cout << "                                  MENU     " << std::endl;
    std::cout << "======================================================================" << std::endl;
    std::cout << "Use u to navigate up and d to navigate down through the options. Press c/C to choose." << std::endl;
    std::cout << std::endl;
}