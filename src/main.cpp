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
#include "parser_keyword_function_call.h"
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
#include "parser_unary_operation.h"
#include "interpreter_default_frame.h"
#include "interpreter_exec_frame.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_int_value.h"
#include "interpreter_void_type.h"
#include "interpreter_int_type.h"
#include <cstring>

#include "preprocessor.h"

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

//TODO update docs
/**
 * @mainpage
 * 
 * Interpreted language
 * 
 * @author Ricardo Luis Vaz Silva
 * @date 2/19/19
 * @version 0.01
 */

void test_lexer(),test_expressions(),test_lines(),test_definitions();

int exec(std::string filename){
    Lexer::Lexer lexer(base_symbols,base_keywords);
    std::vector<std::shared_ptr<Lexer::Token>> tokens(lexer.tokenize_from_file(filename));
    std::vector<std::shared_ptr<Parser::Definition>> deflist;
    Parser::parserProgress p {data:tokens,location:0};
    while(p.get_nothrow()!=nullptr){
        deflist.push_back(Parser::DefinitionMatcher().makeMatch(p));
    }
    Interpreter::DefaultFrame dframe(deflist);
    std::shared_ptr<Interpreter::ExecFrame> eframe(std::make_shared<Interpreter::ExecFrame>(nullptr,&dframe));
    std::shared_ptr<Interpreter::Function> entrypoint(eframe->get_function("main",{}));
    if(!entrypoint){
        throw std::runtime_error("missing 'main()' function");
    }else{
        if(CHECKPTR(entrypoint->get_type(),Interpreter::VoidType)){
            eframe->fn_call(entrypoint,{});
            return 0;
        }else{
            if(!CHECKPTR(entrypoint->get_type(),Interpreter::IntType)){
                throw std::runtime_error("'main' function must return 'int' or 'void'");
            }
            return std::dynamic_pointer_cast<Interpreter::IntValue>(eframe->fn_call(entrypoint,{}))->get();
        }
    }
}

int test_exec(){
    try{
        std::string filename;
        std::vector<std::shared_ptr<Lexer::Token>> tokens;
        std::vector<std::shared_ptr<Parser::Definition>> deflist;
        Lexer::Lexer lexer(base_symbols,base_keywords);
        Console::clear();
    start:
        while(true){
            std::cout<<">";
            std::cin>>filename;
            if(filename=="cls"){
                Console::clear();
                continue;
            }else if(filename=="help"){
                std::cout<<"type file path to load program, 'q' 'quit' or 'exit' to leave, 'cls' to clear screen\n";
                continue;
            }
            if(filename=="q"||filename=="quit"||filename=="exit")return 0;
            try{
                tokens=lexer.tokenize_from_file(filename);//split file into tokens
                SetCurrentDirectoryA(filename.substr(0,std::max(filename.rfind("/"),filename.rfind("\\"))).c_str());
            }catch(MyExcept::FileError &e){
                try{
                    tokens=lexer.tokenize_from_file(filename+".txt");
                    SetCurrentDirectoryA(filename.substr(0,std::max(filename.rfind("/"),filename.rfind("\\"))).c_str());
                }catch(MyExcept::FileError &e2){
                    try{
                        tokens=lexer.tokenize_from_file("examples/"+filename);
                        SetCurrentDirectoryA("examples");
                    }catch(MyExcept::FileError &e2){
                        try{
                            tokens=lexer.tokenize_from_file("examples/"+filename+".txt");
                            SetCurrentDirectoryA("examples");
                        }catch(MyExcept::FileError &e2){
                            std::cout<<e.what()<<", 'exit' 'quit' or 'q' to cancel\n";
                            continue;
                        }
                    }
                }
            }
            break;
        }
        //Console::clear();
        Parser::parserProgress p {data:tokens,location:0};
        deflist.clear();
        while(p.get_nothrow()!=nullptr){
            deflist.push_back(Parser::DefinitionMatcher().makeMatch(p));
        }
        Interpreter::DefaultFrame dframe(deflist);
        std::shared_ptr<Interpreter::ExecFrame> eframe(std::make_shared<Interpreter::ExecFrame>(nullptr,&dframe));
        std::shared_ptr<Interpreter::Function> entrypoint(eframe->get_function("main",{}));
        if(!entrypoint){
            std::cout<<"no main function";
        }else{
            if(CHECKPTR(entrypoint->get_type(),Interpreter::VoidType)){
                eframe->fn_call(entrypoint,{});
                std::cout<<filename<<" finished exeuction\n";
                goto start;
            }else{
                if(!CHECKPTR(entrypoint->get_type(),Interpreter::IntType)){
                    throw std::runtime_error("'main' function must return 'int' or 'void'");
                }
                int retval=std::dynamic_pointer_cast<Interpreter::IntValue>(eframe->fn_call(entrypoint,{}))->get();
                std::cout<<filename<<" returned with value "<<std::to_string(retval)<<"\n";
                goto start;
            }
        }
    }catch(MyExcept::ParseError &e){
        std::cout<<e.what();
        return 0;
    }catch(MyExcept::SyntaxError &e){
        std::cout<<e.what();
        return 0;
    }catch(MyExcept::NoMatchException &e){
        std::cout<<e.what();
        return 0;
    }catch(std::exception &e){
        std::cout<<"uncaught exception: "<<e.what()<<"\n";
        throw;
    }
    return 1;
}

int test_preprocessor(){
    try{
        system("cls");
        std::cout<<preprocess_file("pre_test.txt");
        return 0;
    }catch(std::exception &e){
        std::cout<<"uncaught exception: "<<e.what();
        return 1;
    }
}

int main(int argc,char ** argv){
    Console::init();
    if(argc<2){
        while(true){
            Console::clear();
            std::cout<<"0> test lexer\n1> test expression parser\n2> test line parser\n3> test whole code parsing\n4> test execution\n5> test preprocessor\n\nChoice: ";
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
            }else if(input.compare("4")==0){
                return test_exec();
            }else if(input.compare("5")==0){
                return test_preprocessor();
            }else{
                continue;
            }
            return 0;
        }
    }else if(argc==2){
        return exec(argv[1]);
    }else if(argc==3&&strcmp(argv[1],"-checkparse")==0){
        try{
            std::string filename(argv[1]);
            std::vector<std::shared_ptr<Lexer::Token>> tokens;
            Lexer::Lexer lexer(base_symbols,base_keywords);
            try{
                tokens=lexer.tokenize_from_file(filename);//split file into tokens
            }catch(MyExcept::FileError &e){
                std::cout<<e.what()<<"Could not open file '"+filename+"'";
                return 1;
            }
            Parser::parserProgress p {data:tokens,location:0};
            while(p.get_nothrow()!=nullptr){
                Parser::DefinitionMatcher().makeMatch(p);
            }
        }catch(MyExcept::ParseError &e){
            std::cout<<e.what();
            return 1;
        }catch(MyExcept::NoMatchException &e){
            std::cout<<e.what();
            return 1;
        }catch(std::exception &e){
            std::cout<<"uncaught exception: "<<e.what();
            return 1;
        }
        std::cout<<"Parse OK";
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
    //return std::string(indent,' ')+std::string(indent,' ');//2 space indent
    return indent>0?"| "+get_indent(indent-1):"";
}

void print_expression(int,std::shared_ptr<Parser::Expression>);
void print_line(int,std::shared_ptr<Parser::Line>);
void print_expression_term(int,std::shared_ptr<Parser::ExpressionTerm>);
void print_variable_definition(int indent,std::shared_ptr<Parser::VariableDefinition> def);
void print_var_type(int indent,std::shared_ptr<Parser::VarType> type);

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
    std::cout<<get_indent(indent+1)<<call->identifier<<"\n";
    std::cout<<get_indent(indent)<<".arguments:\n";
    if(call->arguments==nullptr){
        std::cout<<get_indent(indent+1)<<"No Args\n";
    }else{
        print_expression_list(indent+1,call->arguments);
    }
}

void print_keyword_function_call(int indent,std::shared_ptr<Parser::KeywordFunctionCall> call){
    std::cout<<get_indent(indent)<<">Keyword Function Call\n";
    std::cout<<get_indent(indent)<<".identifier:\n";
    print_token(indent+1,call->identifier);
    std::cout<<get_indent(indent)<<".extra_type:\n";
    print_var_type(indent+1,call->extra_type);
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

void print_unary_operation(int indent,std::shared_ptr<Parser::UnaryOperation> op){
    std::cout<<get_indent(indent)<<">Pre Unary Operation\n";
    std::cout<<get_indent(indent)<<".term:\n";
    print_expression_term(indent+1,op->term);
    std::cout<<get_indent(indent)<<".operator:\n";
    print_token(indent+1,op->unary_operator);
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
    case Parser::EXPRESSION_TERM_KEYWORD_FUNCTION_CALL:
        std::cout<<get_indent(indent)<<".keyword function call:\n";
        print_keyword_function_call(indent+1,std::static_pointer_cast<Parser::KeywordFunctionCall>(term->contents_p));
        break;
    case Parser::EXPRESSION_TERM_UNARY_OPERATION:
        std::cout<<get_indent(indent)<<".unary operation:\n";
        print_unary_operation(indent+1,std::static_pointer_cast<Parser::UnaryOperation>(term->contents_p));
        break;
    case Parser::EXPRESSION_TERM_LITERAL_INT:
        std::cout<<get_indent(indent)<<".literal (int):\n";
        print_token(indent+1,term->contents_t);
        break;
    case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
        std::cout<<get_indent(indent)<<".literal (float):\n";
        print_token(indent+1,term->contents_t);
        break;
    case Parser::EXPRESSION_TERM_LITERAL_STRING:
        std::cout<<get_indent(indent)<<".literal (string):\n";
        print_token(indent+1,term->contents_t);
        break;
    case Parser::EXPRESSION_TERM_LITERAL_TRUE:
        std::cout<<get_indent(indent)<<".literal:\n";
        std::cout<<get_indent(indent+1)<<"true\n";
        break;
    case Parser::EXPRESSION_TERM_LITERAL_FALSE:
        std::cout<<get_indent(indent)<<".literal:\n";
        std::cout<<get_indent(indent+1)<<"false\n";
        break;
    case Parser::EXPRESSION_TERM_IDENTIFIER:
        std::cout<<get_indent(indent)<<".identifier:\n";
        print_token(indent+1,term->contents_t);
        break;
    default:
        throw std::runtime_error("unknown Parser::ExpressionTerm::type value");
        break;
    }
    if(!term->unary_post_operators.empty()){
        std::cout<<get_indent(indent)<<".unary post operators:\n";
        for(size_t i=0;i<term->unary_post_operators.size();i++){
            std::cout<<get_indent(indent+1)<<".operator["<<std::to_string(i)<<"]:\n";
            print_token(indent+2,term->unary_post_operators[i]);
        }
    }
    if(!term->array_access.empty()){
        std::cout<<get_indent(indent)<<".array access:\n";
        for(size_t i=0;i<term->array_access.size();i++){
            std::cout<<get_indent(indent+1)<<".depth["<<std::to_string(i)<<"]:\n";
            print_expression(indent+2,std::static_pointer_cast<Parser::Expression>(term->array_access[i]));
        }
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
    if(stmt->pre){
        std::cout<<get_indent(indent)<<".pre:\n";
        print_expression(indent+1,stmt->pre);
    }
    if(stmt->vardef_pre){
        std::cout<<get_indent(indent)<<".pre [variable definition]:\n";
        print_variable_definition(indent+1,std::static_pointer_cast<Parser::VariableDefinition>(stmt->vardef_pre));
    }
    if(stmt->condition){
        std::cout<<get_indent(indent)<<".condition:\n";
        print_expression(indent+1,stmt->condition);
    }
    if(stmt->inc){
        std::cout<<get_indent(indent)<<".inc:\n";
        print_expression(indent+1,stmt->inc);
    }
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
    case Parser::STATEMENT_BREAK:
        std::cout<<get_indent(indent+1)<<">Break Statement\n";
        break;
    case Parser::STATEMENT_CONTINUE:
        std::cout<<get_indent(indent+1)<<">Continue Statement\n";
        break;
    }
}

void print_primitive(int indent,Parser::ParserPrimitiveType_t primitive){
    switch(primitive){
    case Parser::PRIMITIVE_ANY:
        std::cout<<get_indent(indent)<<"[PRIMITIVE] any\n";
        break;
    case Parser::PRIMITIVE_POINTER:
        std::cout<<get_indent(indent)<<"[PRIMITIVE] pointer\n";
        break;
    case Parser::PRIMITIVE_TYPE:
        std::cout<<get_indent(indent)<<"[PRIMITIVE] type\n";
        break;
    case Parser::PRIMITIVE_CHAR:
        std::cout<<get_indent(indent)<<"[PRIMITIVE] char\n";
        break;
    case Parser::PRIMITIVE_INT:
        std::cout<<get_indent(indent)<<"[PRIMITIVE] int\n";
        break;
    case Parser::PRIMITIVE_FLOAT:
        std::cout<<get_indent(indent)<<"[PRIMITIVE] float\n";
        break;
    case Parser::PRIMITIVE_STRING:
        std::cout<<get_indent(indent)<<"[PRIMITIVE] string\n";
        break;
    case Parser::PRIMITIVE_INVALID:
        std::cout<<get_indent(indent)<<"[INVALID PRIMITIVE TYPE]\n";
        break;
    }
}

void print_var_type(int indent,std::shared_ptr<Parser::VarType> type){
    std::cout<<get_indent(indent)<<">Variable Type\n";
    std::cout<<get_indent(indent)<<".type:\n";
    switch(type->type){
        case Parser::VARTYPE_PRIMITIVE:
            print_primitive(indent+1,type->primitive);
            break;
        default:
            //no more types, in the future TODO
            break;
    }
    if(type->array_sizes.size()>0){
        std::cout<<get_indent(indent)<<".array type:\n";
        for(size_t i=0;i<type->array_sizes.size();i++){
            std::cout<<get_indent(indent+1)<<".layer["<<std::to_string(i)<<"]:\n";
            print_expression(indent+2,std::static_pointer_cast<Parser::Expression>(type->array_sizes[i]));
        }
    }
}

void print_function_definition_parameter(int indent,std::shared_ptr<Parser::FunctionDefinitionParameter> param){
    std::cout<<get_indent(indent)<<">Parameter\n";
    std::cout<<get_indent(indent)<<".type:\n";
    print_var_type(indent+1,param->type);
    std::cout<<get_indent(indent)<<".name:\n";
    std::cout<<get_indent(indent+1)<<param->name<<"\n";
}

void print_function_definition(int indent,std::shared_ptr<Parser::FunctionDefinition> func){
    std::cout<<get_indent(indent)<<">Function Definition\n";
    std::cout<<get_indent(indent)<<".return type:\n";
    print_var_type(indent+1,func->return_type);
    std::cout<<get_indent(indent)<<".name:\n";
    std::cout<<get_indent(indent+1)<<func->name<<"\n";
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
    std::cout<<get_indent(indent+1)<<item->name<<"\n";
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
