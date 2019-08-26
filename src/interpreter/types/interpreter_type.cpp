#include "interpreter_type.h"
#include "interpreter_any_type.h"
#include "interpreter_void_type.h"
#include "interpreter_char_type.h"
#include "interpreter_unsigned_char_type.h"
#include "interpreter_int_type.h"
#include "interpreter_unsigned_int_type.h"
#include "interpreter_float_type.h"
#include "interpreter_string_type.h"
#include "interpreter_array_type.h"
#include "interpreter_default_frame.h"
#include "parser_expression.h"
#include "parser_expression_term.h"
#include "lexer_integer_token.h"
#include "interpreter_util_defines_misc.h"
#include "my_except.h"

using namespace Interpreter;

std::shared_ptr<Type> Type::any_type_instance(std::make_shared<AnyType>());
std::shared_ptr<Type> Type::void_type_instance(std::make_shared<VoidType>());
std::shared_ptr<Type> Type::char_type_instance(std::make_shared<CharType>());
std::shared_ptr<Type> Type::unsigned_char_type_instance(std::make_shared<UnsignedCharType>());
std::shared_ptr<Type> Type::int_type_instance(std::make_shared<IntType>());
std::shared_ptr<Type> Type::unsigned_int_type_instance(std::make_shared<UnsignedIntType>());
std::shared_ptr<Type> Type::float_type_instance(std::make_shared<FloatType>());
std::shared_ptr<Type> Type::string_type_instance(std::make_shared<StringType>());

std::shared_ptr<Type> Type::any_type(){
    return any_type_instance;
}

std::shared_ptr<Type> Type::void_type(){
    return void_type_instance;
}

std::shared_ptr<Type> Type::char_type(){
    return char_type_instance;
}

std::shared_ptr<Type> Type::unsigned_char_type(){
    return unsigned_char_type_instance;
}

std::shared_ptr<Type> Type::int_type(){
    return int_type_instance;
}

std::shared_ptr<Type> Type::unsigned_int_type(){
    return unsigned_int_type_instance;
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

bool Type::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return false;
}

std::shared_ptr<Type> Type::from_vartype_ignore_array(DefaultFrame * context,std::shared_ptr<Parser::VarType> t){
    switch(t->type){
    case Parser::VARTYPE_VOID:
        if(t->has_sign)throw std::runtime_error("unexpected "+std::string(t->sign?"signed":"unsigned"));
        return void_type_instance;
    case Parser::VARTYPE_IDENTIFIER:
        return class_type(context,"");//throws
    case Parser::VARTYPE_PRIMITIVE:
        switch(t->primitive){
        case Parser::PRIMITIVE_INVALID:
            throw MyExcept::SyntaxError(t->line_start,t->line_end,"invalid primitive value 'PRIMITIVE_INVALID'");
        case Parser::PRIMITIVE_ANY:
            if(t->has_sign)throw std::runtime_error("unexpected "+std::string(t->sign?"signed":"unsigned"));
            return any_type_instance;
        case Parser::PRIMITIVE_INT:
            return (t->has_sign&&!t->sign)?unsigned_int_type_instance:int_type_instance;
        case Parser::PRIMITIVE_CHAR:
            return (t->has_sign&&!t->sign)?unsigned_char_type_instance:char_type_instance;
        case Parser::PRIMITIVE_FLOAT:
            if(t->has_sign)throw std::runtime_error("unexpected "+std::string(t->sign?"signed":"unsigned"));
            return float_type_instance;
        case Parser::PRIMITIVE_STRING:
            return string_type_instance;
        }
    }
    throw std::runtime_error("invalid type");
}

std::shared_ptr<Type> Type::from_vartype(DefaultFrame * context,std::shared_ptr<Parser::VarType> t){
    std::shared_ptr<Type> type=from_vartype_ignore_array(context,t);
    for(std::shared_ptr<Parser::Expression> e:t->array_sizes){
        if(e){
            if(e->type==Parser::EXPRESSION_TERM&&std::static_pointer_cast<Parser::ExpressionTerm>(e->contents)->type==Parser::EXPRESSION_TERM_LITERAL_INT){
                type=std::make_shared<ArrayType>(type,std::static_pointer_cast<Lexer::IntegerToken>(std::static_pointer_cast<Parser::ExpressionTerm>(e->contents)->contents_t)->get_integer());
            }else{
                throw std::runtime_error("invalid type for array size, must be integer literal");
            }
        }else{//[] array
            type=std::make_shared<ArrayType>(type,-1);
        }
    }
    return type;
}

bool Type::allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return is(self,other);
}

bool Type::has_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return allows_implicit_cast(self,other);
}

std::shared_ptr<Value> Type::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(is(self->get_type(),other)){
        return self;
    }
    throw std::runtime_error("illegal cast");
}

std::shared_ptr<Value> Type::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end){
    throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
}

std::shared_ptr<Value> Type::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end){
    throw MyExcept::SyntaxError(line_start,line_end,"operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
}

std::shared_ptr<Value> Type::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
}

std::shared_ptr<Value> Type::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    if(pre){
        throw std::runtime_error("invalid unary pre operator '"+get_op_str(op)+"'");
    }else{
        throw std::runtime_error("invalid unary post operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> Type::make_value(std::shared_ptr<Type> self){
    throw std::runtime_error("cannot make "+self->get_name()+" value");
}

std::shared_ptr<Variable> Type::make_variable(std::shared_ptr<Type> self,std::string name){
    throw std::runtime_error("cannot make "+self->get_name()+" variable");
}

void Type::check_variable_assignment(int op,std::shared_ptr<Value> self,int line_start,int line_end){
    switch(op){
    case SYMBOL_LEFT_SHIFT_ASSIGNMENT:
    case SYMBOL_RIGHT_SHIFT_ASSIGNMENT:
    case SYMBOL_BITWISE_AND_ASSIGNMENT:
    case SYMBOL_BITWISE_OR_ASSIGNMENT:
    case SYMBOL_BITWISE_XOR_ASSIGNMENT:
    case SYMBOL_PERCENT_ASSIGNMENT:
    case SYMBOL_PLUS_ASSIGNMENT:
    case SYMBOL_MINUS_ASSIGNMENT:
    case SYMBOL_MULTIPLY_ASSIGNMENT:
    case SYMBOL_DIVIDE_ASSIGNMENT:
    case SYMBOL_ASSIGNMENT:
        if(std::dynamic_pointer_cast<Variable>(self)==nullptr){
            throw MyExcept::SyntaxError(line_start,line_end,"operator '"+get_op_str(op)+"' only available for variables");
        }
        break;
    }
}
