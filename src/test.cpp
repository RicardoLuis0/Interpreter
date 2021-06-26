#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Util/read_file.h"
#include "Lexer/Lexer.h"
#include "Lexer/WordToken.h"
#include "MyExcept/MyExcept.h"
#include "symbols_keywords.h"
#include "Util/Console.h"
#include "Parser/Definition.h"
#include "Interpreter/DefaultFrame.h"
#include "Interpreter/ExecFrame.h"
#include "Interpreter/IntValue.h"

static int exec(std::string filename){
    std::string data;
    read_file(filename,data);
    Lexer::Lexer lexer(base_symbols,base_keywords);
    std::vector<std::shared_ptr<Lexer::Token>> tokens(lexer.tokenize_from_string(filename,data));
    Console::changeDir(filename.substr(0,std::max(filename.rfind("/"),filename.rfind("\\"))));
    std::vector<std::shared_ptr<Parser::Definition>> deflist;
    Parser::parserProgress p(tokens);
    //get imports
    std::vector<std::string> imports({"default"});
    while(p.isKeyword(KEYWORD_IMPORT)){
        do{
            if(p.isSymbol(SYMBOL_SEMICOLON)){
                continue;
            }else if(p.isSymbol(SYMBOL_MULTIPLY)){
                imports.push_back("*");
            }else if(std::shared_ptr<Lexer::WordToken> tk=std::static_pointer_cast<Lexer::WordToken>(p.isType(Lexer::TOKEN_TYPE_WORD))){
                imports.push_back(tk->get_literal());
            }else{
                throw MyExcept::NoMatchException(p.get_line(),"expected library name, got '"+p.get_nothrow_nonull()->get_literal()+"'");
            }
        }while(p.isSymbol(SYMBOL_COMMA));
        if(!p.isSymbol(SYMBOL_SEMICOLON)){
            throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");
        }
    }
    while(p.get_nothrow()!=nullptr){
        deflist.push_back(std::make_shared<Parser::Definition>(p));
    }
    Interpreter::DefaultFrame dframe(deflist,imports);
    std::shared_ptr<Interpreter::ExecFrame> eframe(std::make_shared<Interpreter::ExecFrame>(nullptr,&dframe));
    std::shared_ptr<Interpreter::Function> entrypoint(eframe->get_function("main",{}));
    std::vector<std::shared_ptr<Interpreter::Value>> fn_args;
    auto t=entrypoint->get_type();
    if(t->is(t,Interpreter::Type::void_type())){
        return 0;
    }else{
        if(!t->allows_implicit_cast(t,Interpreter::Type::int_type())){
            return 0;
        }
        auto r=eframe->fn_call(entrypoint,{});
        return std::dynamic_pointer_cast<Interpreter::IntValue>(r->get_type()->cast(r,Interpreter::Type::int_type()))->get();
    }
}

struct test{
    std::string name;
    std::string path;
    bool expected_fail;
};

std::vector<test> tests {
    {"If/Else Statement\t...\t","Tests/If.txt",false},
    {"While Statement\t\t...\t","Tests/While.txt",false},
    {"Break Statement\t\t...\t","Tests/Break.txt",false},
    {"Continue Statement\t...\t","Tests/Continue.txt",false},
    {"For Statement 1\t\t...\t","Tests/For1.txt",false},
    {"For Statement 2\t\t...\t","Tests/For2.txt",false},
    {"For Statement 3\t\t...\t","Tests/For3.txt",false},
    {"For Statement 4\t\t...\t","Tests/For4.txt",false},
    {"Nested Functions\t...\t","Tests/Nested.txt",false},
    {"Const 1\t\t\t...\t","Tests/Const1.txt",false},
    {"Const 2\t\t\t...\t","Tests/Const2.txt",true},
    {"Const 3\t\t\t...\t","Tests/Const3.txt",true},
    {"Array 1\t\t\t...\t","Tests/Arr1.txt",false},
    {"Array 2\t\t\t...\t","Tests/Arr2.txt",false},
    {"Vector 1\t\t...\t","Tests/Vector1.txt",false},
    {"Vector 2\t\t...\t","Tests/Vector2.txt",false},
    {"Vector 3\t\t...\t","Tests/Vector3.txt",false},
    {"Pointer 1\t\t...\t","Tests/Ptr1.txt",false},
    {"Pointer 2\t\t...\t","Tests/Ptr2.txt",false},
    {"Type 1\t\t\t...\t","Tests/Type1.txt",false},
    {"Type 2\t\t\t...\t","Tests/Type2.txt",false},
    {"TypeOf 1\t\t...\t","Tests/TypeOf1.txt",false},
    {"TypeOf 2\t\t...\t","Tests/TypeOf2.txt",false},
    {"Is Expression\t\t...\t","Tests/Is.txt",false},
};

int main(){
    for(auto t:tests){
        std::cout<<t.name;
        try{
            if((exec(t.path)>0)!=t.expected_fail){
                std::cout<<"   Ok\n";
            }else{
                std::cout<<"  Fail\n";
            }
        }catch(MyExcept::FileError &){
            std::cout<<"No File\n";
        }catch(...){
            if(t.expected_fail){
                std::cout<<"   Ok\n";
            }else{
                std::cout<<"  Fail\n";
            }
        }
    }
}
