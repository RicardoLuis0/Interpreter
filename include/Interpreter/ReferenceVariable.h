#ifndef REFERENCEVARIABLE_H
#define REFERENCEVARIABLE_H

#include "Interpreter/Variable.h"
#include "Interpreter/ReferenceType.h"

namespace Interpreter {

    class ReferenceVariable : public Variable {
        public:
            ReferenceVariable(std::string name,std::shared_ptr<ReferenceType> type,std::shared_ptr<Variable> value);
            virtual std::shared_ptr<Type> get_type() override;
            virtual std::shared_ptr<Value> clone() override;
            virtual std::shared_ptr<Variable> clone_var(std::string new_name) override;
            std::string get_orig_name();
            std::shared_ptr<Type> get_orig_type();
            std::shared_ptr<Variable> get_value();
        protected:
            friend class ReferenceType;
            std::shared_ptr<Variable> value;
            std::shared_ptr<ReferenceType> type;
    };

}

#endif // REFERENCEVARIABLE_H
