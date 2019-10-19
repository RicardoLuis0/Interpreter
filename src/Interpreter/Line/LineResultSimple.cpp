#include "Interpreter/LineResultSimple.h"

using namespace Interpreter;

LineResultSimple::LineResultSimple(LineResultAction_t act):action(act){
    
}

LineResultAction_t LineResultSimple::getAction(){
    return action;
}
