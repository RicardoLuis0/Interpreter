#include "Interpreter/ContinueStatement.h"
#include "Interpreter/LineResultSimple.h"

using namespace Interpreter;

ContinueStatement::ContinueStatement(int i):Line(i){
}

std::shared_ptr<LineResult> ContinueStatement::run(ExecFrame *){
    return std::make_shared<LineResultSimple>(ACTION_CONTINUE);
}
