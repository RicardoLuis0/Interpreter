#include "interpreter_for_statement.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_line_result_simple.h"
#include "interpreter_string_type.h"
#include "interpreter_int_type.h"
#include "interpreter_float_type.h"

using namespace Interpreter;

ForStatement::ForStatement(DefaultFrame * context,std::shared_ptr<Parser::ForStatement> stmt):
    pre(nullptr),
    condition(nullptr),
    inc(nullptr),
    defFrame(stmt->vardef_pre?std::make_shared<DefaultFrame>(context,stmt->vardef_pre):nullptr),
    code(std::make_shared<CodeBlock>(defFrame?defFrame.get():context,stmt->code))
{
    if(stmt->pre)pre=std::make_shared<Expression>(context,stmt->pre);
    if(stmt->condition)condition=std::make_shared<Expression>(defFrame?defFrame.get():context,stmt->condition);
    if(stmt->inc)inc=std::make_shared<Expression>(defFrame?defFrame.get():context,stmt->inc);
}

std::shared_ptr<LineResult> ForStatement::run(ExecFrame * context){
    if(CHECKPTR(condition->get_type(),StringType))throw std::runtime_error("string is not valid condition");
    std::shared_ptr<Value> val;
    if(pre)pre->run(context);
    std::vector<std::shared_ptr<Variable>> vars;
    std::shared_ptr<ExecFrame> defFrameContext(std::make_shared<ExecFrame>(context,defFrame.get()));
    while(1){
        if(condition)val=condition->eval(defFrame?defFrameContext.get():context);
        if(!(condition)||(CHECKPTR(val->get_type(),IntType)&&std::dynamic_pointer_cast<IntValue>(val)->get()!=0)||(CHECKPTR(val->get_type(),FloatType)&&std::dynamic_pointer_cast<FloatValue>(val)->get()!=0)){
            std::shared_ptr<LineResult> r=code->run((code->getContext(defFrame?defFrameContext.get():context)).get());
            switch(r->getAction()){
            case ACTION_BREAK:
                return std::make_shared<LineResultSimple>(ACTION_NONE);
            case ACTION_CONTINUE:
                continue;
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
