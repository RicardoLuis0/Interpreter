#ifndef DEFAULTFRAME_H
#define DEFAULTFRAME_H

#include "parser_definition.h"
#include "parser_code_block.h"
#include "parser_var_type.h"
#include "parser_variable_definition_item.h"
#include "parser_function_definition.h"

#include "interpreter_function.h"
//#include "interpreter_user_function.h"
#include "interpreter_native_function.h"
#include "interpreter_value.h"
#include "interpreter_variable.h"

#include <map>
#include <memory>

namespace Interpreter{
    class DefaultFrame{
        protected:
        public:
            DefaultFrame(std::vector<std::shared_ptr<Parser::Definition>>);//make global scope
            DefaultFrame(DefaultFrame * parent,Function * func);//Function func must be of type UserFunction
            DefaultFrame(DefaultFrame * parent);
            DefaultFrame * parent;
            std::map<std::string,std::shared_ptr<Function>> functions;
            std::map<std::string,std::shared_ptr<Variable>> variable_defaults;
            std::map<std::string,int> int_values;
            std::map<std::string,float> float_values;
            std::map<std::string,std::string> string_values;
            std::shared_ptr<Variable> get_variable(std::string);
            std::shared_ptr<Function> get_function(std::string);
            void register_native_function(std::shared_ptr<NativeFunction> func);
            void add_parameters(std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>>);
            void add_variable(std::shared_ptr<Parser::VarType> type,std::shared_ptr<Parser::VariableDefinitionItem> var,bool global=false);
            void add_function(std::shared_ptr<Parser::FunctionDefinition>);
            void add_definition(std::shared_ptr<Parser::Definition>,bool global=false,void(*expr_callback)(void*,std::shared_ptr<Parser::VariableDefinitionItem>)=nullptr,void * callback_arg=nullptr);//expr_callback called when there's an expression definition in VariableDefinitionItem
    };
}


#endif // DEFAULTFRAME_H
