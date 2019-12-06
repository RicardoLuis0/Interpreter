#include <iostream>
#include <string>
#include <vector>
#include "Util/read_file.h"
#include "Lexer/Lexer.h"
#include "Lexer/WordToken.h"
#include "MyExcept/MyExcept.h"
#include "symbols_keywords.h"
#include "Util/Console.h"
#include "Parser/DefinitionMatcher.h"
#include "Interpreter/DefaultFrame.h"
#include "Interpreter/ExecFrame.h"
#include "Interpreter/IntValue.h"

int exec(std::string filename){
    std::string data;
    read_file(filename,data);
    Lexer::Lexer lexer(base_symbols,base_keywords);
    std::vector<std::shared_ptr<Lexer::Token>> tokens(lexer.tokenize_from_string(filename,data));
    Console::changeDir(filename.substr(0,std::max(filename.rfind("/"),filename.rfind("\\"))));
    std::vector<std::shared_ptr<Parser::Definition>> deflist;
    Parser::parserProgress p(tokens);
    while(p.get_nothrow()!=nullptr){
        deflist.push_back(Parser::DefinitionMatcher().makeMatch(p));
    }
    Interpreter::DefaultFrame dframe(deflist,{"*"});
    std::shared_ptr<Interpreter::ExecFrame> eframe(std::make_shared<Interpreter::ExecFrame>(nullptr,&dframe));
    std::shared_ptr<Interpreter::Function> entrypoint(eframe->get_function("main",{}));
    std::vector<std::shared_ptr<Interpreter::Value>> fn_args;
    auto t=entrypoint->get_type();
    if(t->is(t,Interpreter::Type::void_type())){
        eframe->fn_call(entrypoint,{});
        return 0;
    }else{
        if(!t->allows_implicit_cast(t,Interpreter::Type::int_type())){
            throw std::runtime_error("'main()' function must return 'int' or 'void'");
        }
        auto r=eframe->fn_call(entrypoint,{});
        return std::dynamic_pointer_cast<Interpreter::IntValue>(r->get_type()->cast(r,Interpreter::Type::int_type()))->get();
    }
}

struct test{
    std::string name;
    std::string path;
};

std::vector<test> tests {
    {"If/Else Statement\t...\t","Tests/If.txt"},
    {"While Statement\t\t...\t","Tests/While.txt"},
    {"Break Statement\t\t...\t","Tests/Break.txt"},
    {"Continue Statement\t...\t","Tests/Continue.txt"},
    {"For Statement 1\t\t...\t","Tests/For1.txt"},
    {"For Statement 2\t\t...\t","Tests/For2.txt"},
    {"For Statement 3\t\t...\t","Tests/For3.txt"},
    {"For Statement 4\t\t...\t","Tests/For4.txt"},
};

int main(){
    for(auto t:tests){
        std::cout<<t.name;
        try{
            if(exec(t.path)){
                std::cout<<" Ok\n";
                continue;
            }
        }catch(...){
        }
        std::cout<<"Fail\n";
    }
}
