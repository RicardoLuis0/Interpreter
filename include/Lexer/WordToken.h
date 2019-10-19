#ifndef WORD_TOKEN_H
#define WORD_TOKEN_H

#include "Lexer/Token.h"


/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class WordToken word_token.h "word_token.h"
     * @brief Token of the type "TOKEN_TYPE_WORD"
     */

    class WordToken : public Token {
        public:
            /**
             * @brief Constructor
             * 
             * Initializes Superclass and variables
             * @param line {@link Token#line}
             * @param data content of the Token
             */
            WordToken(int line,const std::string &data);
            const std::string get_literal() const override;
            const std::string get_formatted() const override;
        private:
            const std::string str;
    };

}

#endif // WORD_TOKEN_H
