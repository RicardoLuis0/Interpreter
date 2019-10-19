#ifndef SYMBOL_DATA_H
#define SYMBOL_DATA_H

/** @file symbol_data.h */

#include <string>
//#include "symbol_type.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @struct symbol_data symbol_data.h "symbol_data.h"
     * @brief simple struct for symbol definition {@link Lexer::symbol_list}
     */

    struct symbol_data{
        std::string str; /**< @brief Match String for the Symbol */
        std::string name; /**< @brief Enum Name for the Symbol Type */
        int type; /**< @brief Type of the Symbol {@link #Lexer::symbol_type_t} */
    };

}

#endif // SYMBOL_DATA_H
