#include "Interpreter/BreakStatement.h"
#include "Interpreter/LineResultSimple.h"

using namespace Interpreter;

BreakStatement::BreakStatement(int i):Line(i){
}

std::shared_ptr<LineResult> BreakStatement::run(ExecFrame * context){
    return std::make_shared<LineResultSimple>(ACTION_BREAK);
}
