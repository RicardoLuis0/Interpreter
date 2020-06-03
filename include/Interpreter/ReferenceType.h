#ifndef REFERENCETYPE_H
#define REFERENCETYPE_H

#include "Interpreter/Type.h"

namespace Interpreter {
    class ReferenceType : public Type {
        public:
            ReferenceType(std::shared_ptr<Type> type,bool is_const=false);
            std::shared_ptr<Type> change_const(std::shared_ptr<Type> self,bool new_const) override;
            std::shared_ptr<Value> get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end) override;
            std::shared_ptr<Value> get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end) override;
            std::shared_ptr<Value> call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other) override;
            std::shared_ptr<Value> call_unary_operator(int op,std::shared_ptr<Value> self,bool pre) override;
            std::shared_ptr<Value> cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other) override;
            std::shared_ptr<Value> make_value(std::shared_ptr<Type> self) override;
            std::shared_ptr<Variable> make_variable(std::shared_ptr<Type> self,std::string name) override;
            std::string get_name() override;
            bool is(std::shared_ptr<Type> self,std::shared_ptr<Type> other) override;
            std::shared_ptr<Type> get_type();
        private:
            friend class ReferenceVariable;
            std::shared_ptr<Type> type;
    };
}

#endif // REFERENCETYPE_H
