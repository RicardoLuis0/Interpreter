#include "parser_line_matcher.h"

#include "symbols_keywords.h"
#include "parser_code_block_matcher.h"
#include "parser_statement_matcher.h"
#include "parser_expression_matcher.h"
#include "parser_definition_matcher.h"
#include "parser_var_type_matcher.h"

#include "my_except.h"

//Line = CodeBlock | Statement | Definition | Expression , symbol ';' | symbol ';' ;

using namespace Parser;

std::shared_ptr<Line> LineMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    int location_backup=p.location;
    try{
        return std::make_shared<Line>(CodeBlockMatcher().makeMatch(p),LINE_CODE_BLOCK,line_start,p.get_line(-1));
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        if(p.isSymbol(SYMBOL_CURLY_BRACKET_OPEN))throw;//must be codeblock, rethrow
        try{
            return std::make_shared<Line>(StatementMatcher().makeMatch(p),LINE_STATEMENT,line_start,p.get_line(-1));
        }catch(MyExcept::NoMatchException &e){
            p.location=location_backup;
            if(p.isKeyword({KEYWORD_IF,KEYWORD_FOR,KEYWORD_WHILE,KEYWORD_RETURN}))throw;//must be statement, rethrow
            try{
                return std::make_shared<Line>(DefinitionMatcher().makeMatch(p),LINE_DEFINITION,line_start,p.get_line(-1));
            }catch(MyExcept::NoMatchException &e){
                p.location=location_backup;
                std::shared_ptr<VarType> vt=nullptr;
                try{
                    vt=VarTypeMatcher().makeMatch(p);
                }catch(MyExcept::NoMatchException &e){
                    vt=nullptr;
                }
                if(vt)throw;//must be definition, throw
                std::shared_ptr<Expression> expr=nullptr;
                try{
                    expr=ExpressionMatcher().makeMatch(p);
                }catch(MyExcept::NoMatchException &e){
                    p.location=location_backup;
                    if(p.isSymbol(SYMBOL_SEMICOLON)){//allow empty lines
                        return std::make_shared<Line>(nullptr,LINE_EMPTY,line_start,p.get_line(-1));
                    }else{
                        throw;
                    }
                }
                if(p.isSymbol(SYMBOL_SEMICOLON)){
                    return std::make_shared<Line>(expr,LINE_EXPRESSION,line_start,p.get_line(-1));
                }else{
                    throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");//must end in semicolon
                }
            }
        }
    }
}