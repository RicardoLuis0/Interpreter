#include "interpreter_expression.h"
#include "interpreter_util_defines_misc.h"
#include "symbols_keywords.h"

#include "parser_expression_group.h"
#include "parser_binary_operation.h"
#include "interpreter_line_result_simple.h"
#include "interpreter_expr_part_fn_call.h"
#include "interpreter_expr_part_var.h"
#include "interpreter_expr_part_value.h"
#include "string_token.h"
#include "integer_token.h"
#include "float_token.h"

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

std::map<int,int> Expression::operator_precedence{
    {SYMBOL_ASSIGNMENT,11},
    {SYMBOL_EQUALS,5},
    {SYMBOL_NOT_EQUALS,5},
    {SYMBOL_GREATER,4},
    {SYMBOL_GREATER_EQUALS,4},
    {SYMBOL_LOWER,4},
    {SYMBOL_LOWER_EQUALS,4},
    {SYMBOL_PLUS,2},
    {SYMBOL_PLUS_ASSIGNMENT,11},
    {SYMBOL_MINUS,2},
    {SYMBOL_MINUS_ASSIGNMENT,11},
    {SYMBOL_MULTIPLY,1},
    {SYMBOL_MULTIPLY_ASSIGNMENT,11},
    {SYMBOL_DIVIDE,1},
    {SYMBOL_DIVIDE_ASSIGNMENT,11},
    {SYMBOL_LOGICAL_AND,9},
    {SYMBOL_LOGICAL_OR,10},
    {SYMBOL_BITWISE_AND,6},
    {SYMBOL_BITWISE_AND_ASSIGNMENT,11},
    {SYMBOL_BITWISE_OR,8},
    {SYMBOL_BITWISE_OR_ASSIGNMENT,11},
    {SYMBOL_BITWISE_XOR,7},
    {SYMBOL_BITWISE_XOR_ASSIGNMENT,11},
    {SYMBOL_LEFT_SHIFT,3},
    {SYMBOL_LEFT_SHIFT_ASSIGNMENT,11},
    {SYMBOL_RIGHT_SHIFT,3},
    {SYMBOL_RIGHT_SHIFT_ASSIGNMENT,11},
    {SYMBOL_PERCENT,1},
    {SYMBOL_PERCENT_ASSIGNMENT,11},
};

Expression::Expression(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::Expression> e){
    add_expression(context,e);
    type=check(context);
}

std::shared_ptr<Parser::VarType> Expression::get_type(){
    return type;
}

std::shared_ptr<Parser::VarType> Expression::get_type(std::shared_ptr<DefaultFrame> context,std::shared_ptr<ExprPart> ex){
    if(typeid(*ex)==typeid(ExprPartOp))throw std::runtime_error("invalid object type ExprPartOp for Expression::get_type");
    return ex->get_type(context);
}

void Expression::add_expression(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::Expression> e){
    std::stack<int> op_stack;
    //parse operator precedence using shunting yard, check for undefined functions/variables
    while(1){
        if(e->type==Parser::EXPRESSION_BINARY_OPERATION){
            std::shared_ptr<Parser::BinaryOperation> op(std::static_pointer_cast<Parser::BinaryOperation>(e->contents));
            int op_num=op->binary_operator->get_symbol_type();
            if(operator_precedence[op_num]==0){
                //unimplemented special handling
                e=op->term2;
            }else{
                add_term(context,op->term1);
                if(!MAP_HAS(operator_precedence,op_num))throw std::runtime_error("unknown operator");
                while(!op_stack.empty()&&operator_precedence[op_stack.top()]>=operator_precedence[op_num]){
                    expression.push(std::make_shared<ExprPartOp>(op_stack.top()));
                    op_stack.pop();
                }
                op_stack.push(op_num);
                e=op->term2;
            }
        }else if(e->type==Parser::EXPRESSION_TERM){
            add_term(context,std::static_pointer_cast<Parser::ExpressionTerm>(e->contents));
            while(!op_stack.empty()){
                expression.push(std::make_shared<ExprPartOp>(op_stack.top()));
                op_stack.pop();
            }
            break;
        }
    }
}

void Expression::add_term(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::ExpressionTerm> term){
    switch(term->type){
    case Parser::EXPRESSION_TERM_EXPRESSION_GROUP:
        add_expression(context,std::static_pointer_cast<Parser::ExpressionGroup>(term->contents_p)->contents);
        break;
    case Parser::EXPRESSION_TERM_FUNCTION_CALL:
        expression.push(std::make_shared<ExprPartFnCall>(context,std::static_pointer_cast<Parser::FunctionCall>(term->contents_p)));
        break;
    case Parser::EXPRESSION_TERM_IDENTIFIER:
        expression.push(std::make_shared<ExprPartVar>(context,std::static_pointer_cast<Lexer::WordToken>(term->contents_t)->get_literal()));
        break;
    case Parser::EXPRESSION_TERM_LITERAL_INT:
        expression.push(std::make_shared<ExprPartValue>(int(std::static_pointer_cast<Lexer::IntegerToken>(term->contents_t)->get_integer())));
        break;
    case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
        expression.push(std::make_shared<ExprPartValue>(std::static_pointer_cast<Lexer::FloatToken>(term->contents_t)->get_float()));
        break;
    case Parser::EXPRESSION_TERM_LITERAL_STRING:
        expression.push(std::make_shared<ExprPartValue>(std::static_pointer_cast<Lexer::StringToken>(term->contents_t)->get_string()));
        break;
    case Parser::EXPRESSION_TERM_UNARY_OPERATION:
        //TODO Expression::add_term unary
        throw std::runtime_error("unimplemented Expression::add_term unary");
        break;
    }
    //throw std::runtime_error("unimplemented Expression term");
}

std::shared_ptr<Parser::VarType> Expression::check(std::shared_ptr<DefaultFrame> context){
    std::stack<std::shared_ptr<ExprPart>> temp_stack=expression;
    std::shared_ptr<ExprPart> ex=temp_stack.top();
    temp_stack.pop();
    std::shared_ptr<Parser::VarType> temp_type;
    if(typeid(*ex)==typeid(ExprPartOp)){
        std::shared_ptr<ExprPartOp> op(std::static_pointer_cast<ExprPartOp>(ex));
        temp_type=check_op(context,temp_stack,op);
    }else{
        temp_type=get_type(context,ex);
    }
    if(temp_type&&temp_stack.size()!=0){//if the stack wasn't consumed to the end by check_op, or wasn't a single value
        throw std::runtime_error("invalid object state for Interpreter_Expression");
    }
    return temp_type;
}

std::shared_ptr<Parser::VarType> Expression::check_op(std::shared_ptr<DefaultFrame> context,std::stack<std::shared_ptr<ExprPart>> &st,std::shared_ptr<ExprPartOp> op){
    std::shared_ptr<ExprPart> ex2=st.top();//right term
    st.pop();
    std::shared_ptr<Parser::VarType> t2;
    if(typeid(*ex2)==typeid(ExprPartOp)){
        t2=check_op(context,st,std::static_pointer_cast<ExprPartOp>(ex2));
    }else{
        t2=ex2->get_type(context);
    }
    std::shared_ptr<ExprPart> ex1=st.top();//left term
    st.pop();
    std::shared_ptr<Parser::VarType> t1;
    if(typeid(*ex1)==typeid(ExprPartOp)){
        t1=check_op(context,st,std::static_pointer_cast<ExprPartOp>(ex1));
    }else{
        t1=ex1->get_type(context);
    }
    operator_class_t op_type=get_operator_class(op->op);
    switch(op_type){//string only allows '=', '+', '+=' and '=='
    case OP_MOD:
        if(!(is_int(t1)&&is_int(t2))){
            throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for modulus operator '"+get_op_str(op->op)+"'");
        }
        return t1;
    case OP_MOD_ASSIGNMENT:
        if(!(is_int(t1)&&is_int(t2))){
            throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for assignment operator '"+get_op_str(op->op)+"'");
        }
        goto assign_varcheck;
    case OP_BITWISE_ASSIGNMENT:
        if(!(is_int(t1)&&is_int(t2))){
            throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for assignment operator '"+get_op_str(op->op)+"'");
        }
        goto assign_varcheck;
    case OP_MATH_ASSIGNMENT:
        if(is_string(t1)||is_string(t2)){
            if(op->op!=SYMBOL_PLUS_ASSIGNMENT||!(is_string(t1)&&is_string(t2))){//if both aren't strings or the operator isn't +=
                throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for assignment operator '"+get_op_str(op->op)+"'");
            }
        }
        goto assign_varcheck;
    case OP_ASSIGNMENT:
        if(!(is_num(t1)&&is_num(t2))&&!(is_string(t1)&&is_string(t2))){
            throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for assignment operator '"+get_op_str(op->op)+"'");
        }
assign_varcheck:
        if(typeid(*ex1)!=typeid(ExprPartVar)){
            throw std::runtime_error("can't assign to non-variable type");
        }
        return t1;
    case OP_MATH:
        if(is_string(t1)||is_string(t2)){
            if(op->op==SYMBOL_PLUS&&is_string(t1)&&is_string(t2)){//if both are strings and the operator is +
                return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_STRING);
            }
            throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for math operator '"+get_op_str(op->op)+"'");
        }
        if(is_int(t2)&&is_int(t1)) return t2;
        if(is_float(t2)&&is_num(t1)) return t2;
        if(is_num(t2)&&is_float(t1)) return t1;
        throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for math operator '"+get_op_str(op->op)+"'");
    case OP_BITWISE:
        if(!(is_int(t1)&&is_int(t2))){
            throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for bitwise operator '"+get_op_str(op->op)+"'");
        }
        return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_INT);//bitwise always returns int
    case OP_LOGICAL:
        if(!(is_int(t1)&&is_int(t2))){
            throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for logical operator '"+get_op_str(op->op)+"'");
        }
        return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_INT);//logical always returns int
    case OP_EQUALITY:
        if(is_string(t1)!=is_string(t2)){//if one is a string and the other isn't, throw
            throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for equality operator '"+get_op_str(op->op)+"'");
        }
    case OP_COMPARISON:
        if(is_compatible(t1,t2)){
            return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_INT);//comparison always returns int
        }
        throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2)+" for comparison operator '"+get_op_str(op->op)+"'");
    default:
        break;
    }
    throw std::runtime_error("unknown operator '"+get_op_str(op->op)+"'");
}

std::shared_ptr<LineResult> Expression::run(std::shared_ptr<ExecFrame> context){
    eval(context);
    return std::make_shared<LineResultSimple>(ACTION_NONE);
}

std::shared_ptr<Value> Expression::eval(std::shared_ptr<ExecFrame> context){
    std::stack<std::shared_ptr<ExprPart>> temp_stack=expression;
    std::shared_ptr<ExprPart> ex=temp_stack.top();
    temp_stack.pop();
    if(typeid(*ex)==typeid(ExprPartOp)){
        std::shared_ptr<ExprPartOp> op(std::static_pointer_cast<ExprPartOp>(ex));
        return eval_op(context,temp_stack,op);
    }else{
        return ex->eval(context);
    }
}

std::shared_ptr<Value> Expression::eval_op(std::shared_ptr<ExecFrame> context,std::stack<std::shared_ptr<ExprPart>> &st,std::shared_ptr<ExprPartOp> op){
    std::shared_ptr<ExprPart> ex2=st.top();//right term
    st.pop();
    std::shared_ptr<Value> v2;
    if(typeid(*ex2)==typeid(ExprPartOp)){
        v2=eval_op(context,st,std::static_pointer_cast<ExprPartOp>(ex2));
    }else{
        v2=ex2->eval(context);
    }
    std::shared_ptr<ExprPart> ex1=st.top();//left term
    st.pop();
    std::shared_ptr<Value> v1;
    if(typeid(*ex1)==typeid(ExprPartOp)){
        v1=eval_op(context,st,std::static_pointer_cast<ExprPartOp>(ex1));
    }else{
        v1=ex1->eval(context);
    }
    switch(op->op){
    case SYMBOL_RIGHT_SHIFT_ASSIGNMENT:
    case SYMBOL_LEFT_SHIFT_ASSIGNMENT:
    case SYMBOL_LEFT_SHIFT:
    case SYMBOL_RIGHT_SHIFT:
        //TODO left,right shift operators and their assignments
        break;
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
    throw std::runtime_error("unimplemented operator '"+get_op_str(op->op)+"'");
}
