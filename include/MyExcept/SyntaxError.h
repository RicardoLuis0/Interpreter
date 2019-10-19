#ifndef SYNTAX_ERROR_H
#define SYNTAX_ERROR_H

#include <string>
#include <stdexcept>

namespace MyExcept {
    class SyntaxError : public std::runtime_error {
            public:
                explicit SyntaxError(const std::string& error);
                explicit SyntaxError(const int &line_start,const int &line_end,const std::string& error);
                explicit SyntaxError(const int &line_start,const int &line_end,const std::string& error,const std::string &filename);
    };
};

#endif // SYNTAX_ERROR_H
