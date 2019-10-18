#include "interpreter_unsigned_int_value.h"

#include "interpreter_int_value.h"
#include "interpreter_char_value.h"
#include "interpreter_unsigned_char_value.h"
#include "interpreter_float_value.h"
#include "interpreter_unsigned_int_variable.h"
#include "interpreter_util_defines_misc.h"

#define PRINTF_CONTAINER_METHOD getUInt32
#define PRINTF_CONTAINER_TYPE uint32_t

#define CLASS_NAME UnsignedIntValue
#define VARIABLE_CLASS_NAME UnsignedIntVariable
#define VALUE_NAME uivalue
#define VALUE_TYPE unsigned int
#define VALUE_TYPE_TYPE unsigned_int_type
#define UNSIGNED

#include "interpreter_intlike_methods.inc.h"
