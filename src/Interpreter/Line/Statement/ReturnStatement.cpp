#include "Interpreter/ReturnStatement.h"
#include "Interpreter/LineResultReturn.h"
#include "Interpreter/UserFunction.h"
#include "MyExcept/MyExcept.h"

using namespace Interpreter;

ReturnStatement::ReturnStatement(DefaultFrame * context,std::shared_ptr<Parser::ReturnStatement> stmt):Line(stmt->line_start),value(nullptr),line(stmt->line_start){
    DefaultFrame * func_frame=context;
    while(!(func_frame->is_function)){
        if(func_frame->is_simple){
            break;
        }
        if(func_frame->parent==nullptr&&!func_frame->is_simple){
            throw MyExcept::SyntaxError(source_line,source_line,"return statement called outside of a function (HOW\?\?\?)");//shouldn't be possible, EVER
        }
        func_frame=func_frame->parent;
    }
    if(stmt->value){
       value=std::make_shared<Expression>(context,stmt->value);
    }
    if(func_frame->is_simple){
        if(value&&!value->get_type()->allows_implicit_cast(value->get_type(),Type::int_type())){
            throw MyExcept::SyntaxError(source_line,source_line,"in function "+func_frame->self_function->get_name()+"(...), cannot "+((value->get_type()->has_cast(value->get_type(),Type::int_type()))?"implicitly ":"")+"cast "+value->get_type()->get_name()+" to "+Type::int_type()->get_name());
        }
    }else if(func_frame->self_function->get_type()->is(func_frame->self_function->get_type(),Type::void_type())){
        if(value){
            throw MyExcept::SyntaxError(source_line,source_line,"in function "+func_frame->self_function->get_name()+"(...), void function cannot return a value");
        }
    }else if(value){
        if(!value->get_type()->allows_implicit_cast(value->get_type(),func_frame->self_function->get_type())){
            throw MyExcept::SyntaxError(source_line,source_line,"in function "+func_frame->self_function->get_name()+"(...), cannot "+((value->get_type()->has_cast(value->get_type(),func_frame->self_function->get_type()))?"implicitly ":"")+"cast "+value->get_type()->get_name()+" to "+func_frame->self_function->get_type()->get_name());
        }
    }else{
        throw MyExcept::SyntaxError(source_line,source_line,"in function "+func_frame->self_function->get_name()+"(...), return statement missing return value");
    }
}

std::shared_ptr<LineResult> ReturnStatement::run(ExecFrame * context){
    return std::make_shared<LineResultReturn>(value?value->eval(context):nullptr,line);
}
