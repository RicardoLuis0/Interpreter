#include "interpreter_for_statement.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_line_result_simple.h"

using namespace Interpreter;

ForStatement::ForStatement(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::ForStatement> stmt):pre(nullptr),condition(nullptr),inc(nullptr),code(std::make_shared<CodeBlock>(context.get(),stmt->code)){
    if(stmt->pre)pre=std::make_shared<Expression>(context,stmt->pre);
    if(stmt->condition)condition=std::make_shared<Expression>(context,stmt->condition);
    if(stmt->inc)inc=std::make_shared<Expression>(context,stmt->inc);
}

std::shared_ptr<LineResult> ForStatement::run(std::shared_ptr<ExecFrame> context){
    if(condition->get_type()->is_string())throw std::runtime_error("string is not valid condition");
    std::shared_ptr<Value> val;
    if(pre)pre->run(context);
    while(1){
        if(condition)val=condition->eval(context);
        if(!(condition)||(val->get_type()->is_int()&&std::dynamic_pointer_cast<IntValue>(val)->get()!=0)||(val->get_type()->is_float()&&std::dynamic_pointer_cast<FloatValue>(val)->get()!=0)){
            std::shared_ptr<LineResult> r=code->run(code->getContext(context.get()));
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
        if(inc)inc->run(context);
    }
}
