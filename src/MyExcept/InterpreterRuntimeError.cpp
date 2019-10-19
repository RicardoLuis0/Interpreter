#include "MyExcept/InterpreterRuntimeError.h"

using namespace MyExcept;

InterpreterRuntimeError::InterpreterRuntimeError(const std::string& error):
    runtime_error("Error in unspecified line: "+error){
}

InterpreterRuntimeError::InterpreterRuntimeError(const int &line,const std::string& error):
    runtime_error("Error in line "+std::to_string(line)+": "+error){
}

InterpreterRuntimeError::InterpreterRuntimeError(const int &line,const std::string& error,const std::string &filename):
    runtime_error("("+filename+") Error in line "+std::to_string(line)+": "+error){
}
