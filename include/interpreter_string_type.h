#ifndef INTERPRETER_STRING_TYPE_H
#define INTERPRETER_STRING_TYPE_H

#include "interpreter_int_type.h"

namespace Interpreter {
    class StringType : public PrimitiveType {
        std::shared_ptr<Value> get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other) override;
        std::shared_ptr<Value> get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre) override;
        std::shared_ptr<Value> call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other) override;
        std::shared_ptr<Value> call_unary_operator(int op,std::shared_ptr<Value> self,bool pre) override;
        bool allows_implicit_cast(std::shared_ptr<Type> other) override;
        std::shared_ptr<Value> cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other) override;
        std::shared_ptr<Value> make_value() override;
        std::shared_ptr<Variable> make_variable(std::string name) override;
        std::string get_name() override;
    };
}


#endif // INTERPRETER_STRING_TYPE_H
