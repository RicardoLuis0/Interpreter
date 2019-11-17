#include <iostream>
#include "MyExcept/MyExcept.h"
#include "Lexer/Lexer.h"
#include "Util/Console.h"
#include "symbols_keywords.h"

#include "Parser/Parser.h"
#include "Parser/ExpressionMatcher.h"
#include "Parser/LineMatcher.h"
#include "Parser/Expression.h"
#include "Parser/ExpressionList.h"
#include "Parser/ExpressionGroup.h"
#include "Parser/ExpressionTerm.h"
#include "Parser/BinaryOperation.h"
#include "Parser/FunctionCall.h"
#include "Parser/KeywordFunctionCall.h"
#include "Parser/IfStatement.h"
#include "Parser/ForStatement.h"
#include "Parser/WhileStatement.h"
#include "Parser/Statement.h"
#include "Parser/Line.h"
#include "Parser/CodeBlock.h"
#include "Parser/Definition.h"
#include "Parser/VarType.h"
#include "Parser/VariableDefinition.h"
#include "Parser/FunctionDefinition.h"
#include "Parser/FunctionDefinitionParameter.h"
#include "Parser/ReturnStatement.h"
#include "Parser/DefinitionMatcher.h"
#include "Parser/UnaryOperation.h"
#include "Interpreter/DefaultFrame.h"
#include "Interpreter/ExecFrame.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "Interpreter/CodeBlock.h"
#include "Interpreter/IntValue.h"
#include "Interpreter/VoidType.h"
#include "Interpreter/IntType.h"
#include "Interpreter/ArrayType.h"
#include "Interpreter/ArrayValue.h"
#include "Interpreter/ArrayVariable.h"
#include "Interpreter/StringValue.h"
#include "Interpreter/LineResultReturn.h"
#include "deflib.h"
#include "Util/read_file.h"
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "preprocessor.h"

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

int simple_exec_string(std::string filename,std::string &data,int argc,char ** argv,int offset,int str_offset=0){
    Lexer::Lexer lexer(base_symbols,base_keywords);
    std::vector<std::shared_ptr<Lexer::Token>> tokens(lexer.tokenize_from_string(filename,data));
    Parser::parserProgress p(tokens);
    std::vector<std::shared_ptr<Parser::Line>> linedeflist;
    while(p.get_nothrow()!=nullptr){
        linedeflist.push_back(Parser::LineMatcher().makeMatch(p));
    }
    std::shared_ptr<Interpreter::DefaultFrame> run_frame(std::make_shared<Interpreter::DefaultFrame>(nullptr));
    Interpreter::import_all(run_frame.get());//import everything
    std::vector<std::shared_ptr<Interpreter::Line>> lines;
    run_frame->variable_types["args"]=std::make_shared<Interpreter::ArrayType>(Interpreter::Type::string_type(),-1);
    std::shared_ptr<Interpreter::CodeBlock> cb(std::make_shared<Interpreter::CodeBlock>(run_frame.get(),std::make_shared<Parser::CodeBlock>(linedeflist,0,p.get_line())));
    run_frame->variable_types.erase("args");
    std::shared_ptr<Interpreter::ExecFrame> run_exec_frame(std::make_shared<Interpreter::ExecFrame>(nullptr,run_frame.get()));
    std::shared_ptr<Interpreter::ExecFrame> cb_exec_frame=cb->getContext(run_exec_frame.get());
    std::vector<std::shared_ptr<Interpreter::Value>> main_args;
    for(int i=offset;i<argc;i++){
        main_args.push_back(std::make_shared<Interpreter::StringValue>(argv[i]));
    }
    run_exec_frame->variables["args"]=std::make_shared<Interpreter::ArrayVariable>("args",std::make_shared<Interpreter::ArrayType>(Interpreter::Type::string_type(),main_args.size()),main_args);
    std::shared_ptr<Interpreter::LineResult> result=cb->run(cb_exec_frame.get());
    switch(result->getAction()){
    case Interpreter::ACTION_NONE:
        return 0;
    case Interpreter::ACTION_BREAK:
        throw std::runtime_error("Invalid use of 'break' statement");
    case Interpreter::ACTION_CONTINUE:
        throw std::runtime_error("Invalid use of 'continue' statement");
    case Interpreter::ACTION_RETURN:
        if(auto ret=std::dynamic_pointer_cast<Interpreter::LineResultReturn>(result)){
            auto val=ret->get();
            if(val->get_type()->allows_implicit_cast(val->get_type(),Interpreter::Type::int_type())){
                return std::dynamic_pointer_cast<Interpreter::IntValue>(val->get_type()->cast(val,Interpreter::Type::int_type()))->get();
            }else{
                throw std::runtime_error("Cannot convert return value to int");
            }
        }
    }
    throw std::runtime_error("Internal error");
}

int simple_exec(std::string filename,int argc,char ** argv,int offset){
    std::string data;
    read_file(filename,data);
    if(data.substr(0,8)=="#simple\n"){
        data=data.substr(7);
        return simple_exec_string(filename,data,argc,argv,offset);
    }else{
        return simple_exec_string(filename,data,argc,argv,offset);
    }
}

int exec(std::string filename,int argc,char ** argv){
    std::string data;
    read_file(filename,data);
    if(data.substr(0,8)=="#simple\n"){
        data=data.substr(7);
        return simple_exec_string(filename,data,argc,argv,2);
    }
    Lexer::Lexer lexer(base_symbols,base_keywords);
    std::vector<std::shared_ptr<Lexer::Token>> tokens(lexer.tokenize_from_string(filename,data));
    Console::changeDir(filename.substr(0,std::max(filename.rfind("/"),filename.rfind("\\"))));
    std::vector<std::shared_ptr<Parser::Definition>> deflist;
    Parser::parserProgress p(tokens);
    while(p.get_nothrow()!=nullptr){
        deflist.push_back(Parser::DefinitionMatcher().makeMatch(p));
    }
    Interpreter::DefaultFrame dframe(deflist,{"*"});//TODO change to import only what's asked
    std::shared_ptr<Interpreter::ExecFrame> eframe(std::make_shared<Interpreter::ExecFrame>(nullptr,&dframe));
    std::shared_ptr<Interpreter::Function> entrypoint(eframe->get_function("main",{}));
    std::vector<std::shared_ptr<Interpreter::Value>> fn_args;
    if(!entrypoint){
        entrypoint=eframe->get_function("main",{{std::make_shared<Interpreter::ArrayType>(Interpreter::Type::string_type(),-1)}});
        if(!entrypoint){
            throw std::runtime_error("missing 'main()' or 'main(string[])' function");
        }
        std::vector<std::shared_ptr<Interpreter::Value>> main_args;
        for(int i=2;i<argc;i++){
            main_args.push_back(std::make_shared<Interpreter::StringValue>(argv[i]));
        }
        fn_args.push_back(std::make_shared<Interpreter::ArrayValue>(std::make_shared<Interpreter::ArrayType>(Interpreter::Type::string_type(),main_args.size()),main_args));
    }
    if(CHECKPTR(entrypoint->get_type(),Interpreter::VoidType)){
        eframe->fn_call(entrypoint,fn_args);
        return 0;
    }else{
        if(!CHECKPTR(entrypoint->get_type(),Interpreter::IntType)){
            throw std::runtime_error("'main()' function must return 'int' or 'void'");
        }
        return std::dynamic_pointer_cast<Interpreter::IntValue>(eframe->fn_call(entrypoint,fn_args))->get();
    }
}

char unescape(char c){
    switch(c) {
    case 'a':
        return '\a';
    case 'b':
        return '\b';
    case 't':
        return '\t';
    case 'n':
        return '\n';
    case 'v':
        return '\v';
    case 'f':
        return '\f';
    case 'r':
        return '\r';
    case '\\':
        return '\\';
    case '"':
        return '\"';
    default:
        return c;
    }
}

int test_exec(){
    std::string filename;
    std::vector<std::shared_ptr<Lexer::Token>> tokens;
    std::vector<std::shared_ptr<Parser::Definition>> deflist;
    Lexer::Lexer lexer(base_symbols,base_keywords);
    Console::clear();
start:
    while(true){
    Interpreter::DefaultFrame dframe(deflist,{"*"});//TODO change to import only what's asked
        std::cout<<">";
        std::cout.flush();
        while(std::cin.peek()=='\n')std::cin.ignore();
        std::getline(std::cin,filename,'\n');
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
            Console::changeDir(filename.substr(0,std::max(filename.rfind("/"),filename.rfind("\\"))));
        }catch(MyExcept::FileError &e){
            try{
                tokens=lexer.tokenize_from_file(filename+".txt");
                Console::changeDir(filename.substr(0,std::max(filename.rfind("/"),filename.rfind("\\"))));
            }catch(MyExcept::FileError &){
                try{
                    tokens=lexer.tokenize_from_file("examples/"+filename);
                    Console::changeDir("examples");
                }catch(MyExcept::FileError &){
                    try{
                        tokens=lexer.tokenize_from_file("examples/"+filename+".txt");
                        Console::changeDir("examples");
                    }catch(MyExcept::FileError &){
                        std::cout<<e.what()<<", 'exit' 'quit' or 'q' to cancel\n";
                        continue;
                    }
                }
            }
        }
        break;
    }
    //Console::clear();
    Parser::parserProgress p(tokens);
    deflist.clear();
    while(p.get_nothrow()!=nullptr){
        deflist.push_back(Parser::DefinitionMatcher().makeMatch(p));
    }
    Interpreter::DefaultFrame dframe(deflist,{"*"});//TODO change to import only what's asked
    std::shared_ptr<Interpreter::ExecFrame> eframe(std::make_shared<Interpreter::ExecFrame>(nullptr,&dframe));
    std::shared_ptr<Interpreter::Function> entrypoint(eframe->get_function("main",{}));
    std::vector<std::shared_ptr<Interpreter::Value>> fn_args;
    if(!entrypoint){
        entrypoint=eframe->get_function("main",{{std::make_shared<Interpreter::ArrayType>(Interpreter::Type::string_type(),-1)}});
        if(!entrypoint){
            throw std::runtime_error("missing 'main()' or 'main(string[])' function");
        }
        std::cout<<filename<<"\nargumens:";
        std::string temp;
        while(std::cin.peek()=='\n')std::cin.ignore();
        std::getline(std::cin,temp,'\n');
        std::string buf;
        bool reading_string=false;
        bool reading_escape=false;
        std::vector<std::shared_ptr<Interpreter::Value>> main_args;
        for(char c:temp){
            if(reading_string){
                if(reading_escape){
                    buf+=unescape(c);
                    reading_escape=false;
                }else{
                    if(c=='\\'){
                        reading_escape=true;
                    }else if(c=='"'){
                        main_args.push_back(std::make_shared<Interpreter::StringValue>(buf));
                        buf="";
                        reading_string=false;
                    }else{
                        buf+=c;
                    }
                }
            }else if(c=='"'||c==' '){
                if(buf.size()>0)main_args.push_back(std::make_shared<Interpreter::StringValue>(buf));
                buf="";
                if(c=='"'){
                    reading_string=true;
                }
            }else{
                buf+=c;
            }
        }
        if(buf.size()>0)main_args.push_back(std::make_shared<Interpreter::StringValue>(buf));
        fn_args.push_back(std::make_shared<Interpreter::ArrayValue>(std::make_shared<Interpreter::ArrayType>(Interpreter::Type::string_type(),main_args.size()),main_args));
        std::cout<<"\n";
    }
    if(CHECKPTR(entrypoint->get_type(),Interpreter::VoidType)){
        eframe->fn_call(entrypoint,fn_args);
        std::cout<<"\n\n"<<filename<<" finished exeuction\n";
        goto start;
    }else{
        if(!CHECKPTR(entrypoint->get_type(),Interpreter::IntType)){
            throw std::runtime_error("'main' function must return 'int' or 'void'");
        }
        int retval=std::dynamic_pointer_cast<Interpreter::IntValue>(eframe->fn_call(entrypoint,fn_args))->get();
        std::cout<<"\n\n"<<filename<<" returned with value "<<std::to_string(retval)<<"\n";
        goto start;
    }
}

int main(int argc,char ** argv){
    srand(static_cast<unsigned int>(time(NULL)));
    Console::init();
    try{
        if(argc<2){
            while(true){
                Console::clear();
                std::cout<<"0> test lexer\n1> test expression parser\n2> test line parser\n3> test whole code parsing\n4> test execution\n\nChoice: ";
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
                }else{
                    continue;
                }
                return 0;
            }
        }else if(argc==3&&strcmp(argv[1],"-checkparse")==0){
            std::string filename(argv[1]);
            std::vector<std::shared_ptr<Lexer::Token>> tokens;
            Lexer::Lexer lexer(base_symbols,base_keywords);
            try{
                tokens=lexer.tokenize_from_file(filename);//split file into tokens
            }catch(MyExcept::FileError &e){
                std::cout<<e.what()<<"Could not open file '"+filename+"'";
                return 1;
            }
            Parser::parserProgress p(tokens);
            while(p.get_nothrow()!=nullptr){
                Parser::DefinitionMatcher().makeMatch(p);
            }
        std::cout<<"Parse OK";
        return 0;
        }else if(argc==3&&strcmp(argv[1],"-AST")==0){
            std::vector<std::shared_ptr<Lexer::Token>> tokens;
            std::vector<std::shared_ptr<Parser::Definition>> deflist;
            Lexer::Lexer lexer(base_symbols,base_keywords);
            tokens=lexer.tokenize_from_file(argv[2]);
            Parser::parserProgress p(tokens);
            while(p.get_nothrow()!=nullptr){
                deflist.push_back(Parser::DefinitionMatcher().makeMatch(p));
            }
            for(auto def:deflist){
                def->print(0);
                std::cout<<"\n";
            }
        }else if(argc>=3&&strcmp(argv[1],"-simple")==0){
            return simple_exec(argv[2],argc,argv,3);
        }else{
            return exec(argv[1],argc,argv);
        }
        return 0;
    }catch(MyExcept::ParseError &e){
        std::cout<<"\n\n"<<e.what();
        return 1;
    }catch(MyExcept::NoMatchException &e){
        std::cout<<"\n\n"<<e.what();
        return 1;
    }catch(MyExcept::FileError &e){
        std::cout<<"\n\n"<<e.what();
        return 1;
    }catch(std::exception &e){
        std::cout<<"\n\nunknown exception: "<<e.what();
        return 1;
    }
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
        std::cout<<"\n\n"<<e.what();
        return;
    }catch(std::exception &e){
        std::cout<<"\n\nuncaught exception: "<<e.what();
        return;
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
        Parser::parserProgress p(tokens);
        std::shared_ptr<Parser::Expression> expr=Parser::ExpressionMatcher().makeMatch(p);
        expr->print(0);
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
        Parser::parserProgress p(tokens);
        std::shared_ptr<Parser::Line> line=Parser::LineMatcher().makeMatch(p);
        line->print(0);
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
        Parser::parserProgress p(tokens);
        while(p.get_nothrow()!=nullptr){
            deflist.push_back(Parser::DefinitionMatcher().makeMatch(p));
        }
        for(auto def:deflist){
            def->print(0);
            std::cout<<"\n";
        }
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
