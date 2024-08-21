/**
 * @file terminal.hxx
 * @brief Declares utilities for managing terminal operations in the Zylo programming language.
 *
 * This file declares functions and utilities related to terminal operations, such as initializing
 * the terminal, displaying information, and handling user input.
 */

#ifndef ZYLO_TERMINAL_HXX
#define ZYLO_TERMINAL_HXX

#include <string>

/**
 * @namespace zylo_terminal
 * @brief Contains terminal utilities for the Zylo programming language.
 *
 * This namespace includes functions and utilities for managing terminal operations in the Zylo
 * programming language. It provides functionality for initializing the terminal, displaying
 * information about the language, and handling user input.
 *
 * @see zylo
 */
namespace zylo_terminal
{

    /**
     * @brief Initializes the terminal for use with the Zylo interpreter.
     *
     * This function sets up the terminal environment, configuring any necessary settings to prepare
     * the terminal for interaction with the Zylo programming language.
     *
     * @return Returns 0 on successful initialization.
     */
    int init();

    /**
     * @brief Displays information about the Zylo programming language in the terminal.
     *
     * This function shows constants like version and name with predefined colors for better readability.
     *
     * @return Returns 0 on successful display of information.
     */
    int info();

    /**
     * @brief Reads user input from the terminal.
     *
     * This function prompts the user for input and reads the response from the terminal.
     *
     * @param prompt The message to display to the user.
     * @return The user input as a string.
     */
    std::string input(const std::string &prompt);

} // namespace zylo

#endif // ZYLO_TERMINAL_HXX
