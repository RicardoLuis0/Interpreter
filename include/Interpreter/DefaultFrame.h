#ifndef DEFAULTFRAME_H
#define DEFAULTFRAME_H

#include "Parser/Definition.h"
#include "Parser/CodeBlock.h"
#include "Parser/VarType.h"
#include "Parser/VariableDefinitionItem.h"
#include "Parser/VariableDefinition.h"
#include "Parser/FunctionDefinition.h"

#include "Interpreter/Function.h"
#include "Interpreter/Value.h"
#include "Interpreter/Variable.h"
#include "Interpreter/Struct.h"

#include <unordered_map>
#include <memory>

namespace Interpreter{
    struct fnparam_vec_hash{
        inline size_t operator()(std::vector<FunctionParameter>const &param) const{
            static std::hash<std::string> hash_func;
            return hash_func(FunctionParameter::get_typelist(param));
        }
    };
    class DefaultFrame{
        public:
            inline bool is_library_imported(std::string name){
                for(std::string lib:imported_libraries){
                    if(lib==name)return true;
                }
                return false;
            }
            std::vector<std::string> imported_libraries;//keep track of libraries, to prevent double importing
            std::vector<std::shared_ptr<class Expression>> initialize_globals;
            DefaultFrame(DefaultFrame * parent,std::shared_ptr<Parser::VariableDefinition>);//make for statement definition context
            DefaultFrame(std::vector<std::shared_ptr<Parser::Definition>>,std::vector<std::string> library_imports);//make global scope
            DefaultFrame(DefaultFrame * parent,Function * func);//Function func must be of type UserFunction
            DefaultFrame(DefaultFrame * parent);
            DefaultFrame * parent;
            std::shared_ptr<DefaultFrame> static_frame;
            std::shared_ptr<ExecFrame> static_exec_frame;
            std::unordered_map<std::string,std::unordered_map<std::vector<FunctionParameter>,std::shared_ptr<Function>,fnparam_vec_hash>> functions;
            std::unordered_map<std::string,std::shared_ptr<Type>> variable_types;
            std::unordered_map<std::string,std::shared_ptr<Struct>> structs;
            std::unordered_map<std::string,int> int_values;
            std::unordered_map<std::string,float> float_values;
            std::unordered_map<std::string,std::string> string_values;
            std::shared_ptr<Type> get_variable_type(std::string);
            std::vector<std::vector<FunctionParameter>> get_function_variants(std::string);
            std::shared_ptr<Struct> get_struct(std::string);
            std::shared_ptr<Function> get_function(std::string,std::vector<FunctionParameter>);
            std::shared_ptr<Function> get_function_local(std::string,std::vector<FunctionParameter>);
            std::shared_ptr<class Expression> vardefitem_to_assignment(std::shared_ptr<Parser::VariableDefinitionItem> vardef);
            bool is_function=false;
            Function * self_function=nullptr;
            void register_function(std::shared_ptr<Function> func);
            void add_parameters(std::vector<FunctionParameter>);
            void add_variable(std::shared_ptr<Type> type,std::shared_ptr<Parser::VariableDefinitionItem> var,bool global=false);
            void add_function(std::shared_ptr<Parser::FunctionDefinition>,bool global);
            void add_definition(std::shared_ptr<Parser::Definition>,bool global=false,void(*expr_callback)(void*,std::shared_ptr<Parser::VariableDefinitionItem>,std::shared_ptr<Type>,bool)=nullptr,void * callback_arg=nullptr);//expr_callback called when there's an expression definition in VariableDefinitionItem
    };
}


#endif // DEFAULTFRAME_H
