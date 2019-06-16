#include "parser_line_matcher.h"

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
        p.location=location_backup;
        try{
            return std::make_shared<Line>(StatementMatcher().makeMatch(p),LINE_STATEMENT);
        }catch(MyExcept::NoMatchException &e){
            p.location=location_backup;
            return std::make_shared<Line>(ExpressionMatcher().makeMatch(p),LINE_EXPRESSION);
        }
    }
}
