#include "Interpreter/UnsignedCharValue.h"

#include "Interpreter/IntValue.h"
#include "Interpreter/UnsignedIntValue.h"
#include "Interpreter/CharValue.h"
#include "Interpreter/FloatValue.h"
#include "Interpreter/UnsignedCharVariable.h"
#include "Util/InterpreterUtilDefinesMisc.h"

#define PRINTF_CONTAINER_METHOD getUInt8
#define PRINTF_CONTAINER_TYPE uint8_t

#define CLASS_NAME UnsignedCharValue
#define VARIABLE_CLASS_NAME UnsignedCharVariable
#define VALUE_NAME ucvalue
#define VALUE_TYPE unsigned char
#define VALUE_TYPE_TYPE unsigned_char_type
#define UNSIGNED

#include "interpreter_intlike_methods.inc.h"
