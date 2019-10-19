#include "Interpreter/FunctionParameter.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "Interpreter/DefaultFrame.h"

using namespace Interpreter;

FunctionParameter::FunctionParameter(std::shared_ptr<Type> t):type(t),name("undefined"),is_reference(false){
    
}

FunctionParameter::FunctionParameter(std::shared_ptr<Type> t,std::string name,bool ref):type(t),name(name),is_reference(ref){
    
}

std::vector<FunctionParameter> FunctionParameter::from_pfdp(DefaultFrame * context,std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> params){
    std::vector<FunctionParameter> temp;
    for(std::shared_ptr<Parser::FunctionDefinitionParameter> param:params){
        temp.emplace_back(Type::from_vartype(context,param->type),param->name,param->is_reference);
    }
    return temp;
}

bool FunctionParameter::operator==(const FunctionParameter &other)const{
    return typeid(*type)==typeid(*(other.type));
}

std::string FunctionParameter::get_typelist(std::vector<FunctionParameter> params,bool print_ref){
    std::string temp;
    bool first=true;
    for(FunctionParameter param:params){
        if(!first){
            temp+=',';
        }else{
            first=false;
        }
        temp+=param.type->get_name();
        if(print_ref&&param.is_reference){
            temp+=" &";
        }
    }
    return temp;
}
