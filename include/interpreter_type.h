#ifndef INTERPRETER_TYPE_H
#define INTERPRETER_TYPE_H

#include <memory>
#include "parser_var_type.h"
#include "interpreter_value.h"
#include "interpreter_variable.h"


namespace Interpreter {

    class Type {
    public:
        static std::shared_ptr<Type> any_type();
        static std::shared_ptr<Type> void_type();
        static std::shared_ptr<Type> bool_type();
        static std::shared_ptr<Type> char_type();
        static std::shared_ptr<Type> unsigned_char_type();
        static std::shared_ptr<Type> int_type();
        static std::shared_ptr<Type> unsigned_int_type();
        static std::shared_ptr<Type> float_type();
        static std::shared_ptr<Type> string_type();
        static std::shared_ptr<Type> class_type(class DefaultFrame * context,std::string name);
        static std::shared_ptr<Type> from_vartype(class DefaultFrame * context,std::shared_ptr<Parser::VarType>);
        virtual std::string get_name()=0;
        virtual bool is(std::shared_ptr<Type> self,std::shared_ptr<Type> other);
        virtual std::shared_ptr<Value> make_value(std::shared_ptr<Type> self);
        virtual std::shared_ptr<Variable> make_variable(std::shared_ptr<Type> self,std::string name);
        virtual std::shared_ptr<Value> get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other);
        virtual std::shared_ptr<Value> get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre);
        virtual std::shared_ptr<Value> call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other);
        virtual std::shared_ptr<Value> call_unary_operator(int op,std::shared_ptr<Value> self,bool pre);
        virtual bool allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other);
        virtual bool has_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other);
        virtual std::shared_ptr<Value> cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other);
    protected:
        static std::shared_ptr<Type> from_vartype_ignore_array(class DefaultFrame * context,std::shared_ptr<Parser::VarType> t);
        static std::shared_ptr<Type> any_type_instance;
        static std::shared_ptr<Type> void_type_instance;
        static std::shared_ptr<Type> bool_type_instance;
        static std::shared_ptr<Type> char_type_instance;
        static std::shared_ptr<Type> unsigned_char_type_instance;
        static std::shared_ptr<Type> int_type_instance;
        static std::shared_ptr<Type> unsigned_int_type_instance;
        static std::shared_ptr<Type> float_type_instance;
        static std::shared_ptr<Type> string_type_instance;
    };
}

#endif // INTERPRETER_TYPE_H
