#ifndef INTERPRETER_ANY_TYPE_H
#define INTERPRETER_ANY_TYPE_H

#include "Interpreter/Type.h"

namespace Interpreter {
    class AnyType : public Type {
    public:
        AnyType(bool is_const=false);
        std::shared_ptr<Type> change_const(std::shared_ptr<Type> self,bool new_const) override;
        std::shared_ptr<Value> get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end) override;
        std::shared_ptr<Value> get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end) override;
        std::shared_ptr<Value> make_value(std::shared_ptr<Type> self) override;
        std::shared_ptr<Variable> make_variable(std::shared_ptr<Type> self,std::string name) override;
        bool is(std::shared_ptr<Type> self,std::shared_ptr<Type> other) override;
        std::string get_name() override;
    };
}

#endif // INTERPRETER_ANY_TYPE_H
