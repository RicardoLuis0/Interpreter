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
#include "parser_definition.h"
#include "parser_var_type.h"
#include "parser_variable_definition.h"
#include "parser_function_definition.h"
#include "parser_function_definition_parameter.h"
#include "parser_return_statement.h"
#include "parser_definition_matcher.h"

/**
 * @mainpage
 * 
 * Lexer for interpreted language
 * 
 * @author Ricardo Luis Vaz Silva
 * @date 2/19/19
 * @version 0.01
 */

void test_lexer(),test_expressions(),test_lines(),test_definitions();

int main(){
    Console::init();
    while(true){
        Console::clear();
        std::cout<<"0> test lexer\n1> test expression parser\n2> test line parser\n3> test code\n\nChoice: ";
        std::string input;
        std::cin>>input;
        if(input.compare("0")==0){
            test_lexer();
        }else if(input.compare("1")==0){
            test_expressions();
        }else if(input.compare("2")==0){
            test_lines();
        }else if(input.compare("3")==0){
            test_definitions();
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

std::string get_indent(int indent){
    return std::string(indent,' ')+std::string(indent,' ');//2 space indent
}

void print_expression(int,std::shared_ptr<Parser::Expression>);
void print_line(int,std::shared_ptr<Parser::Line>);

void print_expression_list(int indent,std::shared_ptr<Parser::ExpressionList> exprlist){
    std::cout<<get_indent(indent)<<">Expression List\n";
    size_t count=0;
    for(std::shared_ptr<Parser::Expression> expr:exprlist->expression_list){
        std::cout<<get_indent(indent)<<".list["<<count<<"]:\n";
        print_expression(indent+1,expr);
        count++;
    }
}

void print_token(int indent,std::shared_ptr<Lexer::Token> token){
    if(token==nullptr){
        std::cout<<get_indent(indent)<<"std::nullptr_t\n";
    }else{
        std::cout<<get_indent(indent)<<token->get_formatted()<<"\n";
    }
}

void print_function_call(int indent,std::shared_ptr<Parser::FunctionCall> call){
    std::cout<<get_indent(indent)<<">Function Call\n";
    std::cout<<get_indent(indent)<<".identifier:\n";
    print_token(indent+1,call->identifier);
    std::cout<<get_indent(indent)<<".arguments:\n";
    if(call->arguments==nullptr){
        std::cout<<get_indent(indent+1)<<"No Args\n";
    }else{
        print_expression_list(indent+1,call->arguments);
    }
}

void print_expression_group(int indent,std::shared_ptr<Parser::ExpressionGroup> group){
    std::cout<<get_indent(indent)<<">Expression Group\n";
    std::cout<<get_indent(indent)<<".expression:\n";
    print_expression(indent+1,group->contents);
}

void print_expression_term(int indent,std::shared_ptr<Parser::ExpressionTerm> term){
    std::cout<<get_indent(indent)<<">Expression Term\n";
    switch(term->type){
    case Parser::EXPRESSION_TERM_EXPRESSION_GROUP:
        std::cout<<get_indent(indent)<<".expression group:\n";
        print_expression_group(indent+1,std::static_pointer_cast<Parser::ExpressionGroup>(term->contents_p));
        break;
    case Parser::EXPRESSION_TERM_FUNCTION_CALL:
        std::cout<<get_indent(indent)<<".function call:\n";
        print_function_call(indent+1,std::static_pointer_cast<Parser::FunctionCall>(term->contents_p));
        break;
    case Parser::EXPRESSION_TERM_UNARY_OPERATION:
        std::cout<<get_indent(indent)<<".unary operation:\n";
        //TODO print unary operation
        break;
    case Parser::EXPRESSION_TERM_LITERAL_INT:
    case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
    case Parser::EXPRESSION_TERM_LITERAL_STRING:
        std::cout<<get_indent(indent)<<".literal:\n";
        print_token(indent+1,term->contents_t);
        break;
    case Parser::EXPRESSION_TERM_IDENTIFIER:
        std::cout<<get_indent(indent)<<".identifier:\n";
        print_token(indent+1,term->contents_t);
        break;
    }
}

void print_binary_operation(int indent,std::shared_ptr<Parser::BinaryOperation> bin_op){
    std::cout<<get_indent(indent)<<">Binary Operation\n";
    std::cout<<get_indent(indent)<<".term1:\n";
    print_expression_term(indent+1,bin_op->term1);
    std::cout<<get_indent(indent)<<".operator:\n";
    print_token(indent+1,bin_op->binary_operator);
    std::cout<<get_indent(indent)<<".term2:\n";
    print_expression(indent+1,bin_op->term2);
}

void print_expression(int indent,std::shared_ptr<Parser::Expression> expr){
    std::cout<<get_indent(indent)<<">Expression\n";
    if(expr->type==Parser::EXPRESSION_BINARY_OPERATION){
        std::cout<<get_indent(indent)<<".binary operation:\n";
        print_binary_operation(indent+1,std::static_pointer_cast<Parser::BinaryOperation>(expr->contents));
    }else{
        std::cout<<get_indent(indent)<<".expression term:\n";
        print_expression_term(indent+1,std::static_pointer_cast<Parser::ExpressionTerm>(expr->contents));
    }
}

void print_code_block(int indent,std::shared_ptr<Parser::CodeBlock> block){
    std::cout<<get_indent(indent)<<">Code Block\n";
    size_t count=0;
    for(std::shared_ptr<Parser::Line> line:block->lines){
        std::cout<<get_indent(indent)<<".line["<<count<<"]:\n";
        print_line(indent+1,line);
        count++;
    }
}

void print_else_statement(int indent,std::shared_ptr<Parser::ElseStatement> stmt){
    std::cout<<get_indent(indent)<<">Else Statement\n";
    std::cout<<get_indent(indent)<<".code:\n";
    print_line(indent+1,stmt->code);
}

void print_if_statement(int indent,std::shared_ptr<Parser::IfStatement> stmt){
    std::cout<<get_indent(indent)<<">If Statement\n";
    std::cout<<get_indent(indent)<<".condition:\n";
    print_expression(indent+1,stmt->condition);
    std::cout<<get_indent(indent)<<".code:\n";
    print_line(indent+1,stmt->code);
    if(stmt->else_stmt){
        std::cout<<get_indent(indent)<<".else:\n";
        print_else_statement(indent+1,stmt->else_stmt);
    }
}

void print_for_statement(int indent,std::shared_ptr<Parser::ForStatement> stmt){
    std::cout<<get_indent(indent)<<">For Statement\n";
    std::cout<<get_indent(indent)<<".pre:\n";
    print_expression(indent+1,stmt->pre);
    std::cout<<get_indent(indent)<<".condition:\n";
    print_expression(indent+1,stmt->condition);
    std::cout<<get_indent(indent)<<".inc:\n";
    print_expression(indent+1,stmt->inc);
    std::cout<<get_indent(indent)<<".code:\n";
    print_line(indent+1,stmt->code);
}

void print_while_statement(int indent,std::shared_ptr<Parser::WhileStatement> stmt){
    std::cout<<get_indent(indent)<<">While Statement\n";
    std::cout<<get_indent(indent)<<".condition:\n";
    print_expression(indent+1,stmt->condition);
    std::cout<<get_indent(indent)<<".code:\n";
    print_line(indent+1,stmt->code);
}

void print_return_statement(int indent,std::shared_ptr<Parser::ReturnStatement> stmt){
    std::cout<<get_indent(indent)<<">Return Statement\n";
    std::cout<<get_indent(indent)<<".value:\n";
    print_expression(indent+1,stmt->value);
}

void print_statement(int indent,std::shared_ptr<Parser::Statement> stmt){
    std::cout<<get_indent(indent)<<">Statement\n";
    switch(stmt->type){
    case Parser::STATEMENT_IF:
        print_if_statement(indent+1,std::static_pointer_cast<Parser::IfStatement>(stmt->statement));
        break;
    case Parser::STATEMENT_FOR:
        print_for_statement(indent+1,std::static_pointer_cast<Parser::ForStatement>(stmt->statement));
        break;
    case Parser::STATEMENT_WHILE:
        print_while_statement(indent+1,std::static_pointer_cast<Parser::WhileStatement>(stmt->statement));
    case Parser::STATEMENT_RETURN:
        print_return_statement(indent+1,std::static_pointer_cast<Parser::ReturnStatement>(stmt->statement));
        break;
    }
}

void print_var_type(int indent,std::shared_ptr<Parser::VarType> type){
    std::cout<<get_indent(indent)<<">Variable Type\n";
    switch(type->type){
        case Parser::VARTYPE_PRIMITIVE:
            std::cout<<get_indent(indent)<<".primitive:\n";
            print_token(indent+1,type->primitive);
        default:
            //no more types, in the future TODO
            break;
    }
}

void print_function_definition_parameter(int indent,std::shared_ptr<Parser::FunctionDefinitionParameter> param){
    std::cout<<get_indent(indent)<<">Parameter\n";
    std::cout<<get_indent(indent)<<".type:\n";
    print_var_type(indent+1,param->type);
    std::cout<<get_indent(indent)<<".name:\n";
    print_token(indent+1,param->name);
}

void print_function_definition(int indent,std::shared_ptr<Parser::FunctionDefinition> func){
    std::cout<<get_indent(indent)<<">Function Definition\n";
    std::cout<<get_indent(indent)<<".return type:\n";
    print_var_type(indent+1,func->return_type);
    std::cout<<get_indent(indent)<<".name:\n";
    print_token(indent+1,func->name);
    size_t count=0;
    for(std::shared_ptr<Parser::FunctionDefinitionParameter> param:func->parameters){
        std::cout<<get_indent(indent)<<".parameter["<<count<<"]:\n";
        print_function_definition_parameter(indent+1,param);
        count++;
    }
    std::cout<<get_indent(indent)<<".code:\n";
    print_code_block(indent+1,func->code);
}

void print_variable_definition_item(int indent,std::shared_ptr<Parser::VariableDefinitionItem> item){
    std::cout<<get_indent(indent)<<">Variable\n";
    std::cout<<get_indent(indent)<<".name:\n";
    print_token(indent+1,item->name);
    if(item->value){
        std::cout<<get_indent(indent)<<".value:\n";
        print_expression(indent+1,item->value);
    }
}

void print_variable_definition(int indent,std::shared_ptr<Parser::VariableDefinition> def){
    std::cout<<get_indent(indent)<<">Variable Definition List\n";
    std::cout<<get_indent(indent)<<".type:\n";
    print_var_type(indent+1,def->type);
    size_t count=0;
    for(auto item:def->variables){
        std::cout<<get_indent(indent)<<".variable["<<count<<"]:\n";
        print_variable_definition_item(indent+1,item);
        count++;
    }
}

void print_definition(int indent,std::shared_ptr<Parser::Definition> def){
    std::cout<<get_indent(indent)<<">Definition\n";
    switch(def->type){
    case Parser::DEFINITION_VAR:
        print_variable_definition(indent+1,std::static_pointer_cast<Parser::VariableDefinition>(def->def));
        break;
    case Parser::DEFINITION_FUNC:
        print_function_definition(indent+1,std::static_pointer_cast<Parser::FunctionDefinition>(def->def));
        break;
    }
}

void print_line(int indent,std::shared_ptr<Parser::Line> line){
    switch(line->type){
    case Parser::LINE_CODE_BLOCK:
        std::cout<<get_indent(indent)<<".code block:\n";
        print_code_block(indent+1,std::static_pointer_cast<Parser::CodeBlock>(line->contents));
        break;
    case Parser::LINE_EXPRESSION:
        std::cout<<get_indent(indent)<<".expression:\n";
        print_expression(indent+1,std::static_pointer_cast<Parser::Expression>(line->contents));
        break;
    case Parser::LINE_STATEMENT:
        std::cout<<get_indent(indent)<<".statement:\n";
        print_statement(indent+1,std::static_pointer_cast<Parser::Statement>(line->contents));
        break;
    case Parser::LINE_DEFINITION:
        std::cout<<get_indent(indent)<<".definition:\n";
        print_definition(indent+1,std::static_pointer_cast<Parser::Definition>(line->contents));
        break;
    case Parser::LINE_EMPTY:
        std::cout<<get_indent(indent)<<"Empty Line\n";
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

void print_deflist(std::vector<std::shared_ptr<Parser::Definition>> defs){
    std::cout<<">Parser Result\n";
    size_t count=0;
    for(std::shared_ptr<Parser::Definition> def:defs){
        std::cout<<".line["<<count<<"]:\n";
        print_definition(1,def);
        count++;
    }
}

void test_definitions(){
    try{
        std::string filename;
        std::vector<std::shared_ptr<Lexer::Token>> tokens;
        std::vector<std::shared_ptr<Parser::Definition>> deflist;
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
        while(p.get_nothrow()!=nullptr){
            deflist.push_back(Parser::DefinitionMatcher().makeMatch(p));
        }
        print_deflist(deflist);
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
