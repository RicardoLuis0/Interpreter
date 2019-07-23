#ifndef INTERPRETER_TYPE_H
#define INTERPRETER_TYPE_H

#include <memory>
#include "parser_var_type.h"

namespace Interpreter {

    enum type_type_t {
        TYPE_INVALID,
        TYPE_VOID,
        TYPE_PRIMITIVE,
        TYPE_CLASS,//TODO Type for class
    };

    enum type_primitive_type_t {
        PRIMITIVE_INVALID,
        PRIMITIVE_INT,
        PRIMITIVE_FLOAT,
        PRIMITIVE_STRING,
    };

    class Type {//TODO? maybe convert to virtual methods+inheritance
    public:
        static std::shared_ptr<Type> void_type();
        static std::shared_ptr<Type> primitive_type(type_primitive_type_t);
        static std::shared_ptr<Type> class_type();
        static std::shared_ptr<Type> from_vartype(std::shared_ptr<Parser::VarType>);
        Type(type_type_t=TYPE_INVALID,type_primitive_type_t=PRIMITIVE_INVALID);
        type_type_t type;
        type_primitive_type_t primitive;
        std::string get_name();
        bool is_void();
        bool is_primitive();
        bool is_int();
        bool is_float();
        bool is_num();
        bool is_string();
        bool is_compatible(std::shared_ptr<Type>);
        bool is_equal(std::shared_ptr<Type>);
    protected:
        //bool is_a_class();
        //bool is_class(class_type);
    };

}

#endif // INTERPRETER_TYPE_H
