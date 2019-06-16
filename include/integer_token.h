#ifndef INTEGER_TOKEN_H
#define INTEGER_TOKEN_H

#include "token.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class IntegerToken integer_token.h "integer_token.h"
     * @brief Token of the type "TOKEN_TYPE_INTEGER"
     */

    class IntegerToken : public Token{
        public:
            /**
             * @brief Constructor
             * 
             * Initializes Superclass and variables
             * @param line {@link Token#line}
             * @param value content of the Token
             */
            IntegerToken(int line,int value);
            const std::string get_formatted() const override;
            const std::string get_literal() const override;
            const int get_integer() const; /**< @brief get value from Token */
        private:
            const int d; /**< @brief value */
    };

}

#endif // INTEGER_TOKEN_H
