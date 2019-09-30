#include "interpreter_unsigned_char_value.h"

#include "interpreter_int_value.h"
#include "interpreter_unsigned_int_value.h"
#include "interpreter_char_value.h"
#include "interpreter_float_value.h"
#include "interpreter_unsigned_char_variable.h"
#include "interpreter_util_defines_misc.h"

#define PRINTF_CONTAINER_METHOD getUInt8
#define PRINTF_CONTAINER_TYPE uint8_t

#define CLASS_NAME UnsignedCharValue
#define VARIABLE_CLASS_NAME UnsignedCharVariable
#define VALUE_NAME ucvalue
#define VALUE_TYPE unsigned char
#define VALUE_TYPE_TYPE unsigned_char_type
#define UNSIGNED

#include "interpreter_intlike_methods.inc.h"
