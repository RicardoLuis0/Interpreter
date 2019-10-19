#include "Interpreter/IntValue.h"

#include "Interpreter/UnsignedIntValue.h"
#include "Interpreter/CharValue.h"
#include "Interpreter/UnsignedCharValue.h"
#include "Interpreter/FloatValue.h"
#include "Interpreter/IntVariable.h"
#include "Util/InterpreterUtilDefinesMisc.h"

#define PRINTF_CONTAINER_METHOD getInt32
#define PRINTF_CONTAINER_TYPE int32_t

#define CLASS_NAME IntValue
#define VARIABLE_CLASS_NAME IntVariable
#define VALUE_NAME ivalue
#define VALUE_TYPE int
#define VALUE_TYPE_TYPE int_type

#include "interpreter_intlike_methods.inc.h"
