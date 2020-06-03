#ifndef LEXER_H
#define LEXER_H

#include <memory>
#include <vector>
#include <string>
#include "Lexer/Token.h"

#include "Lexer/GlobalTokenMatcher.h"
#include "Lexer/keyword_data.h"
#include "Lexer/symbol_data.h"

namespace Lexer{
    class Lexer{
    public:
        Lexer(std::vector<symbol_data> &symbols,std::vector<keyword_data> &keywords);
        std::vector<std::shared_ptr<Token>> tokenize_from_file(std::string filename);
        std::vector<std::shared_ptr<Token>> tokenize_from_string(std::string filename,std::string &data);
    protected:
        GlobalTokenMatcher tokenMatcher;
    };
}

#endif // LEXER_H
