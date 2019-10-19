#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <string>
#include <stdexcept>

namespace MyExcept {
    class ParseError : public std::runtime_error {
            public:
                explicit ParseError(const int &line,const std::string& error);
                explicit ParseError(const int &line,const std::string& error,const std::string &filename);
    };
};

#endif // PARSE_ERROR_H
