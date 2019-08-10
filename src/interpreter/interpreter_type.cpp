#include "interpreter_type.h"
#include "interpreter_void_type.h"
#include "interpreter_int_type.h"
#include "interpreter_float_type.h"
#include "interpreter_string_type.h"

using namespace Interpreter;

std::shared_ptr<Type> Type::void_type_instance(std::make_shared<VoidType>());
std::shared_ptr<Type> Type::int_type_instance(std::make_shared<IntType>());
std::shared_ptr<Type> Type::float_type_instance(std::make_shared<FloatType>());
std::shared_ptr<Type> Type::string_type_instance(std::make_shared<StringType>());

std::shared_ptr<Type> Type::void_type(){
    return void_type_instance;
}

std::shared_ptr<Type> Type::int_type(){
    return int_type_instance;
}

std::shared_ptr<Type> Type::float_type(){
    return float_type_instance;
}

std::shared_ptr<Type> Type::string_type(){
    return string_type_instance;
}

std::shared_ptr<Type> Type::class_type(class DefaultFrame * context,std::string name){
    throw std::runtime_error("classes/structs/typedefs not implemented yet");
}

std::string Type::get_name(){
    return "invalid";
}

std::shared_ptr<Type> Type::from_vartype(std::shared_ptr<Parser::VarType> t){
    switch(t->type){
    default:
        throw std::runtime_error("invalid type");
    case Parser::VARTYPE_VOID:
        return void_type_instance;
    case Parser::VARTYPE_PRIMITIVE:
        switch(t->primitive){
        case Parser::PRIMITIVE_INVALID:
            throw std::runtime_error("invalid primitive value 'PRIMITIVE_INVALID'");
        case Parser::PRIMITIVE_INT:
            return int_type_instance;
        case Parser::PRIMITIVE_FLOAT:
            return float_type_instance;
        case Parser::PRIMITIVE_STRING:
            return string_type_instance;
        }
    case Parser::VARTYPE_IDENTIFIER:
        return class_type(nullptr,"");//throws
    }
}

bool Type::allows_implicit_cast(std::shared_ptr<Type> other){
    return false;
}

bool Type::has_cast(std::shared_ptr<Type> other){
    return allows_implicit_cast(other);
}

std::shared_ptr<Value> Type::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    throw std::runtime_error("illegal cast");
}
