#include "Parser/FunctionDefinition.h"

#include <iostream>

using namespace Parser;

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


std::string FunctionDefinition::getSource(){
    std::string head=return_type->getSource()+" "+name+"(";
    bool first=true;
    for(auto param:parameters){
        if(!first){
            head+=",";
        }else{
            first=false;
        }
        head+=param->getSource();
    }
    if(variadic){
        if(!first){
            head+=",";
        }
        if(variadic_type){
            head+=variadic_type->getSource()+" ";
        }
        head+="... "+variadic_ident;
    }
    head+=") ";
    return head+code->getSource();
}

void FunctionDefinition::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"FunctionDefinition {\n";
    std::cout<<indent0<<".return_type:\n";
    return_type->print(depth+1);
    std::cout<<indent0<<".name:\n"<<indent1<<name<<"\n";
    if(parameters.size()>0_{
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
