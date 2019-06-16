#include "parser_expression_term_matcher.h"

#include "parser_expression_group_matcher.h"
#include "parser_function_call_matcher.h"
#include "my_except.h"
#include "parser_unary_operation_matcher.h"
#include "symbols_keywords.h"

//ExpressionTerm = ExpressionGroup | FunctionCall | UnaryOperation | literal | identifier ;

std::shared_ptr<Parser::ExpressionTerm> Parser::ExpressionTermMatcher::makeMatch(parserProgress &p){
    int location_backup=p.location;
    try{
        return std::make_shared<ExpressionTerm>(ExpressionGroupMatcher().makeMatch(p),EXPRESSION_TERM_EXPRESSION_GROUP);
    }catch(MyExcept::NoMatchException &e){
        if(p.peekSymbol(SYMBOL_PARENTHESIS_OPEN)){
            //if it is definitely an expression group, re-throw previous exception
            throw;
        }
        p.location=location_backup;
        try{
            return std::make_shared<ExpressionTerm>(FunctionCallMatcher().makeMatch(p),EXPRESSION_TERM_FUNCTION_CALL);
        }catch(MyExcept::NoMatchException &e){
            p.location=location_backup;
            if(p.peekType(Lexer::TOKEN_TYPE_WORD)&&p.peekSymbol(SYMBOL_PARENTHESIS_OPEN,1)){
               //if it is definitely a function call, re-throw previous exception
               throw;
            }
            try{
                return std::make_shared<ExpressionTerm>(UnaryOperationMatcher().makeMatch(p),EXPRESSION_TERM_UNARY_OPERATION);
            }catch(MyExcept::NoMatchException &e){
                p.location=location_backup;
                std::shared_ptr<Lexer::Token> temp_token;
                temp_token=p.isType(Lexer::TOKEN_TYPE_INTEGER);//int
                if(temp_token)return std::make_shared<ExpressionTerm>(temp_token,EXPRESSION_TERM_LITERAL_INT);
                temp_token=p.isType(Lexer::TOKEN_TYPE_FLOAT);//float
                if(temp_token)return std::make_shared<ExpressionTerm>(temp_token,EXPRESSION_TERM_LITERAL_FLOAT);
                temp_token=p.isType(Lexer::TOKEN_TYPE_STRING);//string
                if(temp_token)return std::make_shared<ExpressionTerm>(temp_token,EXPRESSION_TERM_LITERAL_STRING);
                temp_token=p.isType(Lexer::TOKEN_TYPE_WORD);//ident
                if(temp_token)return std::make_shared<ExpressionTerm>(temp_token,EXPRESSION_TERM_IDENTIFIER);
                throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected literal or identifier, got '"+p.get_nothrow_nonull()->get_formatted()+"'");
            }
        }
    }
}
