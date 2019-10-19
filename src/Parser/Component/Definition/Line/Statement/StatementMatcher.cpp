#include "Parser/StatementMatcher.h"

#include "Lexer/KeywordToken.h"
#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"
#include "Parser/IfStatementMatcher.h"
#include "Parser/ForStatementMatcher.h"
#include "Parser/WhileStatementMatcher.h"
#include "Parser/ReturnStatementMatcher.h"

//Statement = IfStatement | WhileStatement | ForStatement | ReturnStatement | keyword 'break' | keyword 'continue' ;

using namespace Parser;

std::shared_ptr<Statement> StatementMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<Lexer::KeywordToken> tk=p.isKeyword({KEYWORD_IF,KEYWORD_FOR,KEYWORD_WHILE,KEYWORD_RETURN,KEYWORD_BREAK,KEYWORD_CONTINUE});
    if(tk){
        p--;
        switch(tk->get_keyword_type()){
        case KEYWORD_IF:
            return std::make_shared<Statement>(IfStatementMatcher().makeMatch(p),STATEMENT_IF,line_start,p.get_line(-1));
        case KEYWORD_FOR:
            return std::make_shared<Statement>(ForStatementMatcher().makeMatch(p),STATEMENT_FOR,line_start,p.get_line(-1));
        case KEYWORD_WHILE:
            return std::make_shared<Statement>(WhileStatementMatcher().makeMatch(p),STATEMENT_WHILE,line_start,p.get_line(-1));
        case KEYWORD_RETURN:
            return std::make_shared<Statement>(ReturnStatementMatcher().makeMatch(p),STATEMENT_RETURN,line_start,p.get_line(-1));
        case KEYWORD_BREAK:
            p++;
            return std::make_shared<Statement>(nullptr,STATEMENT_BREAK,line_start,p.get_line(-1));
        case KEYWORD_CONTINUE:
            p++;
            return std::make_shared<Statement>(nullptr,STATEMENT_CONTINUE,line_start,p.get_line(-1));
        default:
            throw std::runtime_error("unreachable");
        }
    }else{
        throw MyExcept::NoMatchException(0,"this should never fall through");
    }
}
