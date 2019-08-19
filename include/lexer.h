#ifndef LEXER_H
#define LEXER_H

#include <memory>
#include <vector>
#include <string>
#include "lexer_token.h"

#include "lexer_global_token_matcher.h"
#include "keyword_data.h"
#include "symbol_data.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{
    class Lexer{
    public:
        Lexer(std::vector<symbol_data> &symbols,std::vector<keyword_data> &keywords);
        /**
         * Read file from disk and Tokenize it.
         * @param filename file to tokenize
         */
        std::vector<std::shared_ptr<Token>> tokenize_from_file(std::string filename);
        /**
         * Tokenize string passed to it.
         * @param filename name to show in errors
         * @param data string to tokenize
         */
        std::vector<std::shared_ptr<Token>> tokenize_from_string(std::string filename,std::string &data);
    protected:
        GlobalTokenMatcher tokenMatcher;
    };
}

#endif // LEXER_H
