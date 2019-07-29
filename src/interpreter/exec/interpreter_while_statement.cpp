#include "interpreter_while_statement.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_line_result_simple.h"
#include "interpreter_float_type.h"
#include "interpreter_int_type.h"
#include "interpreter_string_type.h"

using namespace Interpreter;

WhileStatement::WhileStatement(DefaultFrame * context,std::shared_ptr<Parser::WhileStatement> stmt):condition(std::make_shared<Expression>(context,stmt->condition)),code(std::make_shared<CodeBlock>(context,stmt->code)){
    
}

std::shared_ptr<LineResult> WhileStatement::run(ExecFrame * context){
    if(CHECKPTR(condition->get_type(),StringType))throw std::runtime_error("string is not valid condition");
    std::shared_ptr<Value> val;
    while(1){
        val=condition->eval(context);
        if((CHECKPTR(val->get_type(),IntType)&&std::dynamic_pointer_cast<IntValue>(val)->get())||(CHECKPTR(val->get_type(),FloatType)&&std::dynamic_pointer_cast<FloatValue>(val)->get())){
            std::shared_ptr<LineResult> r=code->run(code->getContext(context).get());
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
