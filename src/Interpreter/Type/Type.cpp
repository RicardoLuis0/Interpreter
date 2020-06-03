#include "Interpreter/Type.h"
#include "Interpreter/AnyType.h"
#include "Interpreter/TypeType.h"
#include "Interpreter/VoidType.h"
#include "Interpreter/CharType.h"
#include "Interpreter/UnsignedCharType.h"
#include "Interpreter/IntType.h"
#include "Interpreter/UnsignedIntType.h"
#include "Interpreter/FloatType.h"
#include "Interpreter/StringType.h"
#include "Interpreter/ArrayType.h"
#include "Interpreter/PointerType.h"
#include "Interpreter/PointerValue.h"
#include "Interpreter/DummyValue.h"
#include "Interpreter/Variable.h"
#include "Interpreter/DefaultFrame.h"
#include "Parser/Expression.h"
#include "Parser/ExpressionTerm.h"
#include "Lexer/IntegerToken.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "Interpreter/Expression.h"
#include "Interpreter/ReferenceType.h"
#include "Interpreter/ReferenceVariable.h"
#include "MyExcept/MyExcept.h"

using namespace Interpreter;

std::shared_ptr<Type> Type::true_any_type_instance(std::make_shared<AnyType>(false,true));
std::shared_ptr<Type> Type::any_type_instance(std::make_shared<AnyType>());
std::shared_ptr<Type> Type::type_type_instance(std::make_shared<TypeType>());
std::shared_ptr<Type> Type::void_type_instance(std::make_shared<VoidType>());
std::shared_ptr<Type> Type::char_type_instance(std::make_shared<CharType>());
std::shared_ptr<Type> Type::unsigned_char_type_instance(std::make_shared<UnsignedCharType>());
std::shared_ptr<Type> Type::int_type_instance(std::make_shared<IntType>());
std::shared_ptr<Type> Type::unsigned_int_type_instance(std::make_shared<UnsignedIntType>());
std::shared_ptr<Type> Type::float_type_instance(std::make_shared<FloatType>());
std::shared_ptr<Type> Type::string_type_instance(std::make_shared<StringType>());

std::shared_ptr<Type> Type::const_true_any_type_instance(std::make_shared<AnyType>(true,true));
std::shared_ptr<Type> Type::const_any_type_instance(std::make_shared<AnyType>(true));
std::shared_ptr<Type> Type::const_type_type_instance(std::make_shared<TypeType>(true));
std::shared_ptr<Type> Type::const_void_type_instance(std::make_shared<VoidType>(true));
std::shared_ptr<Type> Type::const_char_type_instance(std::make_shared<CharType>(true));
std::shared_ptr<Type> Type::const_unsigned_char_type_instance(std::make_shared<UnsignedCharType>(true));
std::shared_ptr<Type> Type::const_int_type_instance(std::make_shared<IntType>(true));
std::shared_ptr<Type> Type::const_unsigned_int_type_instance(std::make_shared<UnsignedIntType>(true));
std::shared_ptr<Type> Type::const_float_type_instance(std::make_shared<FloatType>(true));
std::shared_ptr<Type> Type::const_string_type_instance(std::make_shared<StringType>(true));

Type::Type(bool b):is_const(b){
}

std::shared_ptr<Type> Type::true_any_type(bool is_const){
    return is_const?const_true_any_type_instance:true_any_type_instance;
}

std::shared_ptr<Type> Type::any_type(bool is_const){
    return is_const?const_any_type_instance:any_type_instance;
}

std::shared_ptr<Type> Type::type_type(bool is_const){
    return is_const?const_type_type_instance:type_type_instance;
}

std::shared_ptr<Type> Type::void_type(bool is_const){
    return is_const?const_void_type_instance:void_type_instance;
}

std::shared_ptr<Type> Type::char_type(bool is_const){
    return is_const?const_char_type_instance:char_type_instance;
}

std::shared_ptr<Type> Type::unsigned_char_type(bool is_const){
    return is_const?const_unsigned_char_type_instance:unsigned_char_type_instance;
}

std::shared_ptr<Type> Type::int_type(bool is_const){
    return is_const?const_int_type_instance:int_type_instance;
}

std::shared_ptr<Type> Type::unsigned_int_type(bool is_const){
    return is_const?const_unsigned_int_type_instance:unsigned_int_type_instance;
}

std::shared_ptr<Type> Type::float_type(bool is_const){
    return is_const?const_float_type_instance:float_type_instance;
}

std::shared_ptr<Type> Type::string_type(bool is_const){
    return is_const?const_string_type_instance:string_type_instance;
}

std::shared_ptr<Type> Type::pointer_type(std::shared_ptr<Type> type,bool is_const){
    return std::make_shared<PointerType>(type,is_const);
}

bool Type::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    if(auto ref=std::dynamic_pointer_cast<ReferenceType>(other)){
        return is(self,ref->get_type())&&!(self->get_const()&&!other->get_const());//a const type isn't a non-const reference
    }else{
        return false;
    }
}

std::shared_ptr<Type> Type::from_vartype_ignore_array(DefaultFrame * context,std::shared_ptr<Parser::VarType> t){
    switch(t->type){
    case Parser::VARTYPE_DECLTYPE:
        return Expression(context,t->decltype_expr).get_type();
    case Parser::VARTYPE_VOID:
        if(t->has_sign)throw std::runtime_error("unexpected "+std::string(t->sign?"signed":"unsigned"));
        return void_type(t->is_const);
    case Parser::VARTYPE_IDENTIFIER:
        throw std::runtime_error("classes/structs/typedefs/etc not implemented yet");
    case Parser::VARTYPE_PRIMITIVE:
        switch(t->primitive){
        default:
            throw std::runtime_error("Type::from_vartype_ignore_array() unkown primitive value");
        case Parser::PRIMITIVE_INVALID:
            throw MyExcept::SyntaxError(t->line_start,t->line_end,"invalid primitive value 'PRIMITIVE_INVALID'");
        case Parser::PRIMITIVE_ANY:
            if(t->has_sign)throw std::runtime_error("unexpected "+std::string(t->sign?"signed":"unsigned"));
            return any_type(t->is_const);
        case Parser::PRIMITIVE_TYPE:
            if(t->has_sign)throw std::runtime_error("unexpected "+std::string(t->sign?"signed":"unsigned"));
            return type_type(t->is_const);
        case Parser::PRIMITIVE_INT:
            return (t->has_sign&&!t->sign)?unsigned_int_type(t->is_const):int_type(t->is_const);
        case Parser::PRIMITIVE_CHAR:
            return (t->has_sign&&!t->sign)?unsigned_char_type(t->is_const):char_type(t->is_const);
        case Parser::PRIMITIVE_FLOAT:
            if(t->has_sign)throw std::runtime_error("unexpected "+std::string(t->sign?"signed":"unsigned"));
            return float_type(t->is_const);
        case Parser::PRIMITIVE_STRING:
            if(t->has_sign)throw std::runtime_error("unexpected "+std::string(t->sign?"signed":"unsigned"));
            return string_type(t->is_const);
        case Parser::PRIMITIVE_POINTER:
            if(t->has_sign)throw std::runtime_error("unexpected "+std::string(t->sign?"signed":"unsigned"));
            return pointer_type(t->extra?from_vartype(context,t->extra):void_type(),t->is_const);
        }
    }
    throw std::runtime_error("invalid type");
}

std::shared_ptr<Type> Type::from_vartype(DefaultFrame * context,std::shared_ptr<Parser::VarType> t){
    std::shared_ptr<Type> type=from_vartype_ignore_array(context,t);
    for(std::shared_ptr<Parser::Expression> e:t->array_sizes){
        if(e){
            if(e->type==Parser::EXPRESSION_TERM&&std::static_pointer_cast<Parser::ExpressionTerm>(e->contents)->type==Parser::EXPRESSION_TERM_LITERAL_INT){
                int v=std::static_pointer_cast<Lexer::IntegerToken>(std::static_pointer_cast<Parser::ExpressionTerm>(e->contents)->contents_t)->get_integer();
                if(v<=0)throw std::runtime_error("invalid size for array");
                type=std::make_shared<ArrayType>(type,v);
            }else{
                auto expr=std::make_shared<Expression>(context,e);
                if(expr->get_type()->allows_implicit_cast(expr->get_type(),int_type())){
                    type=std::make_shared<ArrayType>(type,expr);
                }else{
                    throw std::runtime_error("invalid type for array size, must be conversible to integer");
                }
            }
        }else{//[] array
            type=std::make_shared<ArrayType>(type,-1);
        }
    }
    return type;
}

bool Type::allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return CHECKPTR(other,AnyType)||is(self,other);
}

bool Type::has_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return allows_implicit_cast(self,other);
}

std::shared_ptr<Value> Type::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(is(self->get_type(),other)){
        return self;
    }
    throw std::runtime_error("illegal cast from "+self->get_type()->get_name()+" to "+other->get_name());
}

std::shared_ptr<Value> Type::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end){
    throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
}

std::shared_ptr<Value> Type::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end){
    if(pre){
        if(op==SYMBOL_BITWISE_AND){
            if(std::dynamic_pointer_cast<Variable>(self)==nullptr){
                throw MyExcept::SyntaxError(line_start,line_end,"can't get address of non-variable");//technically possible but nah
            }else if(auto dummy=std::dynamic_pointer_cast<DummyValue>(self)){
                if(auto ref=std::dynamic_pointer_cast<ReferenceType>(dummy->get_type())){
                    return std::make_shared<DummyValue>(pointer_type(ref->get_type()));//'&' on references returns pointer to original value, not to reference
                }
            }
            return std::make_shared<DummyValue>(pointer_type(self->get_type()));
        }
        throw MyExcept::SyntaxError(line_start,line_end,"unary pre operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
    }else{
        throw MyExcept::SyntaxError(line_start,line_end,"unary post operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
    }
}

std::shared_ptr<Value> Type::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
}

std::shared_ptr<Value> Type::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    if(pre){
        if(op==SYMBOL_BITWISE_AND){
            if(auto ref=std::dynamic_pointer_cast<ReferenceVariable>(self)){
                return std::make_shared<PointerValue>(std::dynamic_pointer_cast<PointerType>(pointer_type(ref->get_orig_type())),ref->get_value());//'&' on references returns pointer to original value, not to reference
            }
            return std::make_shared<PointerValue>(std::dynamic_pointer_cast<PointerType>(pointer_type(self->get_type())),self);
        }
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

bool Type::get_const(){
    return is_const;
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
        if(is_const)throw MyExcept::SyntaxError(line_start,line_end,"operator '"+get_op_str(op)+"' unavailable for constant variables");
        break;
    }
}
