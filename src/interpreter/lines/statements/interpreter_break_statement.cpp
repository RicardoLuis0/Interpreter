#include "interpreter_break_statement.h"
#include "interpreter_line_result_simple.h"

using namespace Interpreter;

BreakStatement::BreakStatement(int i):Line(i){
}

std::shared_ptr<LineResult> BreakStatement::run(ExecFrame * context){
    return std::make_shared<LineResultSimple>(ACTION_BREAK);
}
