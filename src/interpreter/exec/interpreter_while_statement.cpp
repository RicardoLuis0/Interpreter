#include "interpreter_while_statement.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_line_result_simple.h"

using namespace Interpreter;

WhileStatement::WhileStatement(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::WhileStatement> stmt):condition(std::make_shared<Expression>(context,stmt->condition)),code(std::make_shared<CodeBlock>(context.get(),stmt->code)){
    
}

std::shared_ptr<LineResult> WhileStatement::run(std::shared_ptr<ExecFrame> context){
    if(condition->get_type()->is_string())throw std::runtime_error("string is not valid condition");
    std::shared_ptr<Value> val;
    while(1){
        val=condition->eval(context);
        if((val->get_type()->is_int()&&std::dynamic_pointer_cast<IntValue>(val)->get())||(val->get_type()->is_float()&&std::dynamic_pointer_cast<FloatValue>(val)->get())){
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
    }
}
