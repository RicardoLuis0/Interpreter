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
