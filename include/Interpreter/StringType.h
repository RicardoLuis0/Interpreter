#ifndef INTERPRETER_STRING_TYPE_H
#define INTERPRETER_STRING_TYPE_H

#include "Interpreter/Type.h"

namespace Interpreter {
    class StringType : public Type {
    public:
        StringType(bool is_const=false);
        std::shared_ptr<Type> change_const(std::shared_ptr<Type> self,bool new_const) override;
        std::shared_ptr<Value> get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end) override;
        std::shared_ptr<Value> call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other) override;
        std::shared_ptr<Value> cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other) override;
        std::shared_ptr<Value> make_value(std::shared_ptr<Type> self) override;
        std::shared_ptr<Variable> make_variable(std::shared_ptr<Type> self,std::string name) override;
        bool is(std::shared_ptr<Type> self,std::shared_ptr<Type> other) override;
        std::string get_name() override;
    };
}


#endif // INTERPRETER_STRING_TYPE_H
