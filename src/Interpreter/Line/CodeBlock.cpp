#include "Interpreter/CodeBlock.h"
#include "Parser/ExpressionTerm.h"
#include "Interpreter/Expression.h"
#include "Parser/BinaryOperation.h"
#include "symbols_keywords.h"
#include "Interpreter/LineResultSimple.h"
#include "Interpreter/ReturnStatement.h"
#include "Interpreter/IfStatement.h"
#include "Interpreter/BreakStatement.h"
#include "Interpreter/ContinueStatement.h"
#include "Interpreter/WhileStatement.h"
#include "Interpreter/ForStatement.h"
#include "Interpreter/UserFunction.h"
#include "Interpreter/ArrayType.h"
#include "Interpreter/ExprPartInitVLA.h"

using namespace Interpreter;

static void varDefCallbackCaller(void * ptr,std::shared_ptr<Parser::VariableDefinitionItem> vdef,std::shared_ptr<Type> type,bool vla){
    static_cast<CodeBlock*>(ptr)->varDefCallback(vdef,type,vla);
}

CodeBlock::CodeBlock(std::shared_ptr<DefaultFrame> frame,std::shared_ptr<Parser::CodeBlock> b):Line(b->line_start),default_frame(frame){
    for(std::shared_ptr<Parser::Line> l : b->lines){
        addLine(l);
    }
}

CodeBlock::CodeBlock(UserFunction * func,std::shared_ptr<Parser::CodeBlock> b):CodeBlock(func->frame,b){
    
}

CodeBlock::CodeBlock(DefaultFrame * p,std::shared_ptr<Parser::CodeBlock> b):CodeBlock(std::make_shared<DefaultFrame>(p),b){
    
}

CodeBlock::CodeBlock(DefaultFrame * p,std::shared_ptr<Parser::Line> l):Line(l->line_start),default_frame(std::make_shared<DefaultFrame>(p)){
    if(l->type==Parser::LINE_CODE_BLOCK){
        std::shared_ptr<Parser::CodeBlock> b(std::static_pointer_cast<Parser::CodeBlock>(l->contents));
        for(std::shared_ptr<Parser::Line> bl : b->lines){
            addLine(bl);
        }
    }else{
        addLine(l);
    }
}

std::shared_ptr<LineResult> CodeBlock::run(ExecFrame * context){
    for(std::shared_ptr<Line> l:code){
        std::shared_ptr<LineResult> result=l->run(context);
        if(result->getAction()!=ACTION_NONE)return result;
    }
    return std::make_shared<LineResultSimple>(ACTION_NONE);
}

void CodeBlock::addLine(std::shared_ptr<Parser::Line> l){
    switch(l->type){
    case Parser::LINE_CODE_BLOCK:
        code.push_back(std::make_shared<CodeBlock>(default_frame.get(),std::static_pointer_cast<Parser::CodeBlock>(l->contents)));
        break;
    case Parser::LINE_STATEMENT:
        addStatement(std::static_pointer_cast<Parser::Statement>(l->contents));
        break;
    case Parser::LINE_EXPRESSION:
        code.push_back(std::make_shared<Expression>(default_frame.get(),std::static_pointer_cast<Parser::Expression>(l->contents)));
        break;
    case Parser::LINE_DEFINITION:
        default_frame->add_definition(std::static_pointer_cast<Parser::Definition>(l->contents),false,varDefCallbackCaller,static_cast<void*>(this));
        break;
    case Parser::LINE_EMPTY://do nothing
        break;
    }
}

void CodeBlock::addStatement(std::shared_ptr<Parser::Statement> stmt){
    switch(stmt->type){
    case Parser::STATEMENT_IF:
        code.push_back(std::make_shared<IfStatement>(default_frame.get(),std::static_pointer_cast<Parser::IfStatement>(stmt->statement)));
        break;
    case Parser::STATEMENT_WHILE:
        code.push_back(std::make_shared<WhileStatement>(default_frame.get(),std::static_pointer_cast<Parser::WhileStatement>(stmt->statement)));
        break;
    case Parser::STATEMENT_FOR:
        code.push_back(std::make_shared<ForStatement>(default_frame.get(),std::static_pointer_cast<Parser::ForStatement>(stmt->statement)));
        break;
    case Parser::STATEMENT_RETURN:
        code.push_back(std::make_shared<ReturnStatement>(default_frame.get(),std::static_pointer_cast<Parser::ReturnStatement>(stmt->statement)));
        break;
    case Parser::STATEMENT_BREAK:
        code.push_back(std::make_shared<BreakStatement>(stmt->line_start));
        break;
    case Parser::STATEMENT_CONTINUE:
        code.push_back(std::make_shared<ContinueStatement>(stmt->line_start));
        break;
    }
}

std::shared_ptr<ExecFrame> CodeBlock::getContext(ExecFrame * parent){
    return std::make_shared<ExecFrame>(parent,default_frame.get());
}

void CodeBlock::varDefCallback(std::shared_ptr<Parser::VariableDefinitionItem> var,std::shared_ptr<Type> t,bool vla){
    if(vla){
        auto arr=std::dynamic_pointer_cast<ArrayType>(t);
        code.push_back(std::make_shared<Expression>(std::make_shared<ExprPartInitVLA>(arr,var->name),-1));
    }
    if(var->value){
        code.push_back(default_frame->vardefitem_to_assignment(var));
    }
}
