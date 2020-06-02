#ifndef SYMBOL_DATA_H
#define SYMBOL_DATA_H

#include <string>
namespace Lexer{
    struct symbol_data{
        symbol_data(std::string s,std::string n,int t):str(s),name(n),type(t){
            
        }
        std::string str;
        std::string name;
        int type;
    };
}

#endif // SYMBOL_DATA_H
