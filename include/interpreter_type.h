#ifndef INTERPRETER_TYPE_H
#define INTERPRETER_TYPE_H

#include <memory>
#include "parser_var_type.h"
#include "interpreter_value.h"
#include "interpreter_variable.h"

namespace Interpreter {

    class Type {
    public:
        static std::shared_ptr<Type> void_type();
        static std::shared_ptr<Type> int_type();
        static std::shared_ptr<Type> float_type();
        static std::shared_ptr<Type> string_type();
        static std::shared_ptr<Type> class_type(class DefaultFrame * context,std::string name);
        static std::shared_ptr<Type> from_vartype(std::shared_ptr<Parser::VarType>);
        virtual std::shared_ptr<Value> make_value()=0;
        virtual std::shared_ptr<Variable> make_variable(std::string name)=0;
        virtual std::string get_name();
        virtual std::shared_ptr<Value> get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other)=0;
        virtual std::shared_ptr<Value> get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre)=0;
        virtual std::shared_ptr<Value> call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other)=0;
        virtual std::shared_ptr<Value> call_unary_operator(int op,std::shared_ptr<Value> self,bool pre)=0;
        virtual bool allows_implicit_cast(std::shared_ptr<Type> other);
        virtual bool has_cast(std::shared_ptr<Type> other);
        virtual std::shared_ptr<Value> cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other);
    protected:
        static std::shared_ptr<Type> void_type_instance;
        static std::shared_ptr<Type> int_type_instance;
        static std::shared_ptr<Type> float_type_instance;
        static std::shared_ptr<Type> string_type_instance;
    };
}

#endif // INTERPRETER_TYPE_H
