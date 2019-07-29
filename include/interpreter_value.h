#ifndef Value_H
#define Value_H

#include <memory>
#include "parser_var_type.h"
//#include "interpreter_type.h"

namespace Interpreter {
    class Value {
        public:
            virtual std::shared_ptr<class Type> get_type()=0;
            //operators
            
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
    };
}

#endif // Value_H
