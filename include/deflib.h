#ifndef DEFLIB_H
#define DEFLIB_H

#include "Interpreter/DefaultFrame.h"

namespace Interpreter {
    void load_library(std::string library);
    void import_min(DefaultFrame*);
    void import(DefaultFrame*,std::string library);
    void import_all(DefaultFrame*);
}

#endif // DEFLIB_H
