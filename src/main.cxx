/**
 * @file main.cxx
 * @brief Main entry point for the Zylo application.
 *
 * This file contains the main function for the Zylo application, which initializes the terminal,
 * displays information about the Zylo language, and handles user input.
 */

#include "terminal.hxx"
#include <iostream>

int main()
{
    // Initialize terminal
    if (zylo_terminal::init() != 0)
    {
        std::cerr << "Error initializing terminal." << std::endl;
        return 1;
    }
    // Get user input
    std::string userCommand = zylo_terminal::input(">>> ");
    std::cout << "You entered: " << userCommand << std::endl;

    return 0;
}
