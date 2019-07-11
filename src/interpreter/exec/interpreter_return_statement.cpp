#include "interpreter_return_statement.h"
#include "interpreter_line_result_return.h"

using namespace Interpreter;

ReturnStatement::ReturnStatement(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::ReturnStatement> stmt):value(std::make_shared<Expression>(context,stmt->value)){
}

std::shared_ptr<LineResult> ReturnStatement::run(std::shared_ptr<ExecFrame> context){
    return std::make_shared<LineResultReturn>(value->eval(context));
}
