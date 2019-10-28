#include "Parser/ForStatement.h"

#include <iostream>

using namespace Parser;

ForStatement::ForStatement(std::shared_ptr<Expression> p,std::shared_ptr<VariableDefinition> vp,std::shared_ptr<Expression> c,std::shared_ptr<Expression> i,std::shared_ptr<Line> l,int ls,int le):
    ParserResultPart(ls,le),
    pre(p),
    condition(c),
    inc(i),
    vardef_pre(vp),
    code(l){
        
}

std::string ForStatement::getSource(){
    throw std::runtime_error("unimplemented");
    return "";
}

void ForStatement::print(int depth){
    throw std::runtime_error("unimplemented");
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"ForStatement {\n";
    std::cout<<indent0<<"}\n";
}

