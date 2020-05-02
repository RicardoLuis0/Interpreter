#include "Parser/FunctionDefinition.h"

#include "Parser/FunctionDefinitionParameter.h"
#include "Parser/VarType.h"
#include "Parser/CodeBlock.h"

#include "Lexer/token_type.h"

#include "symbols_keywords.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

FunctionDefinition::FunctionDefinition(parserProgress &p){
    line_start=p.get_line();
    variadic=false;
    int ls;
    return_type=std::make_shared<VarType>(p);
    std::shared_ptr<Lexer::Token> t=p.isType(Lexer::TOKEN_TYPE_WORD);
    if(!t){
        throw MyExcept::NoMatchException(p,"identifier");
    }
    name=std::static_pointer_cast<Lexer::WordToken>(t)->get_literal();
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN))throw MyExcept::NoMatchException(p,"'('");
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
        ls=p.get_line();
        auto vt=std::make_shared<VarType>(p);
        if(p.isSymbol(SYMBOL_VARIADIC)){
        pvariadic:
            variadic_type=vt;
            t=p.isType(Lexer::TOKEN_TYPE_WORD);
            if(!t){
                throw MyExcept::NoMatchExceptionFatal(p,"identifier");
            }
            variadic_ident=std::static_pointer_cast<Lexer::WordToken>(t)->get_literal();
            variadic=true;
        }else{
            parameters.emplace_back(std::make_shared<FunctionDefinitionParameter>(ls,vt,p));
            try{
                while(p.isSymbol(SYMBOL_COMMA)){
                    ls=p.get_line();
                    vt=std::make_shared<VarType>(p);
                    if(p.isSymbol(SYMBOL_VARIADIC)){
                        goto pvariadic;
                    }else{
                        parameters.emplace_back(std::make_shared<FunctionDefinitionParameter>(ls,vt,p));
                    }
                }
            }catch(MyExcept::NoMatchException &e){
                throw MyExcept::NoMatchExceptionFatal(e);
            }
        }
        if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE))throw MyExcept::NoMatchExceptionFatal(p,"')'");
    }
    code=std::make_shared<CodeBlock>(p);
    line_end=p.get_line(-1);
}

FunctionDefinition::FunctionDefinition(int ls,std::shared_ptr<VarType> vt,std::shared_ptr<Lexer::WordToken> ident,parserProgress &p){
    line_start=ls;
    return_type=vt;
    variadic=false;
    name=ident->get_literal();
    std::shared_ptr<Lexer::Token> t;
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN))throw MyExcept::NoMatchException(p,"'('");
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
        ls=p.get_line();
        auto vt=std::make_shared<VarType>(p);
        if(p.isSymbol(SYMBOL_VARIADIC)){
        pvariadic:
            variadic_type=vt;
            t=p.isType(Lexer::TOKEN_TYPE_WORD);
            if(!t){
                throw MyExcept::NoMatchExceptionFatal(p,"identifier");
            }
            variadic_ident=std::static_pointer_cast<Lexer::WordToken>(t)->get_literal();
            variadic=true;
        }else{
            parameters.emplace_back(std::make_shared<FunctionDefinitionParameter>(ls,vt,p));
            try{
                while(p.isSymbol(SYMBOL_COMMA)){
                    ls=p.get_line();
                    vt=std::make_shared<VarType>(p);
                    if(p.isSymbol(SYMBOL_VARIADIC)){
                        goto pvariadic;
                    }else{
                        parameters.emplace_back(std::make_shared<FunctionDefinitionParameter>(ls,vt,p));
                    }
                }
            }catch(MyExcept::NoMatchException &e){
                throw MyExcept::NoMatchExceptionFatal(e);
            }
        }
        if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE))throw MyExcept::NoMatchExceptionFatal(p,"')'");
    }
    code=std::make_shared<CodeBlock>(p);
    line_end=p.get_line(-1);
}

FunctionDefinition::FunctionDefinition(std::shared_ptr<VarType> ret,
                                       std::shared_ptr<Lexer::WordToken> t,
                                       std::vector<std::shared_ptr<FunctionDefinitionParameter>> p,
                                       bool v,
                                       std::shared_ptr<VarType> vt,
                                       std::shared_ptr<Lexer::WordToken> vi,
                                       std::shared_ptr<CodeBlock> c,
                                       int ls,int le):
    ParserResultPart(ls,le),
    return_type(ret),
    name(t->get_literal()),
    parameters(p),
    variadic(v),
    variadic_type(vt),
    variadic_ident(vi?vi->get_literal():""),
    code(c){
        
}


std::string FunctionDefinition::getSource(int indent){
    std::string head=return_type->getSource(indent)+" "+name+"(";
    bool first=true;
    for(auto param:parameters){
        if(!first){
            head+=",";
        }else{
            first=false;
        }
        head+=param->getSource(indent);
    }
    if(variadic){
        if(!first){
            head+=",";
        }
        if(variadic_type){
            head+=variadic_type->getSource(indent)+" ";
        }
        head+="... "+variadic_ident;
    }
    head+=") ";
    return head+code->getSource(indent)+"\n";
}

void FunctionDefinition::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"FunctionDefinition {\n";
    std::cout<<indent0<<".return_type:\n";
    return_type->print(depth+1);
    std::cout<<indent0<<".name:\n"<<indent1<<name<<"\n";
    if(parameters.size()>0){
        std::cout<<indent0<<".parameters:\n";
        for(int i=0;i<int(parameters.size());i++){
            std::cout<<indent1<<".param["<<i<<"]:\n";
            parameters[i]->print(depth+2);
        }
    }
    std::cout<<indent0<<".variadic:\n"<<indent1<<(variadic?"true":"false")<<"\n";
    if(variadic){
        std::cout<<indent0<<".variadic_type:\n";
        variadic_type->print(depth+1);
        std::cout<<indent0<<".variadic_ident:\n"<<indent1<<variadic_ident<<"\n";
    }
    std::cout<<indent0<<".code:\n";
    code->print(depth+1);
    std::cout<<indent0<<"}\n";
}
