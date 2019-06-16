#ifndef FLOAT_TOKEN_H
#define FLOAT_TOKEN_H

#include "token.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer {

    /**
     * @class FloatToken float_token.h "float_token.h"
     * @brief Token of the type "TOKEN_TYPE_FLOAT"
     */

    class FloatToken : public Token {
        public:
            /**
             * @brief Constructor
             * 
             * Initializes Superclass and variables
             * @param line {@link Token#line}
             * @param value content of the Token
             */
            FloatToken(int line,double value);
            const std::string get_formatted() const override;
            const std::string get_literal() const override;
            const double get_float() const; /**< @brief get value from Token */
        private:
            const double f; /**< @brief value */
    };

}

#endif // FLOAT_TOKEN_H
