#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "Lexer/token_type.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class Token token.h "token.h"
     * @brief Abstract base class for tokens ( { @link Lexer } output ).
     */

    class Token {
        public:
            const int line; /**< Line in which the Token was located in the source file. */
            const token_type_t type; /**< Type of the token ({ @link #Lexer::token_type_t }) */
            /**
             * @brief Constructor
             * 
             * Initializes constant class members
             * @param line {@link Token#line}
             * @param type {@link Token#type}
             */
            Token(int line,token_type_t type);
            /**
             * @brief Get literal token text
             * @return literal token text
             */
            virtual const std::string get_literal() const =0;
            /**
             * @brief Get formatted token string
             * @return formatted token string
             */
            virtual const std::string get_formatted() const =0;
    };

}
#endif // TOKEN_H
