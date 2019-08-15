#include "interpreter_line_result_return.h"

using namespace Interpreter;

LineResultReturn::LineResultReturn(std::shared_ptr<Value> expr):LineResultSimple(ACTION_RETURN),value(expr){
    
}

std::shared_ptr<Value> LineResultReturn::get(){
    return value;
}
