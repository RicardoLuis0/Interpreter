#include "interpreter_type.h"
#include "interpreter_void_type.h"
#include "interpreter_int_type.h"
#include "interpreter_float_type.h"
#include "interpreter_string_type.h"
#include "interpreter_array_type.h"
#include "interpreter_default_frame.h"
#include "parser_expression.h"
#include "parser_expression_term.h"
#include "integer_token.h"

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

std::shared_ptr<Type> Type::class_type(DefaultFrame * context,std::string name){
    throw std::runtime_error("classes/structs/typedefs not implemented yet");
}

std::string Type::get_name(){
    return "invalid";
}

std::shared_ptr<Type> Type::from_vartype_ignore_array(DefaultFrame * context,std::shared_ptr<Parser::VarType> t){
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
        return class_type(context,"");//throws
    }
}

std::shared_ptr<Type> Type::from_vartype(DefaultFrame * context,std::shared_ptr<Parser::VarType> t){
    std::shared_ptr<Type> type=from_vartype_ignore_array(context,t);
    for(std::shared_ptr<Parser::Expression> e:t->array_sizes){
        if(e->type==Parser::EXPRESSION_TERM&&std::static_pointer_cast<Parser::ExpressionTerm>(e->contents)->type==Parser::EXPRESSION_TERM_LITERAL_INT){
            type=std::make_shared<ArrayType>(type,std::static_pointer_cast<Lexer::IntegerToken>(std::static_pointer_cast<Parser::ExpressionTerm>(e->contents)->contents_t)->get_integer());
        }else{
            throw std::runtime_error("invalid type for array size, must be integer literal");
        }
    }
    return type;
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
