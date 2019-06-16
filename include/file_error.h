#ifndef FILE_ERROR_H
#define FILE_ERROR_H

#include <stdexcept>

namespace MyExcept {
    class FileError : public std::runtime_error {
            public:
                explicit FileError(const std::string& filename,int err);
    };
};
#endif // FILE_ERROR_H
