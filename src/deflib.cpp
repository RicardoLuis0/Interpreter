#include "deflib.h"
#include <iostream>
#include "interpreter_function.h"
#include "parser_var_type.h"
#include "interpreter_string_value.h"

namespace Interpreter {
    class puts : public Function {

        std::string get_name() override {
            return "puts";
        }

        std::shared_ptr<Parser::VarType> get_type() override {
            return std::make_shared<Parser::VarType>(Parser::VARTYPE_VOID);
        }

        std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override {
            return {std::make_shared<Parser::FunctionDefinitionParameter>(std::make_shared<Parser::VarType>(Parser::PRIMITIVE_STRING),"str")};
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
            std::getline(std::cin,temp,'\n');
            return std::make_shared<StringValue>(temp);
        }
    };
}

void Interpreter::init_deflib(DefaultFrame * d){
    d->register_function(std::make_shared<Interpreter::puts>());
    d->register_function(std::make_shared<Interpreter::getline>());
}
