#include "interpreter_line_result_simple.h"

using namespace Interpreter;

LineResultSimple::LineResultSimple(LineResultAction_t act):action(act){
    
}

LineResultAction_t LineResultSimple::getAction(){
    return action;
}
