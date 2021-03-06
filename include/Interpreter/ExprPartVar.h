#ifndef INTERPRETER_EXPR_PART_VAR_H
#define INTERPRETER_EXPR_PART_VAR_H

#include "Interpreter/ExprPart.h"

namespace Interpreter {
    class ExprPartVar : public ExprPart {
        public:
            ExprPartVar(DefaultFrame * context,std::string,int line,bool ignore_const=false);
            std::shared_ptr<Value> get_dummy_type() override;
            std::shared_ptr<Type> get_type() override;
            std::shared_ptr<Value> eval(ExecFrame * context) override;
            std::shared_ptr<Type> type;
            std::string ident;
    };
}

#endif // INTERPRETER_EXPR_PART_VAR_H
