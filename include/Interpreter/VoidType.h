#ifndef INTERPRETER_VOID_TYPE_H
#define INTERPRETER_VOID_TYPE_H

#include "Interpreter/Type.h"

namespace Interpreter {
    class VoidType : public Type {
    public:
        VoidType(bool is_const=false);
        std::shared_ptr<Type> change_const(std::shared_ptr<Type> self,bool new_const) override;
        std::string get_name() override;
        bool is(std::shared_ptr<Type> self,std::shared_ptr<Type> other) override;
    };
}

#endif // INTERPRETER_VOID_TYPE_H
