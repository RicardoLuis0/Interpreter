#include "Parser/Line.h"

#include "Parser/CodeBlock.h"
#include "Parser/Statement.h"
#include "Parser/Expression.h"
#include "Parser/Definition.h"
#include "Parser/VarType.h"

#include "symbols_keywords.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

Line::Line(parserProgress &p){
    line_start=p.get_line();
    if(p.isSymbol(SYMBOL_SEMICOLON)){
        type=LINE_EMPTY;
    }else if(p.peekSymbol(SYMBOL_CURLY_BRACKET_OPEN)){
        contents=std::make_shared<CodeBlock>(p);
        type=LINE_CODE_BLOCK;
    }else if(p.peekKeyword({KEYWORD_IF,KEYWORD_FOR,KEYWORD_WHILE,KEYWORD_RETURN,KEYWORD_BREAK,KEYWORD_CONTINUE})){
        contents=std::make_shared<Statement>(p);
        type=LINE_STATEMENT;
    }else{
        int i=p.location;
        try{//TODO improve non-predicting match
            contents=std::make_shared<Definition>(p);
            type=LINE_DEFINITION;
        }catch(MyExcept::NoMatchException &){
            p.location=i;
            contents=std::make_shared<Expression>(p);
            type=LINE_EXPRESSION;
            if(!p.isSymbol(SYMBOL_SEMICOLON)){
                throw MyExcept::NoMatchExceptionFatal(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");//must end in semicolon
            }
        }
    }
    line_end=p.get_line(-1);
}

Line::Line(std::shared_ptr<ParserResultPart> ptr,ParserLineType_t ptype,int ls,int le):ParserResultPart(ls,le),contents(ptr),type(ptype){
    
}

std::string Line::getSource(){
    if(type==LINE_EMPTY){
        return ";";
    }else if(type==LINE_EXPRESSION){
        return contents->getSource()+";";
    }else{
        return contents->getSource();
    }
}

void Line::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"Line {\n";
    std::cout<<indent0<<".content:\n";
    if(type==LINE_EMPTY){
        std::cout<<indent1<<"null\n";
    }else{
        contents->print(depth+1);
    }
    std::cout<<indent0<<"}\n";
}
