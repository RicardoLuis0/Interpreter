#include "interpreter_util_defines_misc.h"
#include "interpreter_if_statement.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_line_result_simple.h"
#include "interpreter_float_type.h"
#include "interpreter_int_type.h"
#include "interpreter_string_type.h"
#include "my_except.h"

using namespace Interpreter;

IfStatement::IfStatement(DefaultFrame * context,std::shared_ptr<Parser::IfStatement> stmt):Line(stmt->line_start),condition(std::make_shared<Expression>(context,stmt->condition)),code(std::make_shared<CodeBlock>(context,stmt->code)){
    if(stmt->else_stmt){
        else_stmt=std::make_shared<CodeBlock>(context,stmt->else_stmt->code);
    }
    if(!condition->get_type()->allows_implicit_cast(condition->get_type(),Type::int_type()))throw MyExcept::SyntaxError(source_line,source_line,condition->get_type()->get_name()+" is not valid type for condition (must be convertible to int)");
}

std::shared_ptr<LineResult> IfStatement::run(ExecFrame * context){
    std::shared_ptr<Value> val=condition->eval(context);
    bool do_code=false;
    try{
        do_code=std::dynamic_pointer_cast<IntValue>(val->get_type()->cast(val,Type::int_type()))->get()!=0;
    }catch(std::runtime_error &e){
        throw MyExcept::InterpreterRuntimeError(source_line,"failed to cast "+val->get_type()->get_name()+" to int, condition must be convertible to int");
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
