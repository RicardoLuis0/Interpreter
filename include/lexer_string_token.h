#ifndef STRING_TOKEN_H
#define STRING_TOKEN_H

#include "lexer_token.h"


/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class StringToken string_token.h "string_token.h"
     * @brief Token of the type "TOKEN_TYPE_STRING"
     */

    class StringToken : public Token{
        public:
            /**
             * @brief Constructor
             * 
             * Initializes Superclass and variables
             * @param line {@link Token#line}
             * @param processed_string string with escape codes processed
             * @param raw_string string with escape codes unprocessed
             */
            StringToken(int line,const std::string &processed_string,const std::string &raw_string);
            const std::string get_string() const; /**< @brief get processed string */
            const std::string get_literal() const override;
            const std::string get_formatted() const override;
        private:
            const std::string processed_string,raw_string; /**< @brief values */
    };

}
#endif // STRING_TOKEN_H
