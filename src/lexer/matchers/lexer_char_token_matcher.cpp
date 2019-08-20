#include "lexer_char_token_matcher.h"
#include "lexer_char_token.h"
#include "hex_read_util.h"
#include "my_except.h"


bool Lexer::CharTokenMatcher::partialMatch(std::string s){
    return partialMatchString(s,'\'');
}

bool Lexer::CharTokenMatcher::fullMatch(std::string s){
    return fullMatchString(s,'\'');
}

std::shared_ptr<Lexer::Token> Lexer::CharTokenMatcher::makeMatch(int line,std::string s){
    std::shared_ptr<StringToken> tk=matchString(line,s,'\'');
    #ifdef MULTICHAR_LITERAL_FATAL
    if(tk->get_string().size()>1){
        throw MyExcept::NoMatchException(line,s);
    }
    #endif
    return std::make_shared<CharToken>(line,tk->get_string()[0],tk->get_literal());
}
