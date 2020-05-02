#include "Parser/Definition.h"


#include "Parser/VarType.h"
#include "Parser/FunctionDefinition.h"
#include "Parser/VariableDefinition.h"
#include "Parser/StructDefinition.h"

#include "symbols_keywords.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

Definition::Definition(parserProgress &p){
    line_start=p.get_line();
    int ls=p.get_line();
    if(p.peekKeyword(KEYWORD_STRUCT)){
        def=std::make_shared<StructDefinition>(p);
        type=DEFINITION_STRUCT;
    }else{
        std::shared_ptr<VarType> vt=std::make_shared<VarType>(p);
        int ls2=p.get_line();
        std::shared_ptr<Lexer::WordToken> ident=std::static_pointer_cast<Lexer::WordToken>(p.isType(Lexer::TOKEN_TYPE_WORD));
        if(!ident)throw MyExcept::NoMatchException(p,"identifier");
        int i=p.location;
        if(p.peekSymbol(SYMBOL_PARENTHESIS_OPEN)){
            try{//TODO improve non-predicting match
                def=std::make_shared<FunctionDefinition>(ls,vt,ident,p);
                type=DEFINITION_FUNC;
            }catch(MyExcept::NoMatchException &){
                p.location=i;
                goto vdef;
            }
        }else{
        vdef:
            def=std::make_shared<VariableDefinition>(ls,vt,ls2,ident,p);
            type=DEFINITION_VAR;
            if(!p.isSymbol(SYMBOL_SEMICOLON))throw MyExcept::NoMatchExceptionFatal(p,"';'");//variable definition must end in semicolon
        }
    }
    line_end=p.get_line(-1);
}

Definition::Definition(ParserDefinitionType_t t,std::shared_ptr<ParserResultPart> d,int ls,int le):ParserResultPart(ls,le),type(t),def(d){
    
}

std::string Definition::getSource(int indent){
    if(type==DEFINITION_VAR){
        return def->getSource(indent)+";";
    }else{
        return def->getSource(indent);
    }
}

void Definition::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"Definition {\n";
    def->print(depth+1);
    std::cout<<indent0<<"}\n";
}
