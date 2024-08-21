/**
 * @file terminal.cxx
 * @brief Implements terminal utilities for the Zylo programming language.
 *
 * This file contains the implementation of functions declared in `terminal.hxx`. It provides
 * functionality for initializing the terminal, displaying information, and handling user input.
 */

#include "terminal.hxx"
#include "color.hxx"
#include "constants.hxx"
#include <iostream>

int zylo_terminal::init()
{
    SetConsoleTitleA(DEFAULT_LANGUAGE_NAME);
    system("cls");
    info();
    return 0;
}

int zylo_terminal::info()
{
    // Display Zylo information
    SetConsoleColor(GREEN);
    std::cout << DEFAULT_LANGUAGE_NAME << " " << ZYLO_VERSION << std::endl;

    SetConsoleColor(WHITE);
    std::cout << "Type 'exit' to quit the interpreter." << std::endl;

    SetConsoleColor(WHITE);
    std::cout << "Type 'help' for a list of available commands." << std::endl;

    // Reset color to default (usually light gray)
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    return 0;
}

std::string zylo_terminal::input(const std::string &prompt)
{
    std::cout << prompt;
    SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    std::string input;
    std::getline(std::cin, input);

    return input;
}