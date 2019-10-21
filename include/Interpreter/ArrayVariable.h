#ifndef INTERPRETER_ARRAY_VARIABLE_H
#define INTERPRETER_ARRAY_VARIABLE_H

#include "Interpreter/ArrayValue.h"
#include "Interpreter/Variable.h"

#ifdef _MSC_VER

//disable inheritance via dominance warning for MSVC

#pragma warning( disable : 4250 )

#endif

namespace Interpreter {
    class ArrayVariable : public virtual Variable , public virtual ArrayValue {
        public:
            ArrayVariable(std::string,std::shared_ptr<ArrayType>);
            ArrayVariable(std::string,std::shared_ptr<ArrayValue>);
            ArrayVariable(std::string,std::shared_ptr<ArrayType>,std::vector<std::shared_ptr<Value>>);
    };
}

#endif // INTERPRETER_ARRAY_VARIABLE_H
