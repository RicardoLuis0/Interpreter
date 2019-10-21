#include <cerrno>
#include <cstdio>
#include <string>
#include "MyExcept/MyExcept.h"

#include "Util/read_file.h"

#ifdef _MSC_VER

//disable c runtime deprecation warnings for MSVC

#pragma warning( disable : 4996 )

#endif

void read_file(std::string filename,std::string &output){
    FILE * f;
    f=fopen(filename.c_str(),"r");
    if(f==nullptr){
        throw MyExcept::FileError(filename,errno);
    }
    output="";
	int c;
    while((c=fgetc(f))!=EOF){
        output+=static_cast<char>(c);
    }
    fclose(f);
}
