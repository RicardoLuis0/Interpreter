#include "Interpreter/UnsignedIntValue.h"

#include "Interpreter/IntValue.h"
#include "Interpreter/CharValue.h"
#include "Interpreter/UnsignedCharValue.h"
#include "Interpreter/FloatValue.h"
#include "Interpreter/UnsignedIntVariable.h"
#include "Util/InterpreterUtilDefinesMisc.h"

#define PRINTF_CONTAINER_METHOD getUInt32
#define PRINTF_CONTAINER_TYPE uint32_t

#define CLASS_NAME UnsignedIntValue
#define VARIABLE_CLASS_NAME UnsignedIntVariable
#define VALUE_NAME uivalue
#define VALUE_TYPE unsigned int
#define VALUE_TYPE_TYPE unsigned_int_type
#define UNSIGNED

#include "interpreter_intlike_methods.inc.h"
