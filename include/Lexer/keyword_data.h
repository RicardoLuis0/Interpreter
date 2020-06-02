#ifndef KEYWORD_DATA_H
#define KEYWORD_DATA_H

#include <string>

namespace Lexer {
    struct keyword_data{
        keyword_data(std::string s,std::string n,int t):str(s),name(n),type(t){
            
        }
        std::string str;
        std::string name;
        int type;
    };

}
#endif // KEYWORD_DATA_H
