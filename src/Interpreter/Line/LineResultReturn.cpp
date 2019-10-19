#include "Interpreter/LineResultReturn.h"

using namespace Interpreter;

LineResultReturn::LineResultReturn(std::shared_ptr<Value> expr,int i):LineResultSimple(ACTION_RETURN),value(expr),line(i){
    
}

std::shared_ptr<Value> LineResultReturn::get(){
    return value;
}

int LineResultReturn::get_line(){
    return line;
}
