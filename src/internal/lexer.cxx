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

void process_escape_characters(std::string &string)
{
    for (int chridx = 0; chridx < string.size(); chridx++)
    {
        const char chr = string[chridx];
        if (chr == '\\' && chridx < string.size() - 1)
        {
            const char nextchr = string[chridx + 1];
            char replchr = ' '; // Default replacement character 8)
            switch (nextchr)
            {
            case 'n':
                replchr = '\n';
                break;
            case 't':
                replchr = '\t';
                break;
            }
            if (replchr != ' ')
            {
                // Replace the escape sequence with the actual character
                string[chridx] = replchr;
                // Remove the escape character
                // NOTE: This is not efficient for large strings
                string.erase(string.begin() + chridx + 1);
            }
        }
    }
}

void unprocess_escape_characters(std::string &string)
{
    for (int chridx = 0; chridx < string.size(); chridx++)
    {
        const char chr = string[chridx];
        std::string inststr;
        switch (chr)
        {
        case '\n':
            inststr = "\\n";
            break;
        case '\t':
            inststr = "\\t";
            break;
        }
        if (!inststr.empty())
        {
            string.erase(string.begin() + chridx);
            string.insert(chridx, inststr);
            chridx++;
        }
    }
}

std::string extract_identifier(std::string &line, char separator)
{
    const char skpchrs[] = {' ', '\t', '\0'};
    const char nonchainablechrs[] = {'(', ')', '[', ']'};
    enum class IdentifierType
    {
        Alpha,    // Alphabetic characters
        Numeric,  // Numeric characters
        Symbolic, // Symbolic characters
        Unknown   // Unknown characters
    };
    auto isskpchr = [&skpchrs](char chr) -> bool
    {
        for (auto skippablechr : skpchrs)
        {
            if (skippablechr == chr)
                return true;
        }
        return false;
    };
    auto isunchainablechr = [&nonchainablechrs](char chr) -> bool
    {
        for (auto nonchainablechr : nonchainablechrs)
        {
            if (nonchainablechr == chr)
                return true;
        }
        return false;
    };
    auto determineidtype = [](char chr) -> IdentifierType
    {
        return (
                   chr == '_' ||
                   (chr >= 'A' && chr <= 'Z') ||
                   (chr >= 'a' && chr <= 'z'))
                   ? IdentifierType::Alpha
                   : (
                         ((chr == '.' || chr == '-' || (chr >= '0' && chr <= '9')
                               ? IdentifierType::Numeric
                               : IdentifierType::Symbolic)));
    };

    IdentifierType idtype = IdentifierType::Unknown; // The type of the current identifier
    std::string nextid;                              // The next identifier to extract
    size_t nextidend = 0;                            // The index of the next identifier's end in the line
    bool isstr = false;                              // Whether the identifier is a string
    bool iscomment = false;                          // Whether the identifier is a comment

    for (auto chr : line) // Iterate over each character in the line
    {
        if (iscomment)
        {
            nextidend++;
            if (chr == '\n')
                break;
            continue;
        }
        if (isunchainablechr(chr)) // Check if the character is unchainable
        {
            if (nextidend == 0)
            {
                nextidend++;
                nextid += chr;
            }
            break;
        }
        if (isskpchr(chr) || isstr)
        {
            if (!iscomment)
            {
                if (chr == '\"')
                {
                    if (isstr)
                    {
                        nextidend++;
                        break;
                    }
                    isstr = true;
                }
                else if (chr == '#')
                {
                    iscomment = true; // Assume the rest of the line is a comment
                    if (nextid.size() > 0)
                        break;
                    else
                        nextidend++;
                    continue;
                }
                if (isstr)
                {
                    nextidend++;
                    nextidend += chr;
                    continue;
                }
            }
            IdentifierType currentidtype = determineidtype(chr);
            if (idtype == IdentifierType::Unknown)
                idtype = currentidtype;
            else
            {
                if (idtype == IdentifierType::Numeric)
                {
                    if (nextid[0] == '-' && chr == '-')
                    {
                        nextidend++;
                        nextid += chr;
                        break;
                    }
                    else if (nextid.size() > 0 && (chr == '-' || currentidtype != IdentifierType::Numeric))
                        break;
                }
                if (
                    (idtype == IdentifierType::Symbolic && currentidtype != IdentifierType::Symbolic) ||
                    (idtype != IdentifierType::Symbolic) &&
                        (currentidtype == IdentifierType::Symbolic || chr == '-'))
                    break;
            }
            nextid += chr;
        }
        else if (nextid.size() > 0)
            break;
        nextidend++;
    }
    line = line.substr(nextidend);
    return nextid;
}