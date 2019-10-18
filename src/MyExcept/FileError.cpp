#include <cstring>

#include "file_error.h"

MyExcept::FileError::FileError(const std::string& filename,int err):runtime_error("Unable to open file \'"+filename+"\', Error code "+std::to_string(err)+" ("+std::string(strerror(err))+")"){}
