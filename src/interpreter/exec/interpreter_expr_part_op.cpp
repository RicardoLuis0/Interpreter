#include "interpreter_expr_part_op.h"
#include "symbols_keywords.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_expr_part_var.h"

using namespace Interpreter;

static std::string get_op_str(int op){
    return get_symbol_data(symbol_type_t(op)).name;
}

enum operator_class_t{
    OP_UNKNOWN,
    OP_ASSIGNMENT,
    OP_MATH,
    OP_MATH_ASSIGNMENT,
    OP_BITWISE,
    OP_BITWISE_ASSIGNMENT,
    OP_LOGICAL,
    OP_EQUALITY,
    OP_COMPARISON,
    OP_MOD,
    OP_MOD_ASSIGNMENT,
};

static operator_class_t get_operator_class(int op){
    switch(op){
    case SYMBOL_PERCENT:
        
        return OP_MOD;
        
    case SYMBOL_PERCENT_ASSIGNMENT:
        
        return OP_MOD_ASSIGNMENT;
        
    case SYMBOL_PLUS:
    case SYMBOL_MINUS:
    case SYMBOL_MULTIPLY:
    case SYMBOL_DIVIDE:
        
        return OP_MATH;
        
    case SYMBOL_ASSIGNMENT:
        
        return OP_ASSIGNMENT;
        
    case SYMBOL_PLUS_ASSIGNMENT:
    case SYMBOL_MINUS_ASSIGNMENT:
    case SYMBOL_MULTIPLY_ASSIGNMENT:
    case SYMBOL_DIVIDE_ASSIGNMENT:
        
        return OP_MATH_ASSIGNMENT;
        
    case SYMBOL_NOT_EQUALS:
    case SYMBOL_EQUALS:
        
        return OP_EQUALITY;
        
    case SYMBOL_GREATER:
    case SYMBOL_GREATER_EQUALS:
    case SYMBOL_LOWER:
    case SYMBOL_LOWER_EQUALS:
        
        return OP_COMPARISON;
        
    case SYMBOL_LEFT_SHIFT:
    case SYMBOL_RIGHT_SHIFT:
    case SYMBOL_BITWISE_AND:
    case SYMBOL_BITWISE_OR:
    case SYMBOL_BITWISE_XOR:
        
        return OP_BITWISE;
        
    case SYMBOL_LEFT_SHIFT_ASSIGNMENT:
    case SYMBOL_RIGHT_SHIFT_ASSIGNMENT:
    case SYMBOL_BITWISE_AND_ASSIGNMENT:
    case SYMBOL_BITWISE_OR_ASSIGNMENT:
    case SYMBOL_BITWISE_XOR_ASSIGNMENT:
        
        return OP_BITWISE_ASSIGNMENT;
        
    case SYMBOL_LOGICAL_AND:
    case SYMBOL_LOGICAL_OR:
        
        return OP_LOGICAL;
        
    default:
        
        return OP_UNKNOWN;
        
    }
}

ExprPartOp::ExprPartOp(std::shared_ptr<ExprPart> l,int i,std::shared_ptr<ExprPart> r):left(l),right(r),op(i){
    std::shared_ptr<Type> t1(left->get_type());
    std::shared_ptr<Type> t2(right->get_type());
    operator_class_t op_type=get_operator_class(op);
    switch(op_type){//string only allows '=', '+', '+=' and '=='
    case OP_MOD:
        if(!(t1->is_int()&&t2->is_int())){
            throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for modulus operator '"+get_op_str(op)+"'");
        }
        type=t1;
        break;
    case OP_MOD_ASSIGNMENT:
        if(!(t1->is_int()&&t2->is_int())){
            throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for assignment operator '"+get_op_str(op)+"'");
        }
        goto assign_varcheck;
    case OP_BITWISE_ASSIGNMENT:
        if(!(t2->is_int()&&t2->is_int())){
            throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for assignment operator '"+get_op_str(op)+"'");
        }
        goto assign_varcheck;
    case OP_MATH_ASSIGNMENT:
        if(t1->is_string()||t2->is_string()){
            if(op!=SYMBOL_PLUS_ASSIGNMENT||!(t1->is_string()&&t2->is_string())){//if both aren't strings or the operator isn't +=
                throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for assignment operator '"+get_op_str(op)+"'");
            }
        }
        goto assign_varcheck;
    case OP_ASSIGNMENT:
        if(!(t1->is_num()&&t2->is_num())&&!(t1->is_string()&&t2->is_string())){
            throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for assignment operator '"+get_op_str(op)+"'");
        }
assign_varcheck:
        if(typeid(*left)!=typeid(ExprPartVar)){
            throw std::runtime_error("can't assign to non-variable type");
        }
        type=t1;
        break;
    case OP_MATH:
        if(t1->is_string()||t2->is_string()){
            if(op==SYMBOL_PLUS&&t1->is_string()&&t2->is_string()){//if both are strings and the operator is +
                type=Type::primitive_type(PRIMITIVE_STRING);
                break;
            }
            throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for math operator '"+get_op_str(op)+"'");
        }
        if(t2->is_int()&&t1->is_int()){
            type=t2;
            break;
        }
        if(t2->is_float()&&t1->is_num()){
            type=t2;
            break;
        }
        if(t2->is_num()&&t1->is_float()){
            type=t1;
            break;
        }
        throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for math operator '"+get_op_str(op)+"'");
    case OP_BITWISE:
        if(!(t1->is_int()&&t2->is_int())){
            throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for bitwise operator '"+get_op_str(op)+"'");
        }
        type=Type::primitive_type(PRIMITIVE_INT);//bitwise always returns int
        break;
    case OP_LOGICAL:
        if(!(t1->is_int()&&t2->is_int())){
            throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for logical operator '"+get_op_str(op)+"'");
        }
        type=Type::primitive_type(PRIMITIVE_INT);//logical always returns int
        break;
    case OP_EQUALITY:
        if(t1->is_string()!=t2->is_string()){//if one is a string and the other isn't, throw
            throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for equality operator '"+get_op_str(op)+"'");
        }
        /* fall through */
    case OP_COMPARISON:
        if(t1->is_compatible(t2)){
            type=Type::primitive_type(PRIMITIVE_INT);//comparison always returns int
            break;
        }
        throw std::runtime_error("incompatible types "+t1->get_name()+" and "+t2->get_name()+" for comparison operator '"+get_op_str(op)+"'");
    default:
        throw std::runtime_error("unknown operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Type> ExprPartOp::get_type(){
    return type;
}

std::shared_ptr<Value> ExprPartOp::eval(std::shared_ptr<ExecFrame> context){
    std::shared_ptr<Value> v1=left->eval(context);
    std::shared_ptr<Value> v2=right->eval(context);
    switch(op){
    default:
    case SYMBOL_RIGHT_SHIFT_ASSIGNMENT:
    case SYMBOL_LEFT_SHIFT_ASSIGNMENT:
    case SYMBOL_LEFT_SHIFT:
    case SYMBOL_RIGHT_SHIFT:
        //TODO left,right shift operators and their assignments
        throw std::runtime_error("unimplemented operator '"+get_op_str(op)+"'");
    case SYMBOL_LOGICAL_AND:
        return v1->logical_and(v2);
    case SYMBOL_LOGICAL_OR:
        return v1->logical_or(v2);
    case SYMBOL_BITWISE_AND:
        return v1->bitwise_and(v2);
    case SYMBOL_BITWISE_OR:
        return v1->bitwise_or(v2);
    case SYMBOL_BITWISE_XOR:
        return v1->bitwise_xor(v2);
    case SYMBOL_BITWISE_XOR_ASSIGNMENT:
        v1->assign_bitwise_xor(v2);
        return v1;
    case SYMBOL_BITWISE_OR_ASSIGNMENT:
        v1->assign_bitwise_or(v2);
        return v1;
    case SYMBOL_BITWISE_AND_ASSIGNMENT:
        v1->assign_bitwise_and(v2);
        return v1;
    case SYMBOL_PLUS_ASSIGNMENT:
        v1->assign_add(v2);
        return v1;
    case SYMBOL_MINUS_ASSIGNMENT:
        v1->assign_sub(v2);
        return v1;
    case SYMBOL_MULTIPLY_ASSIGNMENT:
        v1->assign_mul(v2);
        return v1;
    case SYMBOL_DIVIDE_ASSIGNMENT:
        v1->assign_div(v2);
        return v1;
    case SYMBOL_PERCENT_ASSIGNMENT:
        v1->assign_mod(v2);
        return v1;
    case SYMBOL_ASSIGNMENT:
        v1->assign(v2);
        return v1;
    case SYMBOL_EQUALS:
        return v1->eq(v2);
    case SYMBOL_NOT_EQUALS:
        return v1->neq(v2);
    case SYMBOL_GREATER:
        return v1->gt(v2);
    case SYMBOL_GREATER_EQUALS:
        return v1->gt_eq(v2);
    case SYMBOL_LOWER:
        return v1->lt(v2);
    case SYMBOL_LOWER_EQUALS:
        return v1->lt_eq(v2);
    case SYMBOL_PLUS:
        return v1->add(v2);
    case SYMBOL_MINUS:
        return v1->sub(v2);
    case SYMBOL_MULTIPLY:
        return v1->mul(v2);
    case SYMBOL_DIVIDE:
        return v1->div(v2);
    case SYMBOL_PERCENT:
        return v1->mod(v2);
    }
}
