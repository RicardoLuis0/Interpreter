#include "Interpreter/FunctionParameter.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "Interpreter/DefaultFrame.h"
#include "Interpreter/ReferenceType.h"

using namespace Interpreter;

FunctionParameter::FunctionParameter(std::shared_ptr<Type> t):type(t),name("undefined"){
    
}

FunctionParameter::FunctionParameter(std::shared_ptr<Type> t,std::string name):type(t),name(name){
    
}

std::vector<FunctionParameter> FunctionParameter::from_pfdp(DefaultFrame * context,std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> params){
    std::vector<FunctionParameter> temp;
    for(std::shared_ptr<Parser::FunctionDefinitionParameter> param:params){
        auto t=Type::from_vartype(context,param->type);
        temp.emplace_back(param->is_reference?std::make_shared<ReferenceType>(t):t,param->name);
    }
    return temp;
}

bool FunctionParameter::operator==(const FunctionParameter &other)const{
    return type->is(type,other.type);
}

std::string FunctionParameter::get_typelist(std::vector<FunctionParameter> params){
    std::string temp;
    bool first=true;
    for(FunctionParameter param:params){
        if(!first){
            temp+=',';
        }else{
            first=false;
        }
        temp+=param.type->get_name();
    }
    return temp;
}
