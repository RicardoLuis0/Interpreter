#ifndef INTERPRETER_FUNCTION_H
#define INTERPRETER_FUNCTION_H

#include "Parser/VarType.h"
#include "Interpreter/Value.h"
#include "Parser/FunctionDefinitionParameter.h"
#include "Interpreter/LineResult.h"
#include "Interpreter/FunctionParameter.h"

namespace Interpreter {
    class Function {
        public:
            virtual std::string get_name()=0;
            virtual inline int get_line(){
                return 0;
            }

            virtual inline bool is_variadic(){
                return false;
            }

            virtual inline std::shared_ptr<Type> get_variadic_type(){
                return nullptr;
            }

            virtual std::shared_ptr<Type> get_type()=0;
            virtual std::vector<FunctionParameter> get_parameters()=0;
            virtual std::shared_ptr<Value> call(class ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args)=0;
    };
}

#endif // INTERPRETER_FUNCTION_H
