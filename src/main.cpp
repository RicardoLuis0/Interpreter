#include <iostream>
#include "my_except.h"
#include "lexer.h"
//#include "block_separator.h"
//#include "block_list_element_vector_browser.h"
#include "console.h"
#include "symbols_keywords.h"

#include "parser.h"
#include "parser_expression_matcher.h"
#include "parser_line_matcher.h"
#include "parser_expression.h"
#include "parser_expression_list.h"
#include "parser_expression_group.h"
#include "parser_expression_term.h"
#include "parser_binary_operation.h"
#include "parser_function_call.h"
#include "parser_if_statement.h"
#include "parser_for_statement.h"
#include "parser_while_statement.h"
#include "parser_statement.h"
#include "parser_line.h"
#include "parser_code_block.h"

/**
 * @mainpage
 * 
 * Lexer for interpreted language
 * 
 * @author Ricardo Luis Vaz Silva
 * @date 2/19/19
 * @version 0.01
 */

void test_lexer(),test_expressions(),test_lines();

int main(){
    Console::init();
    while(true){
        Console::clear();
        std::cout<<"0> test lexer\n1> test expression parser\n2> test line parser\n\nChoice: ";
        std::string input;
        std::cin>>input;
        if(input.compare("0")==0){
            test_lexer();
        }else if(input.compare("1")==0){
            test_expressions();
        }else if(input.compare("2")==0){
            test_lines();
        }else{
            continue;
        }
        return 0;
    }
    return 0;
}
void test_lexer(){
    try{
        std::string filename;
        std::vector<std::shared_ptr<Lexer::Token>> tokens;
        Lexer::Lexer lexer(base_symbols,base_keywords);
        while(true){
            Console::clear();
            std::cout<<"Filename: ";
            std::cin>>filename;
            try{
                tokens=lexer.tokenize_from_file(filename);//split file into tokens
                for(std::shared_ptr<Lexer::Token> t:tokens){
                    std::cout<<t->get_formatted()<<"\n";
                }
            }catch(MyExcept::FileError &e){
                std::cout<<e.what()<<"\nTry Again, ";
            }
            break;
        }
    }catch(MyExcept::ParseError &e){
        std::cout<<e.what();
        return;
    }catch(std::exception &e){
        std::cout<<"uncaught exception: "<<e.what();
        return;
    }
}

std::string get_ident(int ident){
    return std::string(ident,' ')+std::string(ident,' ');//2 space ident
}

void print_expression(int,std::shared_ptr<Parser::Expression>);
void print_line(int,std::shared_ptr<Parser::Line>);

void print_expression_list(int ident,std::shared_ptr<Parser::ExpressionList> exprlist){
    std::cout<<get_ident(ident)<<">Expression List\n";
    size_t count=0;
    for(std::shared_ptr<Parser::Expression> expr:exprlist->expression_list){
        std::cout<<get_ident(ident)<<".list["<<count<<"]:\n";
        print_expression(ident+1,expr);
        count++;
    }
}

void print_token(int ident,std::shared_ptr<Lexer::Token> token){
    if(token==nullptr){
        std::cout<<get_ident(ident)<<"std::nullptr_t\n";
    }else{
        std::cout<<get_ident(ident)<<token->get_formatted()<<"\n";
    }
}

void print_function_call(int ident,std::shared_ptr<Parser::FunctionCall> call){
    std::cout<<get_ident(ident)<<">Function Call\n";
    std::cout<<get_ident(ident)<<".identifier:\n";
    print_token(ident+1,call->identifier);
    std::cout<<get_ident(ident)<<".arguments:\n";
    if(call->arguments==nullptr){
        std::cout<<get_ident(ident+1)<<"No Args\n";
    }else{
        print_expression_list(ident+1,call->arguments);
    }
}

void print_expression_group(int ident,std::shared_ptr<Parser::ExpressionGroup> group){
    std::cout<<get_ident(ident)<<">Expression Group\n";
    std::cout<<get_ident(ident)<<".expression:\n";
    print_expression(ident+1,group->contents);
}

void print_expression_term(int ident,std::shared_ptr<Parser::ExpressionTerm> term){
    std::cout<<get_ident(ident)<<">Expression Term\n";
    switch(term->type){
    case Parser::EXPRESSION_TERM_EXPRESSION_GROUP:
        std::cout<<get_ident(ident)<<".expression group:\n";
        print_expression_group(ident+1,std::static_pointer_cast<Parser::ExpressionGroup>(term->contents_p));
        break;
    case Parser::EXPRESSION_TERM_FUNCTION_CALL:
        std::cout<<get_ident(ident)<<".function call:\n";
        print_function_call(ident+1,std::static_pointer_cast<Parser::FunctionCall>(term->contents_p));
        break;
    case Parser::EXPRESSION_TERM_UNARY_OPERATION:
        std::cout<<get_ident(ident)<<".unary operation:\n";
        //TODO print unary operation
        break;
    case Parser::EXPRESSION_TERM_LITERAL_INT:
    case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
    case Parser::EXPRESSION_TERM_LITERAL_STRING:
        std::cout<<get_ident(ident)<<".literal:\n";
        print_token(ident+1,term->contents_t);
        break;
    case Parser::EXPRESSION_TERM_IDENTIFIER:
        std::cout<<get_ident(ident)<<".identifier:\n";
        print_token(ident+1,term->contents_t);
        break;
    }
}

void print_binary_operation(int ident,std::shared_ptr<Parser::BinaryOperation> bin_op){
    std::cout<<get_ident(ident)<<">Binary Operation\n";
    std::cout<<get_ident(ident)<<".term1:\n";
    print_expression_term(ident+1,bin_op->term1);
    std::cout<<get_ident(ident)<<".operator:\n";
    print_token(ident+1,bin_op->binary_operator);
    std::cout<<get_ident(ident)<<".term2:\n";
    print_expression(ident+1,bin_op->term2);
}

void print_expression(int ident,std::shared_ptr<Parser::Expression> expr){
    std::cout<<get_ident(ident)<<">Expression\n";
    if(expr->type==Parser::EXPRESSION_BINARY_OPERATION){
        std::cout<<get_ident(ident)<<".binary operation:\n";
        print_binary_operation(ident+1,std::static_pointer_cast<Parser::BinaryOperation>(expr->contents));
    }else{
        std::cout<<get_ident(ident)<<".expression term:\n";
        print_expression_term(ident+1,std::static_pointer_cast<Parser::ExpressionTerm>(expr->contents));
    }
}

void print_code_block(int ident,std::shared_ptr<Parser::CodeBlock> block){
    std::cout<<get_ident(ident)<<">Code Block\n";
    size_t count=0;
    for(std::shared_ptr<Parser::Line> line:block->lines){
        std::cout<<get_ident(ident)<<".line["<<count<<"]:\n";
        print_line(ident+1,line);
        count++;
    }
}


void print_if_statement(int ident,std::shared_ptr<Parser::IfStatement> stmt){
    std::cout<<get_ident(ident)<<">IfStatement\n";
    std::cout<<get_ident(ident)<<".condition:\n";
    print_expression(ident+1,stmt->condition);
    std::cout<<get_ident(ident)<<".code:\n";
    print_line(ident+1,stmt->code);
}

void print_for_statement(int ident,std::shared_ptr<Parser::ForStatement> stmt){
    std::cout<<get_ident(ident)<<">ForStatement\n";
    std::cout<<get_ident(ident)<<".pre:\n";
    print_expression(ident+1,stmt->pre);
    std::cout<<get_ident(ident)<<".condition:\n";
    print_expression(ident+1,stmt->condition);
    std::cout<<get_ident(ident)<<".inc:\n";
    print_expression(ident+1,stmt->inc);
    std::cout<<get_ident(ident)<<".code:\n";
    print_line(ident+1,stmt->code);
}

void print_while_statement(int ident,std::shared_ptr<Parser::WhileStatement> stmt){
    std::cout<<get_ident(ident)<<">WhileStatement\n";
    std::cout<<get_ident(ident)<<".condition:\n";
    print_expression(ident+1,stmt->condition);
    std::cout<<get_ident(ident)<<".code:\n";
    print_line(ident+1,stmt->code);
}

void print_statement(int ident,std::shared_ptr<Parser::Statement> stmt){
    std::cout<<get_ident(ident)<<">Statement\n";
    switch(stmt->type){
    case Parser::STATEMENT_IF:
        print_if_statement(ident+1,std::static_pointer_cast<Parser::IfStatement>(stmt->statement));
        break;
    case Parser::STATEMENT_FOR:
        print_for_statement(ident+1,std::static_pointer_cast<Parser::ForStatement>(stmt->statement));
        break;
    case Parser::STATEMENT_WHILE:
        print_while_statement(ident+1,std::static_pointer_cast<Parser::WhileStatement>(stmt->statement));
        break;
    }
}

void print_line(int ident,std::shared_ptr<Parser::Line> line){
    switch(line->type){
    case Parser::LINE_CODE_BLOCK:
        std::cout<<get_ident(ident)<<".code block:\n";
        print_code_block(ident+1,std::static_pointer_cast<Parser::CodeBlock>(line->contents));
        break;
    case Parser::LINE_EXPRESSION:
        std::cout<<get_ident(ident)<<".expression:\n";
        print_expression(ident+1,std::static_pointer_cast<Parser::Expression>(line->contents));
        break;
    case Parser::LINE_STATEMENT:
        std::cout<<get_ident(ident)<<".statement:\n";
        print_statement(ident+1,std::static_pointer_cast<Parser::Statement>(line->contents));
        break;
    case Parser::LINE_EMPTY:
        std::cout<<get_ident(ident)<<"Empty Line\n";
    }
}

void test_expressions(){
    try{
        std::string filename;
        std::vector<std::shared_ptr<Lexer::Token>> tokens;
        Lexer::Lexer lexer(base_symbols,base_keywords);
        while(true){
            Console::clear();
            std::cout<<"Filename: ";
            std::cin>>filename;
            try{
                tokens=lexer.tokenize_from_file(filename);//split file into tokens
            }catch(MyExcept::FileError &e){
                std::cout<<e.what()<<"\nTry Again, ";
                continue;
            }
            break;
        }
        Parser::parserProgress p {data:tokens,location:0};
        std::shared_ptr<Parser::Expression> expr=Parser::ExpressionMatcher().makeMatch(p);
        print_expression(0,expr);
    }catch(MyExcept::ParseError &e){
        std::cout<<e.what();
        return;
    }catch(MyExcept::NoMatchException &e){
        std::cout<<e.what();
        return;
    }catch(std::exception &e){
        std::cout<<"uncaught exception: "<<e.what();
        return;
    }
}

void test_lines(){
    try{
        std::string filename;
        std::vector<std::shared_ptr<Lexer::Token>> tokens;
        Lexer::Lexer lexer(base_symbols,base_keywords);
        while(true){
            Console::clear();
            std::cout<<"Filename: ";
            std::cin>>filename;
            try{
                tokens=lexer.tokenize_from_file(filename);//split file into tokens
            }catch(MyExcept::FileError &e){
                std::cout<<e.what()<<"\nTry Again, ";
                continue;
            }
            break;
        }
        Parser::parserProgress p {data:tokens,location:0};
        std::shared_ptr<Parser::Line> line=Parser::LineMatcher().makeMatch(p);
        print_line(0,line);
    }catch(MyExcept::ParseError &e){
        std::cout<<e.what();
        return;
    }catch(MyExcept::NoMatchException &e){
        std::cout<<e.what();
        return;
    }catch(std::exception &e){
        std::cout<<"uncaught exception: "<<e.what();
        return;
    }
}
