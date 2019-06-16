#include "parse_error.h"

MyExcept::ParseError::ParseError(const int &line,const std::string& error):runtime_error("Error in line "+std::to_string(line)+", "+error){}

MyExcept::ParseError::ParseError(const int &line,const std::string& error,const std::string &filename):runtime_error("("+filename+") Error in line "+std::to_string(line)+", "+error){}
