#ifndef INTERPRETER_UNSIGNED_INT_VALUE_H
#define INTERPRETER_UNSIGNED_INT_VALUE_H

#include "interpreter_primitive_value.h"
#include "interpreter_type.h"

namespace Interpreter {
    class UnsignedIntValue : public virtual PrimitiveValue {
        public:
            UnsignedIntValue(unsigned int);
            operator unsigned int&();
            unsigned int &get();
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
            virtual std::shared_ptr<Value> mod(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> bitwise_and(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> bitwise_or(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> bitwise_xor(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> logical_and(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> logical_or(std::shared_ptr<Value>&) override;
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
            virtual std::shared_ptr<Value> assign_mod(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> assign_bitwise_and(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> assign_bitwise_or(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> assign_bitwise_xor(std::shared_ptr<Value>&) override;
            
            //unary
            virtual std::shared_ptr<Value> unary_pre_plus() override;
            virtual std::shared_ptr<Value> unary_pre_minus() override;
            virtual std::shared_ptr<Value> unary_pre_logical_not() override;
            virtual std::shared_ptr<Value> unary_pre_increment() override;
            virtual std::shared_ptr<Value> unary_pre_decrement() override;
            virtual std::shared_ptr<Value> unary_post_increment() override;
            virtual std::shared_ptr<Value> unary_post_decrement() override;
            
    };
}

#endif // INTERPRETER_UNSIGNED_INT_VALUE_H
