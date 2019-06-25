#ifndef INTERPRETER_TEST_H
#define INTERPRETER_TEST_H

#include <map>
#include <vector>
#include <stack>

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

    class Interpreter_ExpressionPart{
        //base class
    };

    class Interpreter_ExpressionPart_Operator : public Interpreter_ExpressionPart{
        public:
            Interpreter_ExpressionPart_Operator(int);
            int op;
    };

    class Interpreter_Value{
        public:
            virtual std::shared_ptr<Parser::VarType> get_type()=0;
    };

    class Interpreter_Variable : public virtual Interpreter_Value{
        public:
            std::string get_name();
        protected:
            std::string name;
    };

    class Interpreter_ExecFrame;

    class Interpreter_Expression : public Interpreter_Line {
        public:
            Interpreter_Expression(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::Expression>);
            std::shared_ptr<Interpreter_Value> execute(std::shared_ptr<Interpreter_ExecFrame> parent_frame);//parent_frame's defauls must be the same as the context the expression was built with
            void check_op(std::shared_ptr<Interpreter_Frame>,std::stack<std::shared_ptr<Interpreter_ExpressionPart>>&,std::shared_ptr<Interpreter_ExpressionPart_Operator>);
            void check(std::shared_ptr<Interpreter_Frame>);//check for errors, validity
            std::shared_ptr<Parser::Expression> expr;
            std::stack<std::shared_ptr<Interpreter_ExpressionPart>> expression;
            std::shared_ptr<Parser::VarType> final_type;
    };

    class Interpreter_ExpressionPart_Expression : public Interpreter_ExpressionPart, public Interpreter_Expression {
        Interpreter_ExpressionPart_Expression(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::Expression>);
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

    class Int_Value : public virtual Interpreter_Value {
        public:
            Int_Value(int);
            operator int&();
            int &get();
            std::shared_ptr<Parser::VarType> get_type() override;
        protected:
            int value;
    };

    class Int_Variable : public virtual Int_Value , public virtual Interpreter_Variable {
        public:
            Int_Variable(int);
    };

    class Float_Value : public virtual Interpreter_Value {
        public:
            Float_Value(double);
            operator double&();
            double &get();
            std::shared_ptr<Parser::VarType> get_type() override;
        protected:
            double value;
    };

    class Float_Variable : public virtual Float_Value , public virtual Interpreter_Variable {
        public:
            Float_Variable(double);
    };

    class String_Value : public virtual Interpreter_Value {
        public:
            String_Value(std::string);
            operator std::string&();
            std::string &get();
            std::shared_ptr<Parser::VarType> get_type() override;
        protected:
            std::string value;
    };

    class String_Variable : public virtual String_Value , public virtual Interpreter_Variable {
        public:
            String_Variable(std::string);
    };

    class Function_Call;

    class Interpreter_ExecFrame{
        public:
            Interpreter_ExecFrame(std::shared_ptr<Interpreter_ExecFrame> parent,std::shared_ptr<Interpreter_Frame> defaults);
            std::shared_ptr<Interpreter_ExecFrame> parent;
            std::shared_ptr<Interpreter_Frame> defaults;
            std::map<std::string,std::shared_ptr<Interpreter_Variable>> variables;
            std::shared_ptr<Interpreter_Variable> get_variable(std::string);
            std::shared_ptr<Function_Call> get_function(std::string);
    };

    class Function_Call {
        public:
            virtual std::string get_name()=0;
            virtual std::shared_ptr<Parser::VarType> get_type()=0;
            virtual std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters()=0;
            virtual std::shared_ptr<Interpreter_Value> call(std::shared_ptr<Interpreter_ExecFrame> parent_frame,std::map<std::string,std::shared_ptr<Interpreter_Value>> args)=0;
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
            Interpreter_Frame(Interpreted_Function_Call * call,std::shared_ptr<Interpreter_Frame> parent,std::shared_ptr<Parser::CodeBlock>);
            Interpreter_Frame(std::shared_ptr<Interpreter_Frame> parent,std::shared_ptr<Parser::CodeBlock>);
            Interpreter_Frame(std::shared_ptr<Interpreter_Frame> parent);
            std::shared_ptr<Interpreter_Frame> parent;
            std::map<std::string,std::shared_ptr<Interpreted_Function_Call>> interpreted_functions;
            std::map<std::string,std::shared_ptr<Native_Function_Call>> native_functions;
            std::map<std::string,std::shared_ptr<Interpreter_Variable>> variable_defaults;
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
            std::shared_ptr<Interpreter_Value> call(std::shared_ptr<Interpreter_ExecFrame>,std::map<std::string,std::shared_ptr<Interpreter_Value>> args) override;
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
