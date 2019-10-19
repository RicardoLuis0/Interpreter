#include "Lexer/LiteralsTokenMatcher.h"
#include "Lexer/IntegerTokenMatcher.h"
#include "Lexer/FloatTokenMatcher.h"
#include "Lexer/StringTokenMatcher.h"
#include "Lexer/CharTokenMatcher.h"
#include "Lexer/OctalTokenMatcher.h"
#include "Lexer/HexTokenMatcher.h"
#include "Lexer/BinaryTokenMatcher.h"

Lexer::LiteralsTokenMatcher::LiteralsTokenMatcher(){
    list.push_back(std::make_shared<StringTokenMatcher>());
    list.push_back(std::make_shared<CharTokenMatcher>());
    list.push_back(std::make_shared<OctalTokenMatcher>());
    list.push_back(std::make_shared<HexTokenMatcher>());
    list.push_back(std::make_shared<BinaryTokenMatcher>());
    list.push_back(std::make_shared<IntegerTokenMatcher>());
    list.push_back(std::make_shared<FloatTokenMatcher>());
}
