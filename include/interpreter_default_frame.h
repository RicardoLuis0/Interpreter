#ifndef DEFAULTFRAME_H
#define DEFAULTFRAME_H

#include "parser_definition.h"
#include "parser_code_block.h"
#include "parser_var_type.h"
#include "parser_variable_definition_item.h"
#include "parser_function_definition.h"

#include "interpreter_value.h"
#include "interpreter_variable.h"

#include <map>
#include <memory>

class Interpreted_Function_Call;//TODO
class Native_Function_Call;//TODO
class Function_Call;//TODO

namespace Interpreter{
    class DefaultFrame{
        public:
            DefaultFrame(std::vector<std::shared_ptr<Parser::Definition>>);//make global scope
            DefaultFrame(DefaultFrame * parent,Interpreted_Function_Call * call,std::shared_ptr<Parser::CodeBlock>);
            DefaultFrame(DefaultFrame * parent,std::shared_ptr<Parser::CodeBlock>);
            DefaultFrame(DefaultFrame * parent);
            DefaultFrame * parent;
            std::map<std::string,std::shared_ptr<Interpreted_Function_Call>> interpreted_functions;
            std::map<std::string,std::shared_ptr<Native_Function_Call>> native_functions;
            std::map<std::string,std::shared_ptr<Variable>> variable_defaults;
            std::map<std::string,int> int_values;
            std::map<std::string,float> float_values;
            std::map<std::string,std::string> string_values;
            std::shared_ptr<Variable> get_variable(std::string);
            std::shared_ptr<Function_Call> get_function(std::string);
            void read_parameters(std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>>);
            void register_native_function(std::shared_ptr<Native_Function_Call> func);
            void add_variable(std::shared_ptr<Parser::VarType> type,std::shared_ptr<Parser::VariableDefinitionItem> var,bool global=false);
            void add_function(std::shared_ptr<Parser::FunctionDefinition>);
            void add_definition(std::shared_ptr<Parser::Definition>,bool global=false);
    };
}

#endif // DEFAULTFRAME_H
