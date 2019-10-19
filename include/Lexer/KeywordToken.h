#ifndef KEYWORD_TOKEN_H
#define KEYWORD_TOKEN_H

#include "Lexer/Token.h"

#include "Lexer/keyword_data.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer {

    /**
     * @class KeywordToken keyword_token.h "keyword_token.h"
     * @brief Token of the type "TOKEN_TYPE_KEYWORD"
     */

    class KeywordToken : public Token, private keyword_data {
        public:
            /**
             * @brief Constructor
             * 
             * Initializes Superclasses
             * @param line {@link Token#line}
             * @param data content of the Token {@link keyword_data}
             */
            KeywordToken(int line,keyword_data data);
            const std::string get_formatted() const override;
            const std::string get_literal() const override;
            const std::string get_name() const; /**< @brief get name for keyword type ({@link #Lexer::keyword_type_t})*/
            const int get_keyword_type() const;  /**< @brief get keyword type ({@link #Lexer::keyword_type_t})*/
    };

}

#endif // KEYWORD_TOKEN_H
