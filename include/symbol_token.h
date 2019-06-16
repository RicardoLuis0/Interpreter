#ifndef SYMBOL_TOKEN_H
#define SYMBOL_TOKEN_H

#include "token.h"
#include "symbol_data.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class SymbolToken symbol_token.h "symbol_token.h"
     * @brief Token of the type "TOKEN_TYPE_SYMBOL"
     */

    class SymbolToken : public Token, private symbol_data {
        public:
            /**
             * @brief Constructor
             * 
             * Initializes Superclasses
             * @param line {@link Token#line}
             * @param data content of the Token {@link symbol_data}
             */
            SymbolToken(int line,symbol_data data);
            const std::string get_formatted() const override;
            const std::string get_literal() const override;
            const std::string get_name() const; /**< @brief get internal name for symbol*/
            const int get_symbol_type() const; /**< @brief get symbol type (presumed enum)*/
    };

}
#endif // SYMBOL_TOKEN_H
