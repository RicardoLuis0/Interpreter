#include "parser_statement_matcher.h"

#include "keyword_token.h"
#include "symbols_keywords.h"
#include "my_except.h"
#include "parser_if_statment_matcher.h"
#include "parser_for_statement_matcher.h"
#include "parser_while_statement_matcher.h"
#include "parser_return_statement_matcher.h"

//Statement = IfStatement | WhileStatement | ForStatement | ReturnStatement | keyword 'break' | keyword 'continue' ;

std::shared_ptr<Parser::Statement> Parser::StatementMatcher::makeMatch(parserProgress &p){
    std::shared_ptr<Lexer::KeywordToken> tk=p.isKeyword({KEYWORD_IF,KEYWORD_FOR,KEYWORD_WHILE,KEYWORD_RETURN,KEYWORD_BREAK,KEYWORD_CONTINUE});
    if(tk){
        p--;
        switch(tk->get_keyword_type()){
        case KEYWORD_IF:
            return std::make_shared<Statement>(IfStatementMatcher().makeMatch(p),STATEMENT_IF);
        case KEYWORD_FOR:
            return std::make_shared<Statement>(ForStatementMatcher().makeMatch(p),STATEMENT_FOR);
        case KEYWORD_WHILE:
            return std::make_shared<Statement>(WhileStatementMatcher().makeMatch(p),STATEMENT_WHILE);
        case KEYWORD_RETURN:
            return std::make_shared<Statement>(ReturnStatementMatcher().makeMatch(p),STATEMENT_RETURN);
        case KEYWORD_BREAK:
            p++;
            return std::make_shared<Statement>(nullptr,STATEMENT_BREAK);
        case KEYWORD_CONTINUE:
            p++;
            return std::make_shared<Statement>(nullptr,STATEMENT_CONTINUE);
        default:
            throw std::runtime_error("unreachable");
        }
    }else{
        throw MyExcept::NoMatchException(0,"ignore_this");
    }
}
