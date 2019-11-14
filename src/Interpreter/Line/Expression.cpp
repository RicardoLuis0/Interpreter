#include "Interpreter/Expression.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "symbols_keywords.h"

#include "Parser/ExpressionGroup.h"
#include "Parser/KeywordFunctionCall.h"
#include "Parser/BinaryOperation.h"
#include "Interpreter/LineResultSimple.h"
#include "Interpreter/ExprPartFnCall.h"
#include "Interpreter/ExprPartVar.h"
#include "Interpreter/ExprPartValue.h"
#include "Interpreter/ExprPartIs.h"
#include "Interpreter/ExprPartCast.h"
#include "Interpreter/ExprPartTypeOf.h"
#include "Lexer/StringToken.h"
#include "Lexer/IntegerToken.h"
#include "Lexer/CharToken.h"
#include "Lexer/FloatToken.h"
#include "Parser/UnaryOperation.h"
#include "Interpreter/ExprPartUnaryOp.h"
#include "Interpreter/Value.h"
#include "Interpreter/PointerValue.h"
#include "Interpreter/TypeValue.h"

using namespace Interpreter;

std::shared_ptr<Expression> Expression::expr_assign_ignore_const(DefaultFrame * context,std::string varname,std::shared_ptr<Parser::Expression> assign_val,int line){
    return std::make_shared<Expression>(std::make_shared<ExprPartOp>(std::make_shared<ExprPartVar>(context,varname,line,true),SYMBOL_ASSIGNMENT,get_expression(context,assign_val),line,assign_val->line_end),line);
}

Expression::Expression(DefaultFrame * context,std::shared_ptr<Parser::Expression> e):Line(e->line_start){
    expression=get_expression(context,e);
}

Expression::Expression(std::shared_ptr<ExprPart> e,int l):Line(l),expression(e){
    
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
        if(op->is_keyword){
            switch(op->binary_keyword_operator->get_keyword_type()){
            case KEYWORD_IS:
                return std::make_shared<ExprPartIs>(get_expression(context,op->term2),get_term(context,op->term1));
            default:
                throw std::runtime_error("keyword operator '"+op->binary_keyword_operator->get_literal()+"' not imeplemented yet");
            }
        }else{
            switch(op->binary_operator->get_symbol_type()){
            case SYMBOL_ARROW:
            case SYMBOL_DOT:
                throw std::runtime_error("member access operators not implemented yet");
                break;
            default:
                return std::make_shared<ExprPartOp>(get_term(context,op->term1),op->binary_operator->get_symbol_type(),get_expression(context,op->term2),e->line_start,e->line_end);
            }
        }
    }else{
        return get_term(context,std::static_pointer_cast<Parser::ExpressionTerm>(e->contents));
    }
}

std::shared_ptr<ExprPart> Expression::get_term(DefaultFrame * context,std::shared_ptr<Parser::ExpressionTerm> term){
    if(term->member_access_type!=Parser::MEMBER_ACCESS_NONE)throw std::runtime_error("member access still not supported");
    std::shared_ptr<ExprPart> expr=nullptr;
    switch(term->type){
    case Parser::EXPRESSION_TERM_EXPRESSION_GROUP:
        expr=get_expression(context,std::static_pointer_cast<Parser::ExpressionGroup>(term->contents_p)->contents);
        break;
    case Parser::EXPRESSION_TERM_FUNCTION_CALL:
        expr=std::make_shared<ExprPartFnCall>(context,std::static_pointer_cast<Parser::FunctionCall>(term->contents_p));
        break;
    case Parser::EXPRESSION_TERM_KEYWORD_FUNCTION_CALL:
        {
            std::shared_ptr<Parser::KeywordFunctionCall> kfn=std::static_pointer_cast<Parser::KeywordFunctionCall>(term->contents_p);
            switch(kfn->identifier->get_keyword_type()){
            case KEYWORD_IS:
                if(kfn->extra_type==nullptr){
                    if(kfn->arguments&&kfn->arguments->expression_list.size()!=2)throw std::runtime_error("missing type to compare, usage 'is<TYPE>(VALUE)' or 'is(TYPE_VALUE,VALUE)'");
                    expr=std::make_shared<ExprPartIs>(get_expression(context,kfn->arguments->expression_list[0]),get_expression(context,kfn->arguments->expression_list[1]));
                }else{
                    if(kfn->arguments&&kfn->arguments->expression_list.size()!=1)throw std::runtime_error("invalid argument count, usage 'is<TYPE>(VALUE)' or 'is(TYPE_VALUE,VALUE)'");
                    expr=std::make_shared<ExprPartIs>(std::make_shared<ExprPartValue>(std::make_shared<TypeValue>(Type::from_vartype(context,kfn->extra_type))),get_expression(context,kfn->arguments->expression_list[0]));
                }
                break;
            case KEYWORD_CAST:
                if(kfn->extra_type==nullptr){
                    if(kfn->arguments&&kfn->arguments->expression_list.size()!=2)throw std::runtime_error("missing type to cast, usage 'cast<TYPE>(VALUE)' or 'cast(TYPE_VALUE,VALUE)'");
                    expr=std::make_shared<ExprPartCast>(get_expression(context,kfn->arguments->expression_list[0]),get_expression(context,kfn->arguments->expression_list[1]));
                }else{
                    if(kfn->arguments&&kfn->arguments->expression_list.size()!=1)throw std::runtime_error("invalid argument count, usage 'cast<TYPE>(VALUE)' or 'cast(TYPE_VALUE,VALUE)'");
                    expr=std::make_shared<ExprPartCast>(std::make_shared<ExprPartValue>(std::make_shared<TypeValue>(Type::from_vartype(context,kfn->extra_type))),get_expression(context,kfn->arguments->expression_list[0]));
                }
                break;
            case KEYWORD_TYPE:
                if(kfn->extra_type==nullptr)throw std::runtime_error("missing type for type literal, usage 'type<TYPE>()'");
                if(kfn->arguments)throw std::runtime_error("invalid argument count, usage 'type<TYPE>()'");
                expr=std::make_shared<ExprPartValue>(std::make_shared<TypeValue>(Type::from_vartype(context,kfn->extra_type)));
                break;
            case KEYWORD_TYPEOF:
                if(kfn->extra_type!=nullptr)throw std::runtime_error("invalid type argument, usage 'typeof(VALUE)'");
                if(kfn->arguments&&kfn->arguments->expression_list.size()!=1)throw std::runtime_error("invalid argument count, usage 'typeof(VALUE)'");
                expr=std::make_shared<ExprPartTypeOf>(get_expression(context,kfn->arguments->expression_list[0]));
                break;
            default:
                throw std::runtime_error("unimplemented Expression Term type keyword function "+kfn->identifier->get_literal());
            }
        }
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
        {
            auto op=std::static_pointer_cast<Parser::UnaryOperation>(term->contents_p);
            if(op->is_keyword){
                switch(op->unary_keyword_operator->get_keyword_type()){
                case KEYWORD_TYPEOF:
                    expr=std::make_shared<ExprPartTypeOf>(get_term(context,op->term));
                    break;
                default:
                    throw std::runtime_error("keyword unary operator '"+op->unary_keyword_operator->get_literal()+"' not imeplemented yet");
                }
            }else{
                expr=std::make_shared<ExprPartUnaryOp>(get_term(context,op->term),op->unary_operator->get_symbol_type(),true,term->line_start,term->line_end);
            }
        }
        break;
    case Parser::EXPRESSION_TERM_LITERAL_TRUE:
        expr=ExprPartValue::from_int(1);
        break;
    case Parser::EXPRESSION_TERM_LITERAL_FALSE:
        expr=ExprPartValue::from_int(0);
        break;
    case Parser::EXPRESSION_TERM_LITERAL_NULL:
        expr=std::make_shared<ExprPartValue>(std::make_shared<PointerValue>(Type::void_type(),nullptr));
        break;
    case Parser::EXPRESSION_TERM_VARTYPE:
        expr=std::make_shared<ExprPartValue>(std::make_shared<TypeValue>(Type::from_vartype(context,std::static_pointer_cast<Parser::VarType>(term->contents_p))));
        break;
    default:
        throw std::runtime_error("unimplemented Expression Term type");//unreachable???
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
