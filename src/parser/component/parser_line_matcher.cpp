#include "parser_line_matcher.h"

#include "symbols_keywords.h"
#include "parser_code_block_matcher.h"
#include "parser_statement_matcher.h"
#include "parser_expression_matcher.h"

#include "my_except.h"

//Line = CodeBlock | Statement | Expression , symbol ';' ;

std::shared_ptr<Parser::Line> Parser::LineMatcher::makeMatch(parserProgress &p){
    int location_backup=p.location;
    try{
        return std::make_shared<Line>(CodeBlockMatcher().makeMatch(p),LINE_CODE_BLOCK);
    }catch(MyExcept::NoMatchException &e){
        if(p.isSymbol(SYMBOL_CURLY_BRACKET_OPEN)){
            throw;//must be codeblock, rethrow
        }
        p.location=location_backup;
        try{
            return std::make_shared<Line>(StatementMatcher().makeMatch(p),LINE_STATEMENT);
        }catch(MyExcept::NoMatchException &e){
            if(p.isKeyword({KEYWORD_IF,KEYWORD_FOR,KEYWORD_WHILE})){
                throw;//must be statement, rethrow
            }
            p.location=location_backup;
            std::shared_ptr<Expression> expr=ExpressionMatcher().makeMatch(p);
            if(p.isSymbol(SYMBOL_SEMICOLON)){
                return std::make_shared<Line>(expr,LINE_EXPRESSION);
            }else{
                throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");//must end in semicolon
            }
        }
    }
}
