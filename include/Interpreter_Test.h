#ifndef INTERPRETER_TEST_H
#define INTERPRETER_TEST_H

#include <map>
#include <vector>

#include "parser_definition.h"
#include "parser_function_definition.h"
#include "parser_variable_definition.h"

namespace Interpreter {

    class Interpreter_Frame;

    class Function_Call {
    public:
        virtual std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters()=0;
        virtual std::shared_ptr<Interpreter_Frame> build_frame()=0;
        virtual void call(std::shared_ptr<Interpreter_Frame>)=0;
    };

    class Interpreted_Function_Call : public Function_Call {
    public:
        Interpreted_Function_Call(std::shared_ptr<Parser::FunctionDefinition>);
        std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override;
        void call(std::shared_ptr<Interpreter_Frame>) override;
    private:
        std::shared_ptr<Parser::FunctionDefinition> function;
        std::shared_ptr<Interpreter_Frame> template_frame;
    };

    class Native_Function_Call : public Function_Call {//to be inherited from
        std::shared_ptr<Interpreter_Frame> build_frame();
    };

    struct Interpreter_Frame{
        public:
            Interpreter_Frame(std::shared_ptr<Interpreter_Frame>);
            Interpreter_Frame(std::vector<std::shared_ptr<Parser::Definition>>);
            Interpreter_Frame(std::shared_ptr<Parser::FunctionDefinition>);
            Interpreter_Frame(Interpreter_Frame * parent,std::shared_ptr<Parser::CodeBlock>);
            std::shared_ptr<Interpreter_Frame> parent;
            std::shared_ptr<Parser::Line> code;
            std::map<std::string,std::shared_ptr<Interpreted_Function_Call>> interpreted_functions;
            std::map<std::string,std::shared_ptr<Native_Function_Call>> native_functions;
            std::map<std::string,std::shared_ptr<Parser::VarType>> variable_types;
            std::map<std::string,int> int_values;
            std::map<std::string,float> float_values;
            std::map<std::string,std::string> string_values;
            std::shared_ptr<Parser::VarType> find_variable_type(std::string);
            int get_int_variable(std::string);
            void set_int_variable(std::string,int);
            float get_float_variable(std::string);
            void set_float_variable(std::string,float);
            std::string get_string_variable(std::string);
            void set_string_variable(std::string,std::string);
            std::shared_ptr<Function_Call> get_function(std::string);
    };

    class Interpreter_Test{
        public:
            Interpreter_Test(std::vector<std::shared_ptr<Parser::Definition>> deflist);
            void run(std::string entrypoint="main");
            void register_function(std::shared_ptr<Native_Function_Call>);
        protected:
            void enterFrame(std::shared_ptr<Interpreter_Frame>);
            Interpreter_Frame global_frame;
        private:
    };
}
#endif // INTERPRETER_TEST_H
