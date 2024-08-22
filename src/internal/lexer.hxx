/**
 * @file lexer.hxx
 * @brief Defines the lexer for the Zylo programming language.
 *
 * This file contains the declaration of the lexer class and related utilities
 * for the Zylo programming language. The lexer is responsible for tokenizing
 * the source code into a sequence of tokens that represent the smallest units
 * of meaningful data in the source code. This is a crucial step in the
 * compilation or interpretation process, as it converts raw text into a form
 * that can be easily processed by the parser.
 *
 * The lexer handles different types of tokens including keywords, operators,
 * literals, and identifiers. It reads the source code character by character
 * and generates tokens based on predefined rules and patterns.
 */

#ifndef ZYLO_INTERNAL_LEXER_HXX // ZYLO_INTERNAL_LEXER_HXX

#define ZYLO_INTERNAL_LEXER_HXX

#include <string>
#include <vector>
#include <iostream>

/**
 * @enum TokenType
 * @brief Defines the types of tokens recognized by the lexer in the Zylo programming language.
 *
 * This enumeration categorizes the various types of tokens that the lexer can identify
 * while processing the source code. Each token type represents a specific category or
 * role that tokens play in the language syntax, allowing the lexer to classify and
 * handle them appropriately.
 */
enum class TokenType
{
    /**
     * @brief Represents a numeric literal.
     *
     * This token type is used for tokens that represent numeric values, such as integers
     * or floating-point numbers.
     */
    Number,

    /**
     * @brief Represents a boolean literal.
     *
     * This token type is used for tokens that represent boolean values, typically `true`
     * or `false`.
     */
    Bool,

    /**
     * @brief Represents a string literal.
     *
     * This token type is used for tokens that represent sequences of characters enclosed
     * in quotes.
     */
    String,

    /**
     * @brief Represents a constant keyword.
     *
     * This token type is used for the `const` keyword, which is used to declare constants
     * in the Zylo programming language.
     */
    Const,

    /**
     * @brief Represents a variable keyword.
     *
     * This token type is used for the `var` keyword, which is used to declare variables
     * in the Zylo programming language.
     */
    Var,

    /**
     * @brief Represents a function keyword.
     *
     * This token type is used for the `func` keyword, which is used to define functions
     * in the Zylo programming language.
     */
    Func,

    /**
     * @brief Represents the end of a statement.
     *
     * This token type is used for tokens that indicate the end of a statement, typically
     * represented by a semicolon (`;`).
     */
    EndStatement,

    /**
     * @brief Represents an `if` keyword.
     *
     * This token type is used for the `if` keyword, which introduces conditional statements
     * in the Zylo programming language.
     */
    If,

    /**
     * @brief Represents an `else` keyword.
     *
     * This token type is used for the `else` keyword, which provides an alternative path
     * in conditional statements.
     */
    Else,

    /**
     * @brief Represents a `while` keyword.
     *
     * This token type is used for the `while` keyword, which introduces a loop that repeats
     * as long as its condition remains true.
     */
    While,

    /**
     * @brief Represents the equality operator (`==`).
     *
     * This token type is used for the equality operator, which compares two values for equality.
     */
    Equals,

    /**
     * @brief Represents a unary operator.
     *
     * This token type is used for operators that operate on a single operand, such as `-` or `!`.
     */
    UnaryOperator,

    /**
     * @brief Represents a binary operator.
     *
     * This token type is used for operators that operate on two operands, such as `+`, `-`, `*`, or `/`.
     */
    BinaryOperator,

    /**
     * @brief Represents an opening parenthesis (`(`).
     *
     * This token type is used for the opening parenthesis, which is used to group expressions
     * or parameters.
     */
    OpenParen,

    /**
     * @brief Represents a closing parenthesis (`)`).
     *
     * This token type is used for the closing parenthesis, which is used to close a grouping
     * of expressions or parameters.
     */
    CloseParen,

    /**
     * @brief Represents an opening bracket (`[`).
     *
     * This token type is used for the opening bracket, which is used to denote arrays or lists.
     */
    OpenBracket,

    /**
     * @brief Represents a closing bracket (`]`).
     *
     * This token type is used for the closing bracket, which is used to close arrays or lists.
     */
    CloseBracket,

    /**
     * @brief Represents an identifier.
     *
     * This token type is used for tokens that represent variable names, function names,
     * or other user-defined identifiers.
     */
    Identifier,

    /**
     * @brief Represents a comment.
     *
     * This token type is used for tokens that represent comments in the source code,
     * which are ignored by the lexer and compiler.
     */
    Comment,

    /**
     * @brief Represents the end of a line.
     *
     * This token type is used for tokens that indicate the end of a line in the source code,
     * such as newline characters.
     */
    EndOfLine,

    /**
     * @brief Represents the end of the file.
     *
     * This token type is used for tokens that indicate the end of the source code file.
     */
    EndOfFile,

    /**
     * @brief Represents an invalid token.
     *
     * This token type is used for tokens that do not match any valid token type, indicating
     * a lexical error or unrecognized input.
     */
    Invalid
};

/**
 * @struct TokenIdentifier
 * @brief Represents a collection of identifiers for different token types.
 *
 * This structure holds a collection of identifiers for various token types. Each
 * token type (as defined in the `TokenType` enumeration) can have associated identifiers,
 * which are stored in this structure. The static member `tokenIdentifiers` is an array
 * where each entry corresponds to a `TokenType`, storing the identifiers relevant to that
 * token type.
 */
struct TokenIdentifier
{
    /**
     * @brief An array of identifiers for each token type.
     *
     * This array stores identifiers for each token type, where the index of the array
     * corresponds to the `TokenType` enumeration value. Each entry in the array is a vector
     * of strings representing the identifiers for that token type.
     */
    std::vector<std::string> indentifiers;

    /**
     * @brief Initializes the token identifiers for each token type.
     *
     * This function initializes the token identifiers for each token type by populating
     * the `indentifiers` array with the relevant identifiers for each token type.
     */
    static TokenIdentifier tk_identifiers[static_cast<int>(TokenType::Invalid)];
};

/**
 * @struct Token
 * @brief Represents a token generated by the lexer.
 *
 * This structure represents a token generated by the lexer during the tokenization
 * process. Each token has a type (as defined by the `TokenType` enumeration) and a
 * value, which is the actual text content of the token in the source code.
 */
struct Token
{
    /**
     * @brief The type of the token.
     *
     * This field stores the type of the token, which indicates the category or role
     * of the token in the language syntax.
     */
    TokenType type;

    /**
     * @brief The text of the token.
     *
     * This member holds the string value of the token, representing the actual text
     * extracted from the source code. This value can be used for further processing
     * or analysis by the parser or other components.
     */
    std::string value;
};

/**
 * @brief Processes escape characters in a string.
 *
 * This function replaces escape sequences (such as `\n`, `\t`, etc.) in the provided
 * string with their corresponding characters. It modifies the string in place.
 *
 * @param string A reference to the string to process. Escape sequences in this string
 *               will be replaced with the actual characters they represent.
 */
void process_escape_characters(std::string &string);

/**
 * @brief Reverts the escape characters in a string to their escape sequence representations.
 *
 * This function converts characters in the string that are represented by escape sequences
 * (such as newline and tab) back into their escape sequence forms (e.g., `\n`, `\t`).
 * It modifies the string in place.
 *
 * @param string A reference to the string to unprocess. Characters that are currently
 *               represented as escape sequences will be converted back to their
 *               escape sequence representations.
 */
void unprocess_escape_characters(std::string &string);

/**
 * @brief Extracts the next identifier from a line of text.
 *
 * This function extracts the next identifier from the given line of text, based on a
 * specified separator character. Identifiers are sequences of characters that are separated
 * by the separator.
 *
 * @param line A reference to the string from which to extract the identifier.
 * @param separator The character used to separate identifiers in the string. Default is a space.
 * @return The extracted identifier as a string.
 */
std::string extract_identifier(std::string &line, char separator = ' ');

/**
 * @brief Extracts words from a string into a vector.
 *
 * This function splits the provided string into words based on whitespace or other delimiters.
 * The words are then stored in a vector and returned.
 *
 * @param string The string to extract words from.
 * @return A vector of strings, each representing a word extracted from the input string.
 */
std::vector<std::string> extract_words(const std::string &string);

/**
 * @brief Determines the type of a token based on its identifier.
 *
 * This function analyzes the given identifier and determines the type of token it represents.
 * The token type is determined based on predefined rules and patterns.
 *
 * @param next_id The identifier for which to determine the token type.
 * @return The `Token` structure representing the type of token.
 */
Token determine_token_type(const std::string &next_id);

/**
 * @brief Tokenizes the source code into a sequence of tokens.
 *
 * This function processes the entire source code and breaks it down into tokens. Each token
 * represents a meaningful unit of the source code, and the sequence of tokens is returned
 * as a vector.
 *
 * @param src The source code to tokenize.
 * @return A vector of `Token` objects representing th me tokens extracted from the source code.
 */
std::vector<Token> tokenize(const std::string &src);

/**
 * @brief Overload of the stream insertion operator to print a token.
 *
 * This function overloads the `<<` operator to allow printing a `Token` object
 * to an output stream, such as `std::cout`. The token is printed in a readable format,
 * displaying the token type and its content.
 *
 * @param ostream The output stream where the token will be printed.
 * @param token The `Token` object to be printed.
 * @return A reference to the output stream, allowing chaining of output operations.
 *
 * @note This function is useful for debugging and visualizing tokens.
 */
std::ostream &operator<<(std::ostream &ostream, Token token);

/**
 * @brief Overload of the stream insertion operator to print a vector of tokens.
 *
 * This function overloads the `<<` operator to allow printing a vector of `Token` objects
 * to an output stream, such as `std::cout`. Each token in the vector is printed in a readable
 * format with separation between them.
 *
 * @param ostream The output stream where the tokens will be printed.
 * @param tokens The vector of `Token` objects to be printed.
 * @return A reference to the output stream, allowing chaining of output operations.
 *
 * @note This function is useful for debugging and visualizing sequences of tokens.
 */
std::ostream &operator<<(std::ostream &ostream, const std::vector<Token> &tokens);

#endif // ZYLO_INTERNAL_LEXER_HXX