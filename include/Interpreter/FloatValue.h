#ifndef INTERPRETER_FLOAT_VALUE_H
#define INTERPRETER_FLOAT_VALUE_H

#include "Interpreter/PrimitiveValue.h"
#include "Interpreter/Type.h"
#include "Printf/ValueContainer.h"

namespace Interpreter {
    class FloatValue : public virtual PrimitiveValue , public virtual Printf::DoubleContainer{
        public:
            virtual double getDouble() override;
            
            FloatValue(double);
            operator double&();
            double &get();
            virtual std::shared_ptr<Type> get_type() override;
            virtual std::shared_ptr<Value> clone() override;
            virtual std::shared_ptr<class Variable> clone_var(std::string new_name) override;
            //operators
            
            //comparison
            virtual std::shared_ptr<Value> gt(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> lt(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> eq(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> neq(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> gt_eq(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> lt_eq(std::shared_ptr<Value>&) override;
            
            //operations
            virtual std::shared_ptr<Value> add(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> sub(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> mul(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> div(std::shared_ptr<Value>&) override;
            
            //assignment
            virtual std::shared_ptr<Value> assign(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> assign_add(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> assign_sub(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> assign_mul(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> assign_div(std::shared_ptr<Value>&) override;
            
            //unary
            virtual std::shared_ptr<Value> unary_pre_plus() override;
            virtual std::shared_ptr<Value> unary_pre_minus() override;
    };
}

#endif // INTERPRETER_FLOAT_VALUE_H
