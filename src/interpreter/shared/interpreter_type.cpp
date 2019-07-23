#include "interpreter_type.h"

using namespace Interpreter;

Type::Type(type_type_t t1,type_primitive_type_t t2):type(t1),primitive(t2){
}

std::shared_ptr<Type> Type::void_type(){
    return std::make_shared<Type>(TYPE_VOID);
}

std::shared_ptr<Type> Type::primitive_type(type_primitive_type_t t){
    return std::make_shared<Type>(TYPE_PRIMITIVE,t);
}

std::shared_ptr<Type> Type::class_type(){
        throw std::runtime_error("classes/structs/typedefs not implemented yet");
}

bool Type::is_void(){
    return (type==TYPE_VOID);
}

bool Type::is_primitive(){
    return (type==TYPE_PRIMITIVE);
}

bool Type::is_int(){
    return (is_primitive()&&primitive==PRIMITIVE_INT);
}

bool Type::is_float(){
    return (is_primitive()&&primitive==PRIMITIVE_FLOAT);
}

bool Type::is_num(){
    return (is_int()||is_float());
}

bool Type::is_string(){
    return (is_primitive()&&primitive==PRIMITIVE_STRING);
}

bool Type::is_compatible(std::shared_ptr<Type> other){
    return (is_num()&&other->is_num())||(is_string()&&other->is_string());
}

bool Type::is_equal(std::shared_ptr<Type> other){
    if(type==other->type){
        if(type==TYPE_PRIMITIVE){
            return primitive==other->primitive;
        }
        return true;
    }
    return false;
}

std::string Type::get_name(){
    switch(type){
    default:
    case TYPE_INVALID:
        return "invalid";
    case TYPE_VOID:
        return "void";
    case TYPE_PRIMITIVE:
        switch(primitive){
        default:
        case PRIMITIVE_INVALID:
            return "invalid";
        case PRIMITIVE_INT:
            return "int";
        case PRIMITIVE_FLOAT:
            return "float";
        case PRIMITIVE_STRING:
            return "string";
        }
    case TYPE_CLASS:
        return "class";
    }
}

std::shared_ptr<Type> Type::from_vartype(std::shared_ptr<Parser::VarType> t){
    switch(t->type){
    default:
        throw std::runtime_error("invalid type");
    case Parser::VARTYPE_VOID:
        return void_type();
    case Parser::VARTYPE_PRIMITIVE:
        switch(t->primitive){
        case Parser::PRIMITIVE_INVALID:
            throw std::runtime_error("invalid primitive value 'PRIMITIVE_INVALID'");
        case Parser::PRIMITIVE_INT:
            return primitive_type(PRIMITIVE_INT);
        case Parser::PRIMITIVE_FLOAT:
            return primitive_type(PRIMITIVE_FLOAT);
        case Parser::PRIMITIVE_STRING:
            return primitive_type(PRIMITIVE_STRING);
        }
    case Parser::VARTYPE_IDENTIFIER:
        return class_type();//throws
    }
}
