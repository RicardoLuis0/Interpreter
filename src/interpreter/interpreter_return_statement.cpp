#include "interpreter_return_statement.h"
#include "interpreter_line_result_return.h"

using namespace Interpreter;

ReturnStatement::ReturnStatement(DefaultFrame * context,std::shared_ptr<Parser::ReturnStatement> stmt):value(std::make_shared<Expression>(context,stmt->value)){
}

std::shared_ptr<LineResult> ReturnStatement::run(ExecFrame * context){
    return std::make_shared<LineResultReturn>(value->eval(context));
}
