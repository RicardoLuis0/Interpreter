#ifndef INTERPRETER_TYPE_H
#define INTERPRETER_TYPE_H

#include <memory>
#include "parser_var_type.h"
#include "interpreter_value.h"
#include "interpreter_variable.h"


namespace Interpreter {

    class Type {
    public:
        static std::shared_ptr<Type> any_type(bool is_const=false);
        static std::shared_ptr<Type> type_type(bool is_const=false);
        static std::shared_ptr<Type> void_type(bool is_const=false);
        static std::shared_ptr<Type> char_type(bool is_const=false);
        static std::shared_ptr<Type> unsigned_char_type(bool is_const=false);
        static std::shared_ptr<Type> int_type(bool is_const=false);
        static std::shared_ptr<Type> unsigned_int_type(bool is_const=false);
        static std::shared_ptr<Type> float_type(bool is_const=false);
        static std::shared_ptr<Type> string_type(bool is_const=false);
        static std::shared_ptr<Type> from_vartype(class DefaultFrame * context,std::shared_ptr<Parser::VarType>);
        Type(bool is_const=false);
        virtual std::shared_ptr<Type> change_const(std::shared_ptr<Type> self,bool new_const)=0;
        virtual std::string get_name()=0;
        virtual bool is(std::shared_ptr<Type> self,std::shared_ptr<Type> other);
        virtual std::shared_ptr<Value> make_value(std::shared_ptr<Type> self);
        virtual std::shared_ptr<Variable> make_variable(std::shared_ptr<Type> self,std::string name);
        virtual std::shared_ptr<Value> get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end);
        virtual std::shared_ptr<Value> get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end);
        virtual std::shared_ptr<Value> call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other);
        virtual std::shared_ptr<Value> call_unary_operator(int op,std::shared_ptr<Value> self,bool pre);
        virtual bool allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other);
        virtual bool has_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other);
        virtual std::shared_ptr<Value> cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other);
    protected:
        void check_variable_assignment(int op,std::shared_ptr<Value> self,int line_start,int line_end);
        static std::shared_ptr<Type> from_vartype_ignore_array(class DefaultFrame * context,std::shared_ptr<Parser::VarType> t);
        static std::shared_ptr<Type> any_type_instance;
        static std::shared_ptr<Type> type_type_instance;
        static std::shared_ptr<Type> void_type_instance;
        static std::shared_ptr<Type> char_type_instance;
        static std::shared_ptr<Type> unsigned_char_type_instance;
        static std::shared_ptr<Type> int_type_instance;
        static std::shared_ptr<Type> unsigned_int_type_instance;
        static std::shared_ptr<Type> float_type_instance;
        static std::shared_ptr<Type> string_type_instance;
        static std::shared_ptr<Type> const_any_type_instance;
        static std::shared_ptr<Type> const_type_type_instance;
        static std::shared_ptr<Type> const_void_type_instance;
        static std::shared_ptr<Type> const_char_type_instance;
        static std::shared_ptr<Type> const_unsigned_char_type_instance;
        static std::shared_ptr<Type> const_int_type_instance;
        static std::shared_ptr<Type> const_unsigned_int_type_instance;
        static std::shared_ptr<Type> const_float_type_instance;
        static std::shared_ptr<Type> const_string_type_instance;
        bool is_const;
        friend class Expression;
    };
}

#endif // INTERPRETER_TYPE_H
