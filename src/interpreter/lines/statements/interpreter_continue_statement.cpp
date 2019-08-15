#include "interpreter_continue_statement.h"
#include "interpreter_line_result_simple.h"

using namespace Interpreter;

std::shared_ptr<LineResult> ContinueStatement::run(ExecFrame * context){
    return std::make_shared<LineResultSimple>(ACTION_CONTINUE);
}
