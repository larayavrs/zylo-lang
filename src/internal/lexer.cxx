/**
 * @file lexer.cxx
 * @brief Implementation of the lexer for the Zylo programming language.
 *
 * This file contains the implementation of the lexer (lexical analyzer) responsible for
 * tokenizing the source code in the Zylo programming language. The lexer reads the source
 * code character by character and groups sequences of characters into tokens, which represent
 * the smallest units of meaning in the language, such as keywords, identifiers, operators,
 * and literals.
 *
 * The lexer handles various tasks including:
 * - Identifying and classifying different types of tokens.
 * - Handling escape sequences within strings.
 * - Managing comments and whitespace.
 * - Reporting invalid tokens and errors.
 *
 * This file works in conjunction with the `lexer.hxx` header file, which provides the necessary
 * declarations for the lexer components.
 */

#include "lexer.hxx"
#include "error.hxx"

TokenIdentifier TokenIdentifier::tk_identifiers[static_cast<int>(TokenType::Invalid)] = {
    {{}},                                                                            // Number
    {{}},                                                                            // Bool
    {{}},                                                                            // String
    {{"const"}},                                                                     // Const
    {{"zylo"}},                                                                      // Var
    {{"func"}},                                                                      // Func
    {{"over"}},                                                                      // EndStatement
    {{"if"}},                                                                        // If
    {{"else"}},                                                                      // Else
    {{"while"}},                                                                     // While
    {{"="}},                                                                         // Equals
    {{"++", "--", "!"}},                                                             // UnaryOperator
    {{"+", "-", "*", "/", "%", "==", "!=", ">", "<", ">=", "<=", "**", "&&", "||"}}, // BinaryOperator
    {{"("}},                                                                         // OpenParen
    {{")"}},                                                                         // CloseParen
    {{"["}},                                                                         // OpenBracket
    {{"]"}},                                                                         // CloseBracket
    {{}},                                                                            // Identifier
    {{"#"}},                                                                         // Comment
    {{"\n", "\r", ";"}}                                                              // EndOfLine
};