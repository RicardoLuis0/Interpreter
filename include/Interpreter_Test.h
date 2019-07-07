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

    class Interpreter_Frame;
    class Interpreter_Expression;
    class Interpreter_Variable;
    class Interpreter_Value;
    class Interpreter_ExecFrame;
    class Function_Call;
    class Interpreted_Function_Call;

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

    class Int_Value;

    class Interpreter_Value{
        public:
            virtual std::shared_ptr<Int_Value> gt(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> lt(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> eq(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> neq(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> gt_eq(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> lt_eq(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> mod(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> bitwise_and(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> bitwise_or(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> bitwise_xor(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> logical_and(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Int_Value> logical_or(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> add(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> sub(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> mul(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> div(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> assign(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> assign_add(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> assign_sub(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> assign_mul(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> assign_div(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> assign_mod(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> assign_bitwise_and(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> assign_bitwise_or(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Interpreter_Value> assign_bitwise_xor(std::shared_ptr<Interpreter_Value>&);
            virtual std::shared_ptr<Parser::VarType> get_type()=0;
    };

    class Interpreter_Variable : public virtual Interpreter_Value {
        public:
            std::string get_name();
        protected:
            std::string name;
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

    class Int_Value : public virtual Interpreter_Value {
        public:
            Int_Value(int);
            operator int&();
            int &get();
            virtual std::shared_ptr<Parser::VarType> get_type() override;
            /*
            virtual std::shared_ptr<Interpreter_Value> add(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> sub(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> mul(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> div(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> assign(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> assign_add(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> assign_sub(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> assign_mul(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> assign_div(std::shared_ptr<Interpreter_Value>&) override;
            */
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
            virtual std::shared_ptr<Parser::VarType> get_type() override;
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
            virtual std::shared_ptr<Parser::VarType> get_type() override;
            virtual std::shared_ptr<Int_Value> eq(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Int_Value> neq(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> assign(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> assign_add(std::shared_ptr<Interpreter_Value>&) override;
            virtual std::shared_ptr<Interpreter_Value> add(std::shared_ptr<Interpreter_Value>&) override;
        protected:
            std::string value;
    };

    class String_Variable : public virtual String_Value , public virtual Interpreter_Variable {
        public:
            String_Variable(std::string);
    };

    class Interpreter_ExecFrame{
        public:
            Interpreter_ExecFrame(std::shared_ptr<Interpreter_ExecFrame> parent,std::shared_ptr<Interpreter_Frame> defaults);
            std::shared_ptr<Interpreter_ExecFrame> parent;
            std::shared_ptr<Interpreter_Frame> defaults;
            std::map<std::string,std::shared_ptr<Interpreter_Variable>> variables;
            std::shared_ptr<Interpreter_Variable> get_variable(std::string);
            void add_args(std::map<std::string,std::shared_ptr<Interpreter_Value>>);
            std::shared_ptr<Function_Call> get_function(std::string);
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

    class Interpreter_Frame{
        public:
            Interpreter_Frame();//empty
            //Interpreter_Frame(std::shared_ptr<Parser::FunctionDefinition>);
            Interpreter_Frame(std::vector<std::shared_ptr<Parser::Definition>>);//make global scope
            //Interpreter_Frame(Interpreter_Frame * parent,std::shared_ptr<Parser::Line>);
            Interpreter_Frame(Interpreter_Frame * parent,Interpreted_Function_Call * call,std::shared_ptr<Parser::CodeBlock>);
            Interpreter_Frame(Interpreter_Frame * parent,std::shared_ptr<Parser::CodeBlock>);
            Interpreter_Frame(Interpreter_Frame * parent);
            Interpreter_Frame * parent;
            std::map<std::string,std::shared_ptr<Interpreted_Function_Call>> interpreted_functions;
            std::map<std::string,std::shared_ptr<Native_Function_Call>> native_functions;
            std::map<std::string,std::shared_ptr<Interpreter_Variable>> variable_defaults;
            std::map<std::string,int> int_values;
            std::map<std::string,float> float_values;
            std::map<std::string,std::string> string_values;
            std::shared_ptr<Interpreter_Variable> get_variable(std::string);
            std::shared_ptr<Function_Call> get_function(std::string);
            void read_parameters(std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>>);
            void register_native_function(std::shared_ptr<Native_Function_Call> func);
            void add_variable(std::shared_ptr<Parser::VarType> type,std::shared_ptr<Parser::VariableDefinitionItem> var,bool global=false);
            void add_function(std::shared_ptr<Parser::FunctionDefinition>);
            void add_definition(std::shared_ptr<Parser::Definition>,bool global=false);
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
