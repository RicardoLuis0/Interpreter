#include <cerrno>
#include <cstdio>
#include <string>
#include "my_except.h"

#include "read_file.h"

void read_file(std::string filename,std::string &output){
    FILE * f;
    f=fopen(filename.c_str(),"r");
    if(f==nullptr){
        throw MyExcept::FileError(filename,errno);
    }
    output="";
    char c;
    while((c=fgetc(f))!=EOF){
        output+=c;
    }
}
