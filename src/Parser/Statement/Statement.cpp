#include "Parser/Statement.h"

#include "Lexer/KeywordToken.h"

#include "Parser/IfStatement.h"
#include "Parser/ForStatement.h"
#include "Parser/WhileStatement.h"
#include "Parser/ReturnStatement.h"

#include "symbols_keywords.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

Statement::Statement(parserProgress &p){
    line_start=p.get_line();
    if(!p.peekType(Lexer::TOKEN_TYPE_KEYWORD)){
        throw MyExcept::NoMatchException(p,"statement");
    }
    switch(std::static_pointer_cast<Lexer::KeywordToken>(p.get(0))->get_keyword_type()){
    case KEYWORD_IF:
        statement=std::make_shared<IfStatement>(p);
        type=STATEMENT_IF;
        break;
    case KEYWORD_FOR:
        statement=std::make_shared<ForStatement>(p);
        type=STATEMENT_FOR;
        break;
    case KEYWORD_WHILE:
        statement=std::make_shared<WhileStatement>(p);
        type=STATEMENT_WHILE;
        break;
    case KEYWORD_RETURN:
        statement=std::make_shared<ReturnStatement>(p);
        type=STATEMENT_RETURN;
        break;
    case KEYWORD_BREAK:
        p++;
        type=STATEMENT_BREAK;
        break;
    case KEYWORD_CONTINUE:
        p++;
        type=STATEMENT_CONTINUE;
        break;
    default:
        throw MyExcept::NoMatchException(p,"statement");
    }
    line_end=p.get_line(-1);
}

Statement::Statement(std::shared_ptr<ParserResultPart> stmt,ParserStatementType_t sttype,int ls,int le):ParserResultPart(ls,le),statement(stmt),type(sttype){
    
}

std::string Statement::getSource(int indent){
    if(type==STATEMENT_BREAK){
        return "break;";
    }else if(type==STATEMENT_CONTINUE){
        return "continue;";
    }else{
        return statement->getSource(indent);
    }
}

void Statement::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"Statement {\n";
    if(type==STATEMENT_BREAK){
        std::cout<<indent0<<".type:\n"<<indent1<<"STATEMENT_BREAK\n";
    }else if(type==STATEMENT_CONTINUE){
        std::cout<<indent0<<".type:\n"<<indent1<<"STATEMENT_CONTINUE\n";
    }else{
        std::cout<<indent0<<".statement:\n";
        statement->print(depth+1);
    }
    std::cout<<indent0<<"}\n";
}
