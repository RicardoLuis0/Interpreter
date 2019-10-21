#include "MyExcept/NoMatchException.h"
#include<string>

MyExcept::NoMatchException::NoMatchException(int line,const std::string& s):runtime_error(s+" in line "+std::to_string(line)){}
