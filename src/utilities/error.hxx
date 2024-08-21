/**
 * @file Error.hxx
 * @brief Defines the Error class for managing error handling within the Zylo programming language.
 *
 * This file contains the declaration of the `Error` class, which is used to represent and handle
 * errors that occur at various stages of the Zylo programming language's processing pipeline,
 * including lexical analysis, parsing, and interpretation.
 * The class includes an enumeration for error location, an error code, and a message describing
 * the error. It also provides a friend function for outputting error details to a stream.
 */

#ifndef ZYLO_ERROR_HXX // ZYLO_ERROR_HXX
#define ZYLO_ERROR_HXX

#include <iostream>

namespace zylo
{

    /**
     * @class Error
     * @brief A class for representing and handling errors within the Zylo programming language.
     *
     * The `Error` class encapsulates error information, including the location within the
     * language processing pipeline where the error occurred, an error code, and a descriptive
     * message. This class provides constructors for initializing error objects and a friend
     * function for outputting the error details, making it easier to manage and display errors
     * encountered during the execution or compilation of Zylo code.
     */
    class Error
    {
    public:
        /**
         * @enum Location
         * @brief Enumerates the different stages of the Zylo language processing pipeline where errors can occur.
         *
         * This enumeration lists the various components of the Zylo language's processing stages where
         * errors might be generated. The possible values are:
         *
         * - `Lexer`: Errors occurring during lexical analysis
         *
         * - `Parser`: Errors occurring during syntax parsing
         *
         * - `Interpreter`: Errors occurring during interpretation or execution of Zylo code
         *
         * - `End`: Marker for the end of the enumeration
         */
        enum class Location
        {
            Lexer,
            Parser,
            Interpreter,
            End
        } location;

        int code;            // The error code representing the specific error type.
        std::string message; // A descriptive message providing details about the error.

        /**
         * @brief Default constructor for the Error class.
         *
         * Initializes an Error object with default values for the location, code, and message.
         */
        Error();

        /**
         * @brief Parameterized constructor for the Error class.
         *
         * Initializes an Error object with specified values for the location, code, and message.
         *
         * @param location The stage of the Zylo language processing pipeline where the error occurred.
         * @param code The error code representing the specific error type.
         * @param message A descriptive message providing details about the error.
         */
        Error(Location location, int code, std::string message);

        /**
         * @brief Outputs the error details to a stream.
         *
         * This friend function allows the contents of an `Error` object to be printed to an
         * output stream, such as `std::cout` or `std::ofstream`, for easier debugging and logging.
         *
         * @param ostream The output stream where the error details will be written.
         * @param error The Error object whose details are to be printed.
         * @return A reference to the output stream.
         */
        friend std::ostream &operator<<(std::ostream &ostream, const Error &error);

    private:
        /**
         * @brief An array of strings representing the names of the error locations.
         *
         * This static array maps the `Location` enumeration values to their corresponding string
         * representations, which are used for outputting human-readable error details.
         */
        static const std::string locations[static_cast<int>(Location::End)];
    };

    /**
     * @brief Outputs the error details to a stream.
     *
     * This function allows the contents of an `Error` object to be printed to an
     * output stream, such as `std::cout` or `std::ofstream`.
     *
     * @param ostream The output stream where the error details will be written.
     * @param error The Error object whose details are to be printed.
     * @return A reference to the output stream.
     */
    std::ostream &operator<<(std::ostream &ostream, const Error &error);

} // namespace Zylo
#endif // ZYLO_ERROR_HXX