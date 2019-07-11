#include "interpreter_code_block.h"
#include "parser_expression_term.h"
#include "interpreter_expression.h"
#include "parser_binary_operation.h"
#include "symbols_keywords.h"
#include "interpreter_line_result_simple.h"
#include "interpreter_return_statement.h"
#include "interpreter_if_statement.h"
#include "interpreter_while_statement.h"
#include "interpreter_for_statement.h"
#include "interpreter_user_function.h"

using namespace Interpreter;

static void varDefCallbackCaller(void * ptr,std::shared_ptr<Parser::VariableDefinitionItem> vdef){
    ((CodeBlock*)ptr)->varDefCallback(vdef);
}

CodeBlock::CodeBlock(std::shared_ptr<DefaultFrame> frame,std::shared_ptr<Parser::CodeBlock> b):default_frame(frame){
    for(std::shared_ptr<Parser::Line> l : b->lines){
        addLine(l);
    }
}

CodeBlock::CodeBlock(UserFunction * func,std::shared_ptr<Parser::CodeBlock> b):CodeBlock(func->frame,b){
    
}

CodeBlock::CodeBlock(DefaultFrame * p,std::shared_ptr<Parser::CodeBlock> b):CodeBlock(std::make_shared<DefaultFrame>(p),b){
    
}

CodeBlock::CodeBlock(DefaultFrame * p,std::shared_ptr<Parser::Line> l):default_frame(std::make_shared<DefaultFrame>(p)){
    if(l->type==Parser::LINE_CODE_BLOCK){
        for(std::shared_ptr<Parser::Line> l : std::static_pointer_cast<Parser::CodeBlock>(l->contents)->lines){
            addLine(l);
        }
    }else{
        addLine(l);
    }
}

std::shared_ptr<LineResult> CodeBlock::run(std::shared_ptr<ExecFrame> context){
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
        code.push_back(std::make_shared<Expression>(default_frame,std::static_pointer_cast<Parser::Expression>(l->contents)));
        break;
    case Parser::LINE_DEFINITION:
        default_frame->add_definition(std::static_pointer_cast<Parser::Definition>(l->contents),false,varDefCallbackCaller,this);
        break;
    case Parser::LINE_EMPTY://do nothing
        break;
    }
}

void CodeBlock::addStatement(std::shared_ptr<Parser::Statement> stmt){
    switch(stmt->type){
    case Parser::STATEMENT_IF:
        code.push_back(std::make_shared<IfStatement>(default_frame,std::static_pointer_cast<Parser::IfStatement>(stmt->statement)));
        break;
    case Parser::STATEMENT_WHILE:
        code.push_back(std::make_shared<WhileStatement>(default_frame,std::static_pointer_cast<Parser::WhileStatement>(stmt->statement)));
        break;
    case Parser::STATEMENT_FOR:
        code.push_back(std::make_shared<ForStatement>(default_frame,std::static_pointer_cast<Parser::ForStatement>(stmt->statement)));
        break;
    case Parser::STATEMENT_RETURN:
        code.push_back(std::make_shared<ReturnStatement>(default_frame,std::static_pointer_cast<Parser::ReturnStatement>(stmt->statement)));
        break;
    }
}

void CodeBlock::varDefCallback(std::shared_ptr<Parser::VariableDefinitionItem> var){
    std::string name=var->name;
    if(var->value->type==Parser::EXPRESSION_TERM){
        switch(std::static_pointer_cast<Parser::ExpressionTerm>(var->value->contents)->type){
        case Parser::EXPRESSION_TERM_LITERAL_INT:
        case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
        case Parser::EXPRESSION_TERM_LITERAL_STRING:
            return;//don't add assignment if is literal, already handled by frame defaults
        default:
            break;
        }
    }
    code.push_back(std::make_shared<Expression>(default_frame,std::make_shared<Parser::Expression>(
            std::make_shared<Parser::BinaryOperation>(
                std::make_shared<Parser::ExpressionTerm>(std::make_shared<Lexer::WordToken>(0,var->name),Parser::EXPRESSION_TERM_IDENTIFIER),
                std::make_shared<Lexer::SymbolToken>(0,get_symbol_data(SYMBOL_ASSIGNMENT)),
                var->value),Parser::EXPRESSION_BINARY_OPERATION)));//add assignment operation if not a literal
}
