#include "interpreter_char_value.h"

#include "interpreter_int_value.h"
#include "interpreter_unsigned_int_value.h"
#include "interpreter_unsigned_char_value.h"
#include "interpreter_float_value.h"
#include "interpreter_char_variable.h"
#include "interpreter_util_defines_misc.h"

#define CLASS_NAME CharValue
#define VARIABLE_CLASS_NAME CharVariable
#define VALUE_NAME cvalue
#define VALUE_TYPE char
#define VALUE_TYPE_TYPE char_type

#include "interpreter_intlike_methods.inc.h"
