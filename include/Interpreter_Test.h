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
#include "parser_function_call.h"
#include "parser_expression_group.h"
#include "parser_expression_term.h"

namespace Interpreter {

    class Interpreter_Line_Run_Result {
        virtual void dummy_virtual(){};
        //base class
    };

    class Interpreter_Line {
        public:
            virtual std::shared_ptr<Interpreter_Line_Run_Result> run(std::shared_ptr<Interpreter_ExecFrame> context)=0;
            //base class
    };

    class Interpreter_Line_Run_Result_None : public Interpreter_Line_Run_Result {
        
    };

    class Interpreter_Line_Run_Result_Break : public Interpreter_Line_Run_Result {
        
    };

    class Interpreter_Line_Run_Result_Continue : public Interpreter_Line_Run_Result {
        
    };

    class Interpreter_Line_Run_Result_Return : public Interpreter_Line_Run_Result {
        public:
            Interpreter_Line_Run_Result_Return(std::shared_ptr<Interpreter_Value>);
            std::shared_ptr<Interpreter_Value> value;
    };

    class Interpreter_ExpressionPart{
            //base class
        public:
            virtual std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<Interpreter_Frame> context)=0;
            virtual std::shared_ptr<Interpreter_Value> eval(std::shared_ptr<Interpreter_ExecFrame> context)=0;
    };

    class Interpreter_Code : public Interpreter_Line {
        public:
            Interpreter_Code(Interpreter_Frame * parent,std::shared_ptr<Parser::CodeBlock>);
            Interpreter_Code(Interpreter_Frame * parent,std::shared_ptr<Parser::Line>);
            std::shared_ptr<Interpreter_Line_Run_Result> run(std::shared_ptr<Interpreter_ExecFrame> context) override;
            std::shared_ptr<Interpreter_Frame> default_frame;
            std::vector<std::shared_ptr<Interpreter_Line>> code;
        private:
            void readLine(std::shared_ptr<Parser::Line>);
    };

    class Interpreter_ExpressionPart_Operator : public Interpreter_ExpressionPart{
        public:
            Interpreter_ExpressionPart_Operator(int);
            std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<Interpreter_Frame> context) override;
            std::shared_ptr<Interpreter_Value> eval(std::shared_ptr<Interpreter_ExecFrame> context) override;
            int op;
    };

    class Interpreter_ExpressionPart_FunctionCall : public Interpreter_ExpressionPart{
        public:
            Interpreter_ExpressionPart_FunctionCall(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::FunctionCall>);
            std::shared_ptr<Interpreter_Value> call(std::shared_ptr<Interpreter_ExecFrame> context);
            std::shared_ptr<Function_Call> get(std::shared_ptr<Interpreter_ExecFrame> context);
            std::shared_ptr<Function_Call> get(std::shared_ptr<Interpreter_Frame> context);
            std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<Interpreter_Frame> context) override;
            std::shared_ptr<Interpreter_Value> eval(std::shared_ptr<Interpreter_ExecFrame> context) override;
            std::string ident;
            std::vector<std::shared_ptr<Interpreter_Expression>> arguments;
    };

    class Interpreter_ExpressionPart_Variable : public Interpreter_ExpressionPart{
        public:
            Interpreter_ExpressionPart_Variable(std::shared_ptr<Interpreter_Frame> context,std::string ident);
            std::shared_ptr<Interpreter_Variable> get(std::shared_ptr<Interpreter_Frame> context);
            std::shared_ptr<Interpreter_Variable> get(std::shared_ptr<Interpreter_ExecFrame> context);
            std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<Interpreter_Frame> context) override;
            std::shared_ptr<Interpreter_Value> eval(std::shared_ptr<Interpreter_ExecFrame> context) override;
            std::string ident;
    };

    class Interpreter_ExpressionPart_Value : public Interpreter_ExpressionPart{
        public:
            Interpreter_ExpressionPart_Value(int);
            Interpreter_ExpressionPart_Value(double);
            Interpreter_ExpressionPart_Value(std::string);
            std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<Interpreter_Frame> context) override;
            std::shared_ptr<Interpreter_Value> eval(std::shared_ptr<Interpreter_ExecFrame> context) override;
            std::shared_ptr<Interpreter_Value> value;
    };

    class Interpreter_Expression : public Interpreter_Line {
            void add_term(std::shared_ptr<Interpreter_Frame>,std::shared_ptr<Parser::ExpressionTerm>);
            void add_expression(std::shared_ptr<Interpreter_Frame>,std::shared_ptr<Parser::Expression>);
            std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Interpreter_ExpressionPart>);
            std::shared_ptr<Parser::VarType> check_op(std::shared_ptr<Interpreter_Frame>,std::stack<std::shared_ptr<Interpreter_ExpressionPart>>&,std::shared_ptr<Interpreter_ExpressionPart_Operator>);
            std::shared_ptr<Parser::VarType> check(std::shared_ptr<Interpreter_Frame>);//check for errors, validity
            std::shared_ptr<Interpreter_Value> eval_op(std::shared_ptr<Interpreter_ExecFrame> context,std::stack<std::shared_ptr<Interpreter_ExpressionPart>>&,std::shared_ptr<Interpreter_ExpressionPart_Operator>);
        public:
            Interpreter_Expression(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::Expression>);
            std::shared_ptr<Interpreter_Value> eval(std::shared_ptr<Interpreter_ExecFrame> context);//parent_frame's defauls must be the same as the context the expression was built with
            std::shared_ptr<Interpreter_Line_Run_Result> run(std::shared_ptr<Interpreter_ExecFrame> context) override;
            std::stack<std::shared_ptr<Interpreter_ExpressionPart>> expression;
            std::shared_ptr<Parser::VarType> final_type;
    };

    class Interpreter_IfStatement : public Interpreter_Line {
        public:
            Interpreter_IfStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::IfStatement>);
            std::shared_ptr<Interpreter_Line_Run_Result> run(std::shared_ptr<Interpreter_ExecFrame> context) override;
            std::shared_ptr<Interpreter_Expression> condition;
            std::shared_ptr<Interpreter_Code> code;
            std::shared_ptr<Interpreter_Code> else_stmt;
    };

    class Interpreter_ForStatement : public Interpreter_Line {
        public:
            Interpreter_ForStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::ForStatement>);
            std::shared_ptr<Interpreter_Line_Run_Result> run(std::shared_ptr<Interpreter_ExecFrame> context) override;
            std::shared_ptr<Interpreter_Expression> pre;
            std::shared_ptr<Interpreter_Expression> condition;
            std::shared_ptr<Interpreter_Expression> inc;
            std::shared_ptr<Interpreter_Code> code;
    };

    class Interpreter_WhileStatement : public Interpreter_Line {
        public:
            Interpreter_WhileStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::WhileStatement>);
            std::shared_ptr<Interpreter_Line_Run_Result> run(std::shared_ptr<Interpreter_ExecFrame> context) override;
            std::shared_ptr<Interpreter_Expression> condition;
            std::shared_ptr<Interpreter_Code> code;
    };

    class Interpreter_ReturnStatement : public Interpreter_Line {
        public:
            Interpreter_ReturnStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::ReturnStatement>);
            std::shared_ptr<Interpreter_Line_Run_Result> run(std::shared_ptr<Interpreter_ExecFrame> context) override;
            std::shared_ptr<Interpreter_Expression> value;
    };

    class Function_Call {
        public:
            virtual std::string get_name()=0;
            virtual std::shared_ptr<Parser::VarType> get_type()=0;
            virtual std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters()=0;
            virtual std::shared_ptr<Interpreter_Value> call(std::shared_ptr<Interpreter_ExecFrame> parent_frame,std::map<std::string,std::shared_ptr<Interpreter_Value>> args)=0;
    };

    class Native_Function_Call : public Function_Call {//to be inherited from
    };

    class Interpreted_Function_Call : public Function_Call {
        public:
            Interpreted_Function_Call(Interpreter_Frame * parent,std::shared_ptr<Parser::FunctionDefinition>);
            std::string get_name() override;
            std::shared_ptr<Parser::VarType> get_type() override;
            std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override;
            std::shared_ptr<Interpreter_Value> call(std::shared_ptr<Interpreter_ExecFrame>,std::map<std::string,std::shared_ptr<Interpreter_Value>> args) override;
        private:
            std::shared_ptr<Parser::FunctionDefinition> function;
            std::shared_ptr<Interpreter_Frame> frame;
    };

    class Interpreter_Test{
        public:
            Interpreter_Test(std::vector<std::shared_ptr<Parser::Definition>> deflist);
            static void run(std::shared_ptr<Interpreter_ExecFrame> exframe,std::string entrypoint="main");
            void run(std::string entrypoint="main");
            void register_function(std::shared_ptr<Native_Function_Call>);
        protected:
            void build_frame(std::vector<std::shared_ptr<Parser::Definition>>);
            //void enterFrame(std::shared_ptr<Interpreter_Frame>);
            //std::vector<std::shared_ptr<Parser::Definition>> deflist;
            std::shared_ptr<Interpreter_Frame> frame;
        private:
    };

}
#endif // INTERPRETER_TEST_H
