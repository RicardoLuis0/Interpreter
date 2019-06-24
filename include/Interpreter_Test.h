#ifndef INTERPRETER_TEST_H
#define INTERPRETER_TEST_H

#include <map>
#include <vector>

#include "parser_definition.h"
#include "parser_function_definition.h"
#include "parser_variable_definition.h"
#include "parser_if_statement.h"
#include "parser_for_statement.h"
#include "parser_while_statement.h"
#include "parser_return_statement.h"

namespace Interpreter {

    class Interpreter_Frame;

    class Interpreter_Line {
        
    };

    class Interpreter_Code {
        public:
            Interpreter_Code(std::shared_ptr<Interpreter_Frame> parent,std::shared_ptr<Parser::CodeBlock>);
            Interpreter_Code(std::shared_ptr<Interpreter_Frame> parent,std::shared_ptr<Parser::Line>);
            std::shared_ptr<Interpreter_Frame> default_frame;
            std::vector<std::shared_ptr<Interpreter_Line>> code;
        private:
            void readLine(std::shared_ptr<Parser::Line>);
    };

    class Interpreter_Expression : public Interpreter_Line {
        public:
            Interpreter_Expression(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::Expression>);
            std::shared_ptr<Parser::Expression> expr;
    };

    class Interpreter_Block : public Interpreter_Line {
        public:
            Interpreter_Block(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::CodeBlock>);
            std::shared_ptr<Interpreter_Code> code;
    };

    class Interpreter_IfStatement : public Interpreter_Line {
        public:
            Interpreter_IfStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::IfStatement>);
            std::shared_ptr<Parser::Expression> condition;
            std::shared_ptr<Interpreter_Code> code;
    };

    class Interpreter_ForStatement : public Interpreter_Line {
        public:
            Interpreter_ForStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::ForStatement>);
            std::shared_ptr<Parser::Expression> pre;
            std::shared_ptr<Parser::Expression> condition;
            std::shared_ptr<Parser::Expression> inc;
            std::shared_ptr<Interpreter_Code> code;
    };

    class Interpreter_WhileStatement : public Interpreter_Line {
        public:
            Interpreter_WhileStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::WhileStatement>);
            std::shared_ptr<Parser::Expression> condition;
            std::shared_ptr<Interpreter_Code> code;
    };

    class Interpreter_ReturnStatement : public Interpreter_Line {
        public:
            Interpreter_ReturnStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::ReturnStatement>);
            std::shared_ptr<Parser::Expression> value;
    };

    class Interpreter_Variable{
        public:
            std::string get_name();
            virtual std::shared_ptr<Parser::VarType> get_type()=0;
        protected:
            std::string name;
    };

    class Int_Variable : public Interpreter_Variable {
        public:
            operator int&();
            int &get();
            std::shared_ptr<Parser::VarType> get_type() override;
        protected:
            int value;
    };

    class Float_Variable : public Interpreter_Variable {
        public:
            operator double&();
            double &get();
            std::shared_ptr<Parser::VarType> get_type() override;
        protected:
            double value;
    };

    class String_Variable : public Interpreter_Variable {
        public:
            operator std::string&();
            std::string &get();
            std::shared_ptr<Parser::VarType> get_type() override;
        protected:
            std::string value;
    };

    class Function_Call {
        public:
            virtual std::string get_name()=0;
            virtual std::shared_ptr<Parser::VarType> get_type()=0;
            virtual std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters()=0;
            virtual std::shared_ptr<Interpreter_Variable> call(std::shared_ptr<Interpreter_Frame> parent_frame,std::map<std::string,std::shared_ptr<Interpreter_Variable>> args)=0;
    };

    class Interpreted_Function_Call;

    class Native_Function_Call : public Function_Call {//to be inherited from
    };

    class Interpreter_Frame{
        public:
            Interpreter_Frame();//empty
            //Interpreter_Frame(std::shared_ptr<Parser::FunctionDefinition>);
            Interpreter_Frame(std::vector<std::shared_ptr<Parser::Definition>>);//make global scope
            //Interpreter_Frame(Interpreter_Frame * parent,std::shared_ptr<Parser::Line>);
            //Interpreter_Frame(Interpreter_Frame * parent,std::shared_ptr<Parser::CodeBlock>);
            Interpreter_Frame(std::shared_ptr<Interpreter_Frame> parent);
            Interpreter_Frame(std::shared_ptr<Interpreter_Frame> parent,std::shared_ptr<Interpreter_Frame>);//copy
            std::shared_ptr<Interpreter_Frame> parent;
            std::map<std::string,std::shared_ptr<Interpreted_Function_Call>> interpreted_functions;
            std::map<std::string,std::shared_ptr<Native_Function_Call>> native_functions;
            std::map<std::string,std::shared_ptr<Interpreter_Variable>> variable_defaults;
            std::map<std::string,std::shared_ptr<Interpreter_Variable>> variables;
            std::map<std::string,int> int_values;
            std::map<std::string,float> float_values;
            std::map<std::string,std::string> string_values;
            std::shared_ptr<Interpreter_Variable> get_variable(std::string);
            std::shared_ptr<Function_Call> get_function(std::string);
            void register_native_function(std::shared_ptr<Native_Function_Call> func);
            void add_variable(std::shared_ptr<Parser::VarType> type,std::shared_ptr<Parser::VariableDefinitionItem> var,bool global=false);
            void add_function(std::shared_ptr<Parser::FunctionDefinition>);
            void add_definition(std::shared_ptr<Parser::Definition>,bool global=false);
    };

    class Interpreted_Function_Call : public Function_Call {
        public:
            Interpreted_Function_Call(std::shared_ptr<Parser::FunctionDefinition>);
            std::string get_name() override;
            std::shared_ptr<Parser::VarType> get_type() override;
            std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override;
            std::shared_ptr<Interpreter_Variable> call(std::shared_ptr<Interpreter_Frame>,std::map<std::string,std::shared_ptr<Interpreter_Variable>> args) override;
        private:
            std::shared_ptr<Parser::FunctionDefinition> function;
    };

    class Interpreter_Test{
        public:
            Interpreter_Test(std::vector<std::shared_ptr<Parser::Definition>> deflist);
            static void run(std::shared_ptr<Interpreter_Frame> global_frame,std::string entrypoint="main");
            std::shared_ptr<Interpreter_Frame> build_frame();
            void run(std::string entrypoint="main");
            void register_function(std::shared_ptr<Native_Function_Call>);
        protected:
            //void enterFrame(std::shared_ptr<Interpreter_Frame>);
            std::vector<std::shared_ptr<Parser::Definition>> deflist;
        private:
    };
}
#endif // INTERPRETER_TEST_H
