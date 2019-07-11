#include "interpreter_line_result_return.h"

using namespace Interpreter;

LineResultReturn::LineResultReturn(std::shared_ptr<Expression> expr):LineResultSimple(ACTION_RETURN),value(expr){
    
}

std::shared_ptr<Value> LineResultReturn::eval(std::shared_ptr<ExecFrame> context){
    return value->eval(context);
}
