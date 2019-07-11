#include "interpreter_util_defines_misc.h"
#include "interpreter_if_statement.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_line_result_simple.h"

using namespace Interpreter;

IfStatement::IfStatement(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::IfStatement> stmt):condition(std::make_shared<Expression>(context,stmt->condition)),code(std::make_shared<CodeBlock>(context.get(),stmt->code)){
    if(stmt->else_stmt){
        else_stmt=std::make_shared<CodeBlock>(context.get(),stmt->else_stmt->code);
    }
}

std::shared_ptr<LineResult> IfStatement::run(std::shared_ptr<ExecFrame> context){
    std::shared_ptr<Value> val=condition->eval(context);
    if(is_string(val->get_type()))throw std::runtime_error("string is not valid condition");
    bool do_code=false;
    if((is_int(val->get_type())&&std::dynamic_pointer_cast<IntValue>(val)->get())||(is_float(val->get_type())&&std::dynamic_pointer_cast<FloatValue>(val)->get())){
        do_code=true;
    }
    if(do_code){
        return code->run(context);
    }else{
        if(else_stmt){
            return else_stmt->run(context);
        }else{
            return std::make_shared<LineResultSimple>(ACTION_NONE);
        }
    }
}