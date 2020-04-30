#include "MyExcept/NoMatchException.h"
#include "Parser/Parser.h"


MyExcept::NoMatchException::NoMatchException(int line,const std::string& s):runtime_error(s+" in line "+std::to_string(line)){}
MyExcept::NoMatchException::NoMatchException(Parser::parserProgress &p,const std::string& x):NoMatchException(p.get_nothrow_nonull()->line,"expected "+x+", got '"+p.get_nothrow_nonull()->get_literal()+"'"){}



