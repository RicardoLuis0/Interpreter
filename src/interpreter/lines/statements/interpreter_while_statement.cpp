#include "interpreter_while_statement.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_line_result_simple.h"
#include "interpreter_float_type.h"
#include "interpreter_int_type.h"
#include "interpreter_string_type.h"
#include "my_except.h"

using namespace Interpreter;

WhileStatement::WhileStatement(DefaultFrame * context,std::shared_ptr<Parser::WhileStatement> stmt):Line(stmt->line_start),condition(std::make_shared<Expression>(context,stmt->condition)),code(std::make_shared<CodeBlock>(context,stmt->code)){
    if(!condition->get_type()->allows_implicit_cast(condition->get_type(),Type::int_type()))throw MyExcept::SyntaxError(source_line,source_line,condition->get_type()->get_name()+" is not valid type for condition (must be convertible to int)");
}

std::shared_ptr<LineResult> WhileStatement::run(ExecFrame * context){
    std::shared_ptr<Value> val;
    while(1){
        val=condition->eval(context);
        bool do_code=false;
        try{
            do_code=std::dynamic_pointer_cast<IntValue>(val->get_type()->cast(val,Type::int_type()))->get()!=0;
        }catch(std::runtime_error &e){
            throw MyExcept::InterpreterRuntimeError(source_line,"failed to cast "+val->get_type()->get_name()+" to int, condition must be convertible to int");
        }
        if(do_code){
            std::shared_ptr<LineResult> r=code->run(code->getContext(context).get());
            switch(r->getAction()){
            case ACTION_BREAK:
                return std::make_shared<LineResultSimple>(ACTION_NONE);
            case ACTION_CONTINUE:
                break;
            case ACTION_NONE:
                break;
            default:
                return r;
            }
        }else{
            return std::make_shared<LineResultSimple>(ACTION_NONE);
        }
    }
}
