#ifndef NO_MATCH_EXCEPTION_H
#define NO_MATCH_EXCEPTION_H

#include <stdexcept>

namespace MyExcept{
    class NoMatchException : public std::runtime_error {
        public:
            explicit NoMatchException(int line,const std::string& s);
    };
};

#endif // NO_MATCH_EXCEPTION_H
