#ifndef Value_H
#define Value_H

#include <memory>
#include "printf_value_container.h"

namespace Interpreter {
    class Value : public virtual Printf::ValueContainer {
        public:
            virtual std::shared_ptr<class Type> get_type()=0;
            virtual std::shared_ptr<Value> clone()=0;
            virtual std::shared_ptr<class Variable> clone_var(std::string new_name)=0;//clone into a variable
            //operators
            
            //special
            virtual std::shared_ptr<Value> access_array(std::shared_ptr<Value>&);
            
            //comparison
            virtual std::shared_ptr<Value> gt(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> lt(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> eq(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> neq(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> gt_eq(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> lt_eq(std::shared_ptr<Value>&);
            
            //operations
            virtual std::shared_ptr<Value> mod(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> bitwise_and(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> bitwise_or(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> bitwise_xor(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> logical_and(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> logical_or(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> add(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> sub(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> mul(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> div(std::shared_ptr<Value>&);
            
            //assignment
            virtual std::shared_ptr<Value> assign(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> assign_add(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> assign_sub(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> assign_mul(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> assign_div(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> assign_mod(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> assign_bitwise_and(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> assign_bitwise_or(std::shared_ptr<Value>&);
            virtual std::shared_ptr<Value> assign_bitwise_xor(std::shared_ptr<Value>&);
            
            //unary
            
            virtual std::shared_ptr<Value> unary_pre_plus();
            virtual std::shared_ptr<Value> unary_pre_minus();
            virtual std::shared_ptr<Value> unary_pre_logical_not();
            virtual std::shared_ptr<Value> unary_pre_increment();
            virtual std::shared_ptr<Value> unary_pre_decrement();
            virtual std::shared_ptr<Value> unary_post_increment();
            virtual std::shared_ptr<Value> unary_post_decrement();
    };
}

#endif // Value_H
