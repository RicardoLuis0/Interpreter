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
    return "for("+(pre?pre->getSource():(vardef_pre?vardef_pre->getSource():""))+";"+(condition?condition->getSource():"")+";"+(inc?inc->getSource():"")+")"+code->getSource();
}

void ForStatement::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"ForStatement {\n";
    if(pre){
        std::cout<<indent0<<".pre:\n";
        pre->print(depth+1);
    }
    if(vardef_pre){
        std::cout<<indent0<<".vardef_pre:\n";
        vardef_pre->print(depth+1);
    }
    if(condition){
        std::cout<<indent0<<".condition:\n";
        condition->print(depth+1);
    }
    if(inc){
        std::cout<<indent0<<".inc:\n";
        inc->print(depth+1);
    }
    std::cout<<indent0<<".code:\n";
    code->print(depth+1);
    std::cout<<indent0<<"}\n";
}

