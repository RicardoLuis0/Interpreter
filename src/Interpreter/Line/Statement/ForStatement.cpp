#include "Interpreter/ForStatement.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "Interpreter/IntValue.h"
#include "Interpreter/FloatValue.h"
#include "Interpreter/LineResultSimple.h"
#include "Interpreter/StringType.h"
#include "Interpreter/IntType.h"
#include "Interpreter/FloatType.h"
#include "MyExcept/MyExcept.h"

using namespace Interpreter;

ForStatement::ForStatement(DefaultFrame * context,std::shared_ptr<Parser::ForStatement> stmt):
    Line(stmt->line_start),
    pre(nullptr),
    condition(nullptr),
    inc(nullptr),
    defFrame(stmt->vardef_pre?std::make_shared<DefaultFrame>(context,stmt->vardef_pre):nullptr),
    code(std::make_shared<CodeBlock>(defFrame?defFrame.get():context,stmt->code))
{
    if(stmt->pre)pre=std::make_shared<Expression>(context,stmt->pre);
    if(stmt->condition)condition=std::make_shared<Expression>(defFrame?defFrame.get():context,stmt->condition);
    if(stmt->inc)inc=std::make_shared<Expression>(defFrame?defFrame.get():context,stmt->inc);
    if(condition&&!condition->get_type()->allows_implicit_cast(condition->get_type(),Type::int_type()))throw MyExcept::SyntaxError(source_line,source_line,condition->get_type()->get_name()+" is not valid type for condition (must be convertible to int)");
}

std::shared_ptr<LineResult> ForStatement::run(ExecFrame * context){
    std::shared_ptr<Value> val;
    if(pre)pre->run(context);
    std::vector<std::shared_ptr<Variable>> vars;
    std::shared_ptr<ExecFrame> defFrameContext(std::make_shared<ExecFrame>(context,defFrame.get()));
    while(1){
        if(condition)val=condition->eval(defFrame?defFrameContext.get():context);
        bool do_code=false;
        try{
            do_code=!condition||std::dynamic_pointer_cast<IntValue>(val->get_type()->cast(val,Type::int_type()))->get()!=0;//if condition is null, treat it as always true
        }catch(std::runtime_error &e){
            throw MyExcept::InterpreterRuntimeError(source_line,"failed to cast "+val->get_type()->get_name()+" to int, condition must be convertible to int");
        }
        if(do_code){
            std::shared_ptr<LineResult> r=code->run((code->getContext(defFrame?defFrameContext.get():context)).get());
            switch(r->getAction()){
            case ACTION_BREAK:
                return std::make_shared<LineResultSimple>(ACTION_NONE);
            case ACTION_CONTINUE:
            case ACTION_NONE:
                break;
            default:
                return r;
            }
        }else{
            return std::make_shared<LineResultSimple>(ACTION_NONE);
        }
        if(inc)inc->run(defFrame?defFrameContext.get():context);
    }
}
