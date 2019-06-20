#include "no_match_exception.h"

MyExcept::NoMatchException::NoMatchException(int line,const std::string& s):runtime_error(s+" in line "+std::to_string(line)){}
