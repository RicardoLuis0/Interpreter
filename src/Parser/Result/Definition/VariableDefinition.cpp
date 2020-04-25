#include "Parser/VariableDefinition.h"

#include <iostream>

using namespace Parser;

VariableDefinition::VariableDefinition(parserProgress &p){
    throw std::runtime_error("unimplemented");
}

VariableDefinition::VariableDefinition(std::shared_ptr<VarType> t,std::vector<std::shared_ptr<VariableDefinitionItem>> v,int ls,int le):ParserResultPart(ls,le),type(t),variables(v){}

std::string VariableDefinition::getSource(){
    std::string str=type->getSource()+" ";
    bool first=true;
    for(auto var:variables){
        if(!first){
            str+=",";
        }else{
            first=false;
        }
        str+=var->getSource();
    }
    return str;
}

void VariableDefinition::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"VariableDefinition {\n";
    std::cout<<indent0<<".type:\n";
    type->print(depth+1);
    std::cout<<indent0<<".variables:\n";
    for(int i=0;i<int(variables.size());i++){
        std::cout<<indent1<<".var["<<i<<"]:\n";
        variables[i]->print(depth+2);
    }
    std::cout<<indent0<<"}\n";
}
