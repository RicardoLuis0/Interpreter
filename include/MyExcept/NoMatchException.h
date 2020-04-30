#ifndef NO_MATCH_EXCEPTION_H
#define NO_MATCH_EXCEPTION_H

#include <string>
#include <stdexcept>
#include "Parser/Parser.h"


namespace MyExcept{
    class NoMatchException : public std::runtime_error {
        public:
            explicit NoMatchException(int line,const std::string& s);
            explicit NoMatchException(Parser::parserProgress &p,const std::string& expected);
    };
    class NoMatchExceptionFatal : public std::runtime_error {
        public:
            explicit NoMatchExceptionFatal(int line,const std::string& s);
            explicit NoMatchExceptionFatal(Parser::parserProgress &p,const std::string& expected);
            explicit NoMatchExceptionFatal(NoMatchException &e);
    };
};

#endif // NO_MATCH_EXCEPTION_H
