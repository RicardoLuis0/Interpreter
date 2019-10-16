#ifndef INTERPRETER_ARRAY_TYPE_H
#define INTERPRETER_ARRAY_TYPE_H

#include "interpreter_type.h"
#include "interpreter_expression.h"
#include "interpreter_exec_frame.h"

namespace Interpreter {
    class ArrayType : public Type {
    public:
        ArrayType(std::shared_ptr<Type>,int,bool is_const=false);
        ArrayType(std::shared_ptr<Type>,std::shared_ptr<Expression> expr,bool is_const=false);
        std::shared_ptr<Type> change_const(std::shared_ptr<Type> self,bool new_const) override;
        std::shared_ptr<Value> get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end) override;
        std::shared_ptr<Value> call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other) override;
        bool allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other) override;
        std::shared_ptr<Value> cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other) override;
        std::shared_ptr<Value> make_value(std::shared_ptr<Type> self) override;
        std::shared_ptr<Variable> make_variable(std::shared_ptr<Type> self,std::string name) override;
        std::string get_name() override;
        bool is(std::shared_ptr<Type> self,std::shared_ptr<Type> other) override;
        std::shared_ptr<Type> get_type();
        int get_size();
        bool is_vla();
        std::shared_ptr<ArrayType> build_vla_array_type(ExecFrame * context);
    private:
        std::shared_ptr<Type> type;
        int size;
        std::shared_ptr<Expression> len_expr;
    };
}

#endif // INTERPRETER_ARRAY_TYPE_H
