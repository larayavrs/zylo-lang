/**
 * @file constants.hxx
 * @brief Defines global constants used throughout the Zylo programming language.
 *
 * This file contains the declaration of various constants that are used globally within the Zylo
 * programming language. These constants provide a centralized location for commonly used values,
 * ensuring consistency and maintainability across the entire codebase. By defining these constants
 * in a single file, the Zylo project can avoid magic numbers and hardcoded values, making the
 * code easier to understand, modify, and debug.
 */

#ifndef ZYLO_CONSTANTS_HXX // ZYLO_CONSTANTS_HXX

#define ZYLO_CONSTANTS_HXX

#include <cstddef>

// Example Constants

/**
 * @brief The default size for the memory buffer used in the Zylo virtual machine.
 *
 * This constant specifies the default size (in bytes) of the memory buffer that the
 * Zylo virtual machine allocates for storing data during execution.
 */
constexpr size_t DEFAULT_MEMORY_BUFFER_SIZE = 1024 * 1024; // 1 MB // TODO: Update value

/**
 * @brief The version number of the Zylo programming language.
 *
 * This constant holds the current version number of the Zylo language, which can be
 * used for version checks, displaying version information, and ensuring compatibility
 * with different versions of Zylo code and tools.
 */
constexpr const char *ZYLO_VERSION = "1.0.0";

/**
 * @brief The default programming language name
 *
 * This constant holds the default name of the programming language.
 */
constexpr const char *DEFAULT_LANGUAGE_NAME = "Zylo";

#endif // ZYLO_CONSTANTS_HXX