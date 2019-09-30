#include "interpreter_int_value.h"

#include "interpreter_unsigned_int_value.h"
#include "interpreter_char_value.h"
#include "interpreter_unsigned_char_value.h"
#include "interpreter_float_value.h"
#include "interpreter_int_variable.h"
#include "interpreter_util_defines_misc.h"

#define PRINTF_CONTAINER_METHOD getInt32
#define PRINTF_CONTAINER_TYPE int32_t

#define CLASS_NAME IntValue
#define VARIABLE_CLASS_NAME IntVariable
#define VALUE_NAME ivalue
#define VALUE_TYPE int
#define VALUE_TYPE_TYPE int_type

#include "interpreter_intlike_methods.inc.h"
