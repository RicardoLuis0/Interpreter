#include "interpreter_util_defines_misc.h"
#include "interpreter_if_statement.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_line_result_simple.h"
#include "interpreter_float_type.h"
#include "interpreter_int_type.h"
#include "interpreter_string_type.h"

using namespace Interpreter;

IfStatement::IfStatement(DefaultFrame * context,std::shared_ptr<Parser::IfStatement> stmt):condition(std::make_shared<Expression>(context,stmt->condition)),code(std::make_shared<CodeBlock>(context,stmt->code)){
    if(stmt->else_stmt){
        else_stmt=std::make_shared<CodeBlock>(context,stmt->else_stmt->code);
    }
}

std::shared_ptr<LineResult> IfStatement::run(ExecFrame * context){
    std::shared_ptr<Value> val=condition->eval(context);
    if(CHECKPTR(val->get_type(),StringType))throw std::runtime_error("string is not valid condition");
    bool do_code=false;
    if((CHECKPTR(val->get_type(),IntType)&&std::dynamic_pointer_cast<IntValue>(val)->get())||(CHECKPTR(val->get_type(),FloatType)&&std::dynamic_pointer_cast<FloatValue>(val)->get())){
        do_code=true;
    }
    if(do_code){
        return code->run(code->getContext(context).get());
    }else{
        if(else_stmt){
            return else_stmt->run(else_stmt->getContext(context).get());
        }else{
            return std::make_shared<LineResultSimple>(ACTION_NONE);
        }
    }
}
