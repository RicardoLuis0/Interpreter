#include "interpreter_for_statement.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_line_result_simple.h"

using namespace Interpreter;

ForStatement::ForStatement(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::ForStatement> stmt):pre(std::make_shared<Expression>(context,stmt->pre)),condition(std::make_shared<Expression>(context,stmt->condition)),inc(std::make_shared<Expression>(context,stmt->inc)),code(std::make_shared<CodeBlock>(context.get(),stmt->code)){
    
}

std::shared_ptr<LineResult> ForStatement::run(std::shared_ptr<ExecFrame> context){
    if(is_string(condition->get_type()))throw std::runtime_error("string is not valid condition");
    std::shared_ptr<Value> val;
    pre->run(context);
    while(1){
        val=condition->eval(context);
        if((is_int(val->get_type())&&std::dynamic_pointer_cast<IntValue>(val)->get())||(is_float(val->get_type())&&std::dynamic_pointer_cast<FloatValue>(val)->get())){
            std::shared_ptr<LineResult> r=code->run(context);
            switch(r->getAction()){
            case ACTION_BREAK:
                return std::make_shared<LineResultSimple>(ACTION_NONE);
            case ACTION_CONTINUE:
                continue;
            case ACTION_NONE:
                break;
            default:
                return r;
            }
        }else{
            return std::make_shared<LineResultSimple>(ACTION_NONE);
        }
        inc->run(context);
    }
}
