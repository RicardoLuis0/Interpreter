#include "deflib.h"
#include <iostream>
#include "interpreter_function.h"
#include "parser_var_type.h"
#include "interpreter_string_value.h"
#include "interpreter_int_value.h"

//NOTE native functions to make later
//void printf(string format,mixed ... args)
//void puts(string) DONE
//void putc(int) 
//string getline() DONE
//int stoi(string) DONE
//float stof(string)
//string itos(int) DONE
//string ftos(float)
//void cls() DONE

namespace Interpreter {
    class puts : public Function {

        std::string get_name() override {
            return "puts";
        }

        std::shared_ptr<Parser::VarType> get_type() override {
            return std::make_shared<Parser::VarType>(Parser::VARTYPE_VOID);
        }

        std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override {
            return {std::make_shared<Parser::FunctionDefinitionParameter>(std::make_shared<Parser::VarType>(Parser::PRIMITIVE_STRING),"str",false)};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            std::cout<<std::dynamic_pointer_cast<StringValue>(args[0])->get();
            return nullptr;
        }

    };

    class getline : public Function{

        std::string get_name() override {
            return "getline";
        }

        std::shared_ptr<Parser::VarType> get_type(){
            return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_STRING);
        }

        std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override {
            return {};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            std::string temp;
            while(std::cin.peek()=='\n')std::cin.ignore();
            std::getline(std::cin,temp,'\n');
            return std::make_shared<StringValue>(temp);
        }
    };

    class stoi : public Function{

        std::string get_name() override {
            return "stoi";
        }

        std::shared_ptr<Parser::VarType> get_type(){
            return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_INT);
        }

        std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override {
            return {std::make_shared<Parser::FunctionDefinitionParameter>(std::make_shared<Parser::VarType>(Parser::PRIMITIVE_STRING),"str",false)};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<IntValue>(std::stoi(std::dynamic_pointer_cast<StringValue>(args[0])->get()));
        }
    };

    class itos : public Function{

        std::string get_name() override {
            return "itos";
        }

        std::shared_ptr<Parser::VarType> get_type(){
            return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_STRING);
        }

        std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override {
            return {std::make_shared<Parser::FunctionDefinitionParameter>(std::make_shared<Parser::VarType>(Parser::PRIMITIVE_INT),"int",false)};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<StringValue>(std::to_string(std::dynamic_pointer_cast<IntValue>(args[0])->get()));
        }
    };

    class cls : public Function{

        std::string get_name() override {
            return "cls";
        }

        std::shared_ptr<Parser::VarType> get_type(){
            return std::make_shared<Parser::VarType>(Parser::VARTYPE_VOID);
        }

        std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override {
            return {};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            system("cls");
            return nullptr;
        }
    };

}

void Interpreter::init_deflib(DefaultFrame * d){
    d->register_function(std::make_shared<Interpreter::puts>());
    d->register_function(std::make_shared<Interpreter::getline>());
    d->register_function(std::make_shared<Interpreter::stoi>());
    d->register_function(std::make_shared<Interpreter::itos>());
    d->register_function(std::make_shared<Interpreter::cls>());
}
