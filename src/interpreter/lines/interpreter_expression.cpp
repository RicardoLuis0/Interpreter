#include "interpreter_expression.h"
#include "interpreter_util_defines_misc.h"
#include "symbols_keywords.h"

#include "parser_expression_group.h"
#include "parser_binary_operation.h"
#include "interpreter_line_result_simple.h"
#include "interpreter_expr_part_fn_call.h"
#include "interpreter_expr_part_var.h"
#include "interpreter_expr_part_value.h"
#include "lexer_string_token.h"
#include "lexer_integer_token.h"
#include "lexer_char_token.h"
#include "lexer_float_token.h"
#include "parser_unary_operation.h"
#include "interpreter_expr_part_unary_op.h"

using namespace Interpreter;

Expression::Expression(DefaultFrame * context,std::shared_ptr<Parser::Expression> e):Line(e->line_start){
    expression=get_expression(context,e);
}

std::shared_ptr<Type> Expression::get_type(){
    return expression->get_type();
}

std::shared_ptr<Value> Expression::get_dummy_type(){
    return expression->get_dummy_type();
}

std::shared_ptr<ExprPart> Expression::get_expression(DefaultFrame * context,std::shared_ptr<Parser::Expression> e){
    if(e->type==Parser::EXPRESSION_BINARY_OPERATION){
        std::shared_ptr<Parser::BinaryOperation> op(std::static_pointer_cast<Parser::BinaryOperation>(e->contents));
        return std::make_shared<ExprPartOp>(get_term(context,op->term1),op->binary_operator->get_symbol_type(),get_expression(context,op->term2),e->line_start,e->line_end);
    }else{
        return get_term(context,std::static_pointer_cast<Parser::ExpressionTerm>(e->contents));
    }
}

std::shared_ptr<ExprPart> Expression::get_term(DefaultFrame * context,std::shared_ptr<Parser::ExpressionTerm> term){
    std::shared_ptr<ExprPart> expr=nullptr;
    switch(term->type){
    case Parser::EXPRESSION_TERM_EXPRESSION_GROUP:
        expr=get_expression(context,std::static_pointer_cast<Parser::ExpressionGroup>(term->contents_p)->contents);
        break;
    case Parser::EXPRESSION_TERM_FUNCTION_CALL:
        expr=std::make_shared<ExprPartFnCall>(context,std::static_pointer_cast<Parser::FunctionCall>(term->contents_p));
        break;
    case Parser::EXPRESSION_TERM_IDENTIFIER:
        expr=std::make_shared<ExprPartVar>(context,std::static_pointer_cast<Lexer::WordToken>(term->contents_t)->get_literal(),term->contents_t->line);
        break;
    case Parser::EXPRESSION_TERM_LITERAL_INT:
        expr=ExprPartValue::from_int(std::static_pointer_cast<Lexer::IntegerToken>(term->contents_t)->get_integer());
        break;
    case Parser::EXPRESSION_TERM_LITERAL_CHAR:
        expr=ExprPartValue::from_char(std::static_pointer_cast<Lexer::CharToken>(term->contents_t)->get_char());//make int value from char literal, TODO change to char value when it's implemented
        break;
    case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
        expr=ExprPartValue::from_double(std::static_pointer_cast<Lexer::FloatToken>(term->contents_t)->get_float());
        break;
    case Parser::EXPRESSION_TERM_LITERAL_STRING:
        expr=std::make_shared<ExprPartValue>(std::static_pointer_cast<Lexer::StringToken>(term->contents_t)->get_string());
        break;
    case Parser::EXPRESSION_TERM_UNARY_OPERATION:
        expr=std::make_shared<ExprPartUnaryOp>(get_term(context,std::static_pointer_cast<Parser::UnaryOperation>(term->contents_p)->term),std::static_pointer_cast<Parser::UnaryOperation>(term->contents_p)->unary_operator->get_symbol_type(),true,term->line_start,term->line_end);
        break;
    case Parser::EXPRESSION_TERM_LITERAL_TRUE:
        expr=ExprPartValue::from_int(1);
        break;
    case Parser::EXPRESSION_TERM_LITERAL_FALSE:
        expr=ExprPartValue::from_int(0);
        break;
    default:
        throw std::runtime_error("unimplemented Expression term type");//unreachable???
    }
    for(std::shared_ptr<Lexer::SymbolToken> t:term->unary_post_operators){
        expr=std::make_shared<ExprPartUnaryOp>(expr,t->get_symbol_type(),false,t->line,t->line);
    }
    for(std::shared_ptr<Parser::ParserResultPart> t:term->array_access){
        expr=std::make_shared<ExprPartOp>(expr,SYMBOL_SQUARE_BRACKET_OPEN,get_expression(context,std::static_pointer_cast<Parser::Expression>(t)),t->line_start,t->line_end);
    }
    return expr;
}

std::shared_ptr<LineResult> Expression::run(ExecFrame * context){
    eval(context);
    return std::make_shared<LineResultSimple>(ACTION_NONE);
}

std::shared_ptr<Value> Expression::eval(ExecFrame * context){
    return expression->eval(context);
}
