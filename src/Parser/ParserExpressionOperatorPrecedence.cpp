#include "Parser/ParserExpressionOperatorPrecedence.h"

#include <map>
#include <vector>
#include "symbols_keywords.h"
#include "Parser/ExpressionTerm.h"
#include "Parser/ExpressionGroup.h"
#include "Parser/BinaryOperation.h"
#include "Lexer/SymbolToken.h"

using namespace Parser;

static std::string get_op_str(int op){
    if(op<_LAST_KEYWORD_){
        return get_keyword_data(keyword_type_t(op)).name;
    }else{
        return get_symbol_data(symbol_type_t(op)).name;
    }
}

static std::map<int,int> operator_precedence{
    {SYMBOL_ASSIGNMENT,99},
    {SYMBOL_EQUALS,5},
    {SYMBOL_NOT_EQUALS,5},
    {SYMBOL_GREATER,4},
    {SYMBOL_GREATER_EQUALS,4},
    {SYMBOL_LOWER,4},
    {SYMBOL_LOWER_EQUALS,4},
    {SYMBOL_PLUS,2},
    {SYMBOL_PLUS_ASSIGNMENT,99},
    {SYMBOL_MINUS,2},
    {SYMBOL_MINUS_ASSIGNMENT,99},
    {SYMBOL_MULTIPLY,1},
    {SYMBOL_MULTIPLY_ASSIGNMENT,99},
    {SYMBOL_DIVIDE,1},
    {SYMBOL_DIVIDE_ASSIGNMENT,99},
    {SYMBOL_LOGICAL_AND,9},
    {SYMBOL_LOGICAL_OR,10},
    {SYMBOL_BITWISE_AND,6},
    {SYMBOL_BITWISE_AND_ASSIGNMENT,99},
    {SYMBOL_BITWISE_OR,8},
    {SYMBOL_BITWISE_OR_ASSIGNMENT,99},
    {SYMBOL_BITWISE_XOR,7},
    {SYMBOL_BITWISE_XOR_ASSIGNMENT,99},
    {SYMBOL_LEFT_SHIFT,3},
    {SYMBOL_LEFT_SHIFT_ASSIGNMENT,99},
    {SYMBOL_RIGHT_SHIFT,3},
    {SYMBOL_RIGHT_SHIFT_ASSIGNMENT,99},
    {SYMBOL_PERCENT,1},
    {SYMBOL_PERCENT_ASSIGNMENT,99},
    {KEYWORD_IS,0},
};

struct element{
    element(std::shared_ptr<Lexer::SymbolToken> i):op(i),is_op(true),elem(nullptr){
        
    }
    element(std::shared_ptr<ParserResultPart> ptr):op(nullptr),is_op(false),elem(ptr){
        
    }
    std::shared_ptr<Lexer::SymbolToken> op;
    bool is_op;
    std::shared_ptr<ParserResultPart> elem;
};

struct state {
    std::vector<element> st;
    int line_start;
    int line_end;
};

static void add_expr(std::shared_ptr<Expression> e,state &out);

static void add_term(std::shared_ptr<ExpressionTerm> e,state &out){
    if(e->type==EXPRESSION_TERM_EXPRESSION_GROUP){
        add_expr(std::static_pointer_cast<ExpressionGroup>(e->contents_p)->contents,out);
    }else{
        out.st.emplace_back(e);
    }
}

static void add_expr(std::shared_ptr<Expression> e,state &out){
    std::vector<std::shared_ptr<Lexer::SymbolToken>> op_stack;
    //parse operator precedence using shunting yard, check for undefined functions/variables
    while(1){
        if(e->type==EXPRESSION_BINARY_OPERATION){
            std::shared_ptr<BinaryOperation> op(std::static_pointer_cast<BinaryOperation>(e->contents));
            int op_num;
            if(op->is_keyword){
                op_num=op->binary_keyword_operator->get_keyword_type();
                op->binary_operator=std::make_shared<Lexer::SymbolToken>(op->binary_keyword_operator->line,Lexer::symbol_data("","",op_num));
            }else{
                op_num=op->binary_operator->get_symbol_type();
            }
            add_term(op->term1,out);
            if(operator_precedence.find(op_num)==operator_precedence.end())throw std::runtime_error("unknown operator "+get_op_str(op_num));
            while(!op_stack.empty()&&operator_precedence[op_stack.back()->get_symbol_type()]<operator_precedence[op_num]){
                out.st.emplace_back(op_stack.back());
                op_stack.pop_back();
            }
            op_stack.push_back(op->binary_operator);
            if(op->binary_keyword_operator)op->binary_operator=nullptr;
            e=op->term2;
        }else if(e->type==EXPRESSION_TERM){
            add_term(std::static_pointer_cast<ExpressionTerm>(e->contents),out);
            while(!op_stack.empty()){
                out.st.emplace_back(op_stack.back());
                op_stack.pop_back();
            }
            break;
        }
    }
}

static std::shared_ptr<Expression> build_op(state &st,std::shared_ptr<Lexer::SymbolToken> op){
    element e=st.st.back();
    st.st.pop_back();
    std::shared_ptr<Expression> right;
    if(e.is_op){
        right=build_op(st,e.op);
    }else{
        right=std::make_shared<Expression>(e.elem,EXPRESSION_TERM,st.line_start,st.line_end);
    }
    e=st.st.back();
    st.st.pop_back();
    std::shared_ptr<ExpressionTerm> left;
    if(e.is_op){
        left=std::make_shared<ExpressionTerm>(std::make_shared<ExpressionGroup>(build_op(st,e.op),st.line_start,st.line_end),EXPRESSION_TERM_EXPRESSION_GROUP,st.line_start,st.line_end);
    }else{
        left=std::static_pointer_cast<ExpressionTerm>(e.elem);
    }
    if(op->get_symbol_type()<_LAST_KEYWORD_){
        return std::make_shared<Expression>(std::make_shared<BinaryOperation>(left,std::make_shared<Lexer::KeywordToken>(op->line,get_keyword_data(keyword_type_t(op->get_symbol_type()))),right,st.line_start,st.line_end),EXPRESSION_BINARY_OPERATION,st.line_start,st.line_end);
    }else{
        return std::make_shared<Expression>(std::make_shared<BinaryOperation>(left,op,right,st.line_start,st.line_end),EXPRESSION_BINARY_OPERATION,st.line_start,st.line_end);
    }
}

static std::shared_ptr<Expression> build_expr(state &st){
    element e=st.st.back();
    st.st.pop_back();
    if(e.is_op){
        return build_op(st,e.op);
    }else{
        return std::make_shared<Expression>(e.elem,EXPRESSION_TERM,st.line_start,st.line_end);
    }
}

std::shared_ptr<Expression> Parser::order_expression(std::shared_ptr<Expression> e){
    state res{{},e->line_start,e->line_end};
    add_expr(e,res);
    return build_expr(res);
}
