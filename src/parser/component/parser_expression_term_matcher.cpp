#include "parser_expression_term_matcher.h"

#include "parser_expression_group_matcher.h"
#include "parser_function_call_matcher.h"
#include "my_except.h"
#include "parser_unary_operation_matcher.h"
#include "symbols_keywords.h"
#include "parser_expression_matcher.h"
#include "lexer_keyword_token.h"

//literal = int,float,string,true,false

//ExpressionTerm = ( ExpressionGroup | FunctionCall | UnaryOperation | literal | identifier ) , { symbol 'unary_post_operator' } , { symbol '[' , Expression , symbol ']' };

using namespace Parser;

std::shared_ptr<ExpressionTerm> ExpressionTermMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    int location_backup=p.location;
    std::shared_ptr<ExpressionTerm> term=nullptr;
    try{
        term=std::make_shared<ExpressionTerm>(ExpressionGroupMatcher().makeMatch(p),EXPRESSION_TERM_EXPRESSION_GROUP,line_start,p.get_line(-1));
    }catch(MyExcept::NoMatchException &e){
        if(p.peekSymbol(SYMBOL_PARENTHESIS_OPEN)){
            //if it is definitely an expression group, re-throw previous exception
            throw;
        }
        p.location=location_backup;
        try{
            term=std::make_shared<ExpressionTerm>(FunctionCallMatcher().makeMatch(p),EXPRESSION_TERM_FUNCTION_CALL,line_start,p.get_line(-1));
        }catch(MyExcept::NoMatchException &e){
            p.location=location_backup;
            if(p.peekType(Lexer::TOKEN_TYPE_WORD)&&p.peekSymbol(SYMBOL_PARENTHESIS_OPEN,1)){
               //if it is definitely a function call, re-throw previous exception
               throw;
            }
            try{
                term=std::make_shared<ExpressionTerm>(UnaryOperationMatcher().makeMatch(p),EXPRESSION_TERM_UNARY_OPERATION,line_start,p.get_line(-1));
            }catch(MyExcept::NoMatchException &e){
                p.location=location_backup;
                std::shared_ptr<Lexer::Token> temp_token;
                if(temp_token=p.isType(Lexer::TOKEN_TYPE_INTEGER)){//int
                    term=std::make_shared<ExpressionTerm>(temp_token,EXPRESSION_TERM_LITERAL_INT,line_start,p.get_line(-1));
                }else if(temp_token=p.isType(Lexer::TOKEN_TYPE_CHAR)){//float
                    term=std::make_shared<ExpressionTerm>(temp_token,EXPRESSION_TERM_LITERAL_CHAR,line_start,p.get_line(-1));
                }else if(temp_token=p.isType(Lexer::TOKEN_TYPE_FLOAT)){//float
                    term=std::make_shared<ExpressionTerm>(temp_token,EXPRESSION_TERM_LITERAL_FLOAT,line_start,p.get_line(-1));
                }else if(temp_token=p.isType(Lexer::TOKEN_TYPE_STRING)){//string
                    term=std::make_shared<ExpressionTerm>(temp_token,EXPRESSION_TERM_LITERAL_STRING,line_start,p.get_line(-1));
                }else if(temp_token=p.isKeyword({KEYWORD_TRUE,KEYWORD_FALSE})){
                    term=std::make_shared<ExpressionTerm>(p.get(-1),(std::static_pointer_cast<Lexer::KeywordToken>(temp_token)->get_keyword_type()==KEYWORD_TRUE)?EXPRESSION_TERM_LITERAL_TRUE:EXPRESSION_TERM_LITERAL_FALSE,line_start,p.get_line(-1));
                }else if(temp_token=p.isType(Lexer::TOKEN_TYPE_WORD)){//ident
                    term=std::make_shared<ExpressionTerm>(temp_token,EXPRESSION_TERM_IDENTIFIER,line_start,p.get_line(-1));
                }else{
                    throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected literal or identifier, got '"+p.get_nothrow_nonull()->get_formatted()+"'");
                }
            }
        }
    }
    if(!term){
        throw std::runtime_error("unexpected nullptr");
    }
    std::shared_ptr<Lexer::SymbolToken> ptr;
    while(ptr=p.isSymbol(UnaryOperationMatcher::post_unary_operators)){
        term->unary_post_operators.push_back(ptr);
    }
    while(p.isSymbol(SYMBOL_SQUARE_BRACKET_OPEN)){
        term->array_access.push_back(ExpressionMatcher().makeMatch(p));
        if(!p.isSymbol(SYMBOL_SQUARE_BRACKET_CLOSE)){
            throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ']', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
        }
    }
    return term;
}
