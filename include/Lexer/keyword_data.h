#ifndef KEYWORD_DATA_H
#define KEYWORD_DATA_H

/** @file keyword_data.h */

#include <string>
//#include "keyword_type.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer {

    /**
     * @struct keyword_data keyword_data.h "keyword_data.h"
     */

    struct keyword_data{
		keyword_data(std::string s,std::string n,int t):
			str(s),name(n),type(t){
		}
        std::string str; /**< @brief Match String for the Keyword */
        std::string name; /**< @brief Enum Name for the Keyword Type */
        int type; /**< @brief Type of the Keyword {@link #Lexer::keyword_type_t} */
    };

}
#endif // KEYWORD_DATA_H
