#include "MyExcept/SyntaxError.h"

using namespace MyExcept;

SyntaxError::SyntaxError(const std::string& error):
    runtime_error("Error in unknown line: "+error){
}

SyntaxError::SyntaxError(const int &line_start,const int &line_end,const std::string& error):
    runtime_error("Error in "+((line_start==line_end)?("line "+std::to_string(line_start)):("lines "+std::to_string(line_start)+"-"+std::to_string(line_end)))+": "+error){
}

SyntaxError::SyntaxError(const int &line_start,const int &line_end,const std::string& error,const std::string &filename):
    runtime_error("("+filename+") Error in line "+((line_start==line_end)?("line "+std::to_string(line_start)):("lines "+std::to_string(line_start)+"-"+std::to_string(line_end)))+": "+error){
}
