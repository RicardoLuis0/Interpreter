#include "MyExcept/FileError.h"
#include <cstring>
#include<string>

#ifdef _MSC_VER

//disable c runtime deprecation warnings for MSVC

#pragma warning( disable : 4996 )

#endif

MyExcept::FileError::FileError(const std::string& filename,int err):runtime_error("Unable to open file \'"+filename+"\', Error code "+std::to_string(err)+" ("+std::string(strerror(err))+")"){}
