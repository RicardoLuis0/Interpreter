#include "interpreter_expression.h"
#include "interpreter_util_defines_misc.h"
#include "symbols_keywords.h"

#include "parser_expression_group.h"
#include "parser_binary_operation.h"
#include "interpreter_line_result_simple.h"
#include "interpreter_expr_part_fn_call.h"
#include "interpreter_expr_part_var.h"
#include "interpreter_expr_part_value.h"
#include "string_token.h"
#include "integer_token.h"
#include "float_token.h"

using namespace Interpreter;

Expression::Expression(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::Expression> e){
    expression=get_expression(context,e);
}

std::shared_ptr<Parser::VarType> Expression::get_type(){
    return expression->get_type();
}

std::shared_ptr<ExprPart> Expression::get_expression(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::Expression> e){//NOTE maybe move this to parser and order the AST instead
    if(e->type==Parser::EXPRESSION_BINARY_OPERATION){
        std::shared_ptr<Parser::BinaryOperation> op(std::static_pointer_cast<Parser::BinaryOperation>(e->contents));
        return std::make_shared<ExprPartOp>(get_term(context,op->term1),op->binary_operator->get_symbol_type(),get_expression(context,op->term2));
    }else{
        return get_term(context,std::static_pointer_cast<Parser::ExpressionTerm>(e->contents));
    }
}

std::shared_ptr<ExprPart> Expression::get_term(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::ExpressionTerm> term){
    switch(term->type){
    case Parser::EXPRESSION_TERM_EXPRESSION_GROUP:
        return get_expression(context,std::static_pointer_cast<Parser::ExpressionGroup>(term->contents_p)->contents);
    case Parser::EXPRESSION_TERM_FUNCTION_CALL:
        return std::make_shared<ExprPartFnCall>(context,std::static_pointer_cast<Parser::FunctionCall>(term->contents_p));
    case Parser::EXPRESSION_TERM_IDENTIFIER:
        return std::make_shared<ExprPartVar>(context,std::static_pointer_cast<Lexer::WordToken>(term->contents_t)->get_literal());
    case Parser::EXPRESSION_TERM_LITERAL_INT:
        return ExprPartValue::from_int(int(std::static_pointer_cast<Lexer::IntegerToken>(term->contents_t)->get_integer()));
    case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
        return ExprPartValue::from_double(std::static_pointer_cast<Lexer::FloatToken>(term->contents_t)->get_float());
    case Parser::EXPRESSION_TERM_LITERAL_STRING:
        return std::make_shared<ExprPartValue>(std::static_pointer_cast<Lexer::StringToken>(term->contents_t)->get_string());
    case Parser::EXPRESSION_TERM_UNARY_OPERATION:
        //TODO Expression::add_term unary
        throw std::runtime_error("unimplemented Expression::add_term unary");
    default:
        throw std::runtime_error("unimplemented Expression term");
    }
}

std::shared_ptr<LineResult> Expression::run(std::shared_ptr<ExecFrame> context){
    eval(context);
    return std::make_shared<LineResultSimple>(ACTION_NONE);
}

std::shared_ptr<Value> Expression::eval(std::shared_ptr<ExecFrame> context){
    return expression->eval(context);
}
