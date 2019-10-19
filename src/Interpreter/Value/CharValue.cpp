#include "Interpreter/CharValue.h"

#include "Interpreter/IntValue.h"
#include "Interpreter/UnsignedIntValue.h"
#include "Interpreter/UnsignedCharValue.h"
#include "Interpreter/FloatValue.h"
#include "Interpreter/CharVariable.h"
#include "Util/InterpreterUtilDefinesMisc.h"

#define PRINTF_CONTAINER_METHOD getInt8
#define PRINTF_CONTAINER_TYPE int8_t

#define CLASS_NAME CharValue
#define VARIABLE_CLASS_NAME CharVariable
#define VALUE_NAME cvalue
#define VALUE_TYPE char
#define VALUE_TYPE_TYPE char_type

#include "interpreter_intlike_methods.inc.h"
