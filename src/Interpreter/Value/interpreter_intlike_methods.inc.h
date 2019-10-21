#ifndef PRINTF_CONTAINER_METHOD
#error Missing PRINTF_CONTAINER_METHOD
#endif

#ifndef PRINTF_CONTAINER_TYPE
#error Missing PRINTF_CONTAINER_TYPE
#endif

#ifndef CLASS_NAME
#error Missing CLASS_NAME
#endif

#ifndef VARIABLE_CLASS_NAME
#error Missing VARIABLE_CLASS_NAME
#endif

#ifndef VALUE_NAME
#error Missing VALUE_NAME
#endif

#ifndef VALUE_TYPE
#error Missing VALUE_TYPE
#endif

#ifndef VALUE_TYPE_TYPE
#error Missing VALUE_TYPE_TYPE
#endif

#ifdef _MSC_VER

//disable type conversion loss of data warning for MSVC

#pragma warning( disable : 4244 )

#endif

#define CHECK(type) (std::shared_ptr<type> val=std::dynamic_pointer_cast<type>(other))

#define CHECK2(type,name) (std::shared_ptr<type> name=std::dynamic_pointer_cast<type>(other))

#define MATH_OPERATION(type,method_operator) return std::make_shared<type>( VALUE_NAME method_operator val->get())

//simple math operator

//inttype math operator

//comparison operator

//assignment operator

//inttype assignment operator

#undef MATH_OPERATION
#undef UNSIGNED_CHECKS

using namespace Interpreter;

PRINTF_CONTAINER_TYPE CLASS_NAME::PRINTF_CONTAINER_METHOD(){
    return VALUE_NAME;
}


CLASS_NAME::CLASS_NAME(VALUE_TYPE val){
    VALUE_NAME=val;
}

CLASS_NAME::operator VALUE_TYPE&(){
    return VALUE_NAME;
}

VALUE_TYPE& CLASS_NAME::get(){
    return VALUE_NAME;
}

std::shared_ptr<Value> CLASS_NAME::clone(){
    return std::make_shared<CLASS_NAME>(VALUE_NAME);
}

std::shared_ptr<Variable> CLASS_NAME::clone_var(std::string new_name){
    return std::make_shared<VARIABLE_CLASS_NAME>(new_name,VALUE_NAME);
}

std::shared_ptr<Type> CLASS_NAME::get_type(){
    return Type::VALUE_TYPE_TYPE();
}

//simple math

#define METHOD_NAME add
#define OPERATOR +
#define OPERATOR_STRING "+"

#include "interpreter_intlike_simple_math_method.inc.h"

#define METHOD_NAME sub
#define OPERATOR -
#define OPERATOR_STRING "-"

#include "interpreter_intlike_simple_math_method.inc.h"

#define METHOD_NAME mul
#define OPERATOR *
#define OPERATOR_STRING "*"

#include "interpreter_intlike_simple_math_method.inc.h"

#define METHOD_NAME div
#define OPERATOR /
#define OPERATOR_STRING "/"

#include "interpreter_intlike_simple_math_method.inc.h"

//inttype math

#define METHOD_NAME mod
#define OPERATOR %
#define OPERATOR_STRING "%"

#include "interpreter_intlike_inttype_math_method.inc.h"

#define METHOD_NAME bitwise_and
#define OPERATOR &
#define OPERATOR_STRING "&"

#include "interpreter_intlike_inttype_math_method.inc.h"

#define METHOD_NAME bitwise_or
#define OPERATOR |
#define OPERATOR_STRING "|"

#include "interpreter_intlike_inttype_math_method.inc.h"

#define METHOD_NAME bitwise_xor
#define OPERATOR ^
#define OPERATOR_STRING "^"

#include "interpreter_intlike_inttype_math_method.inc.h"

//comparison

#define METHOD_NAME gt
#define OPERATOR >
#define OPERATOR_STRING ">"

#include "interpreter_intlike_comparison_method.inc.h"

#define METHOD_NAME lt
#define OPERATOR <
#define OPERATOR_STRING "<"

#include "interpreter_intlike_comparison_method.inc.h"

#define METHOD_NAME eq
#define OPERATOR ==
#define OPERATOR_STRING "=="

#include "interpreter_intlike_comparison_method.inc.h"

#define METHOD_NAME neq
#define OPERATOR !=
#define OPERATOR_STRING "!="

#include "interpreter_intlike_comparison_method.inc.h"

#define METHOD_NAME gt_eq
#define OPERATOR >=
#define OPERATOR_STRING ">="

#include "interpreter_intlike_comparison_method.inc.h"

#define METHOD_NAME lt_eq
#define OPERATOR <=
#define OPERATOR_STRING "<="

#include "interpreter_intlike_comparison_method.inc.h"

#define METHOD_NAME logical_and
#define OPERATOR &&
#define OPERATOR_STRING "&&"

#include "interpreter_intlike_comparison_method.inc.h"

#define METHOD_NAME logical_or
#define OPERATOR ||
#define OPERATOR_STRING "||"

#include "interpreter_intlike_comparison_method.inc.h"

//assignment

#define METHOD_NAME assign
#define OPERATOR =
#define OPERATOR_STRING "="

#include "interpreter_intlike_assignment_method.inc.h"

#define METHOD_NAME assign_add
#define OPERATOR +=
#define OPERATOR_STRING "+="

#include "interpreter_intlike_assignment_method.inc.h"

#define METHOD_NAME assign_sub
#define OPERATOR -=
#define OPERATOR_STRING "-="

#include "interpreter_intlike_assignment_method.inc.h"

#define METHOD_NAME assign_mul
#define OPERATOR *=
#define OPERATOR_STRING "*="

#include "interpreter_intlike_assignment_method.inc.h"

#define METHOD_NAME assign_div
#define OPERATOR /=
#define OPERATOR_STRING "/="

#include "interpreter_intlike_assignment_method.inc.h"

//inttype assignment


#define METHOD_NAME assign_mod
#define OPERATOR %=
#define OPERATOR_STRING "%="

#include "interpreter_intlike_inttype_assignment_method.inc.h"

#define METHOD_NAME assign_bitwise_and
#define OPERATOR &=
#define OPERATOR_STRING "&="

#include "interpreter_intlike_inttype_assignment_method.inc.h"

#define METHOD_NAME assign_bitwise_or
#define OPERATOR |=
#define OPERATOR_STRING "|="

#include "interpreter_intlike_inttype_assignment_method.inc.h"

#define METHOD_NAME assign_bitwise_xor
#define OPERATOR ^=
#define OPERATOR_STRING "^="

#include "interpreter_intlike_inttype_assignment_method.inc.h"

std::shared_ptr<Value> CLASS_NAME::unary_pre_plus(){
#if CLASS_NAME == UnsignedIntValue
	return std::make_shared<IntValue>(static_cast<int>(VALUE_NAME));
#elif CLASS_NAME == UnsignedCharValue
	return std::make_shared<CharValue>(static_cast<char>(VALUE_NAME));
#else
    return std::make_shared<CLASS_NAME>(VALUE_NAME);
#endif
}

std::shared_ptr<Value> CLASS_NAME::unary_pre_minus(){
#if CLASS_NAME == UnsignedIntValue
	return std::make_shared<IntValue>(-static_cast<int>(VALUE_NAME));
#elif CLASS_NAME == UnsignedCharValue
	return std::make_shared<CharValue>(-static_cast<char>(VALUE_NAME));
#else
    return std::make_shared<CLASS_NAME>(-VALUE_NAME);
#endif
}

std::shared_ptr<Value> CLASS_NAME::unary_pre_logical_not(){
    return std::make_shared<CLASS_NAME>(!VALUE_NAME);
}

std::shared_ptr<Value> CLASS_NAME::unary_pre_increment(){
    ++VALUE_NAME;
    return nullptr;
}

std::shared_ptr<Value> CLASS_NAME::unary_pre_decrement(){
    --VALUE_NAME;
    return nullptr;
}

std::shared_ptr<Value> CLASS_NAME::unary_post_increment(){
    return std::make_shared<CLASS_NAME>(VALUE_NAME++);
}

std::shared_ptr<Value> CLASS_NAME::unary_post_decrement(){
    return std::make_shared<CLASS_NAME>(VALUE_NAME--);
}
