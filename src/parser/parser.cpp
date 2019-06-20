#include "parser.h"

#include "symbol_token.h"
#include "keyword_token.h"
#include "eof_token.h"

bool Parser::parserProgress::in_range(int offset){
    return !(location+offset>=data.size());
}

bool Parser::parserProgress::peekType(Lexer::token_type_t id,int offset){
    if(!in_range(offset))return false;
    return (get(offset)->type==id);
}

bool Parser::parserProgress::peekSymbol(int id,int offset){
    if(!in_range(offset))return false;
    return (get(offset)->type==Lexer::TOKEN_TYPE_SYMBOL&&std::static_pointer_cast<Lexer::SymbolToken>(get(offset))->get_symbol_type()==id);
}

bool Parser::parserProgress::peekSymbol(std::vector<int> ids,int offset){
    if(!in_range(offset))return false;
    if(get(offset)->type==Lexer::TOKEN_TYPE_SYMBOL){
        int id=std::static_pointer_cast<Lexer::SymbolToken>(get(offset))->get_symbol_type();
        for(int id2:ids){
            if(id==id2){
                return true;
            }
        }
    }
    return false;
}

bool Parser::parserProgress::peekKeyword(int id,int offset){
    if(!in_range(offset))return false;
    return (get(offset)->type==Lexer::TOKEN_TYPE_KEYWORD&&std::static_pointer_cast<Lexer::KeywordToken>(get(offset))->get_keyword_type()==id);
}

bool Parser::parserProgress::peekKeyword(std::vector<int> ids,int offset){
    if(!in_range(offset))return false;
    if(get(offset)->type==Lexer::TOKEN_TYPE_KEYWORD){
        int id=std::static_pointer_cast<Lexer::KeywordToken>(get(offset))->get_keyword_type();
        for(int id2:ids){
            if(id==id2){
                return true;
            }
        }
    }
    return false;
}

std::shared_ptr<Lexer::Token> Parser::parserProgress::get(int offset){
    if(!in_range(offset))throw std::out_of_range("token out of range");
    return data[location+offset];
}

std::shared_ptr<Lexer::Token> Parser::parserProgress::get_nothrow(int offset){
    if(!in_range(offset))return nullptr;
    return data[location+offset];
}

std::shared_ptr<Lexer::Token> Parser::parserProgress::get_nothrow_nonull(int offset){
    if(!in_range(offset))return std::make_shared<Lexer::EOFToken>(data[data.size()-1]->line);
    return data[location+offset];
}

std::shared_ptr<Lexer::Token> Parser::parserProgress::isType(Lexer::token_type_t id){
    if(!in_range(0))return nullptr;
    if(get()->type==id){
        auto temp=get();
        location++;
        return temp;
    }
    return nullptr;
}

bool Parser::parserProgress::isSymbol(int id){
    if(!in_range(0))return false;
    if(get()->type==Lexer::TOKEN_TYPE_SYMBOL&&std::static_pointer_cast<Lexer::SymbolToken>(get())->get_symbol_type()==id){
        location++;
        return true;
    }
    return false;
}

std::shared_ptr<Lexer::SymbolToken> Parser::parserProgress::isSymbol(std::vector<int> ids){
    if(!in_range(0))return nullptr;
    if(get()->type==Lexer::TOKEN_TYPE_SYMBOL){
        int id=std::static_pointer_cast<Lexer::SymbolToken>(get())->get_symbol_type();
        for(int id2:ids){
            if(id==id2){
                auto temp=get();
                location++;
                return std::static_pointer_cast<Lexer::SymbolToken>(temp);
            }
        }
    }
    return nullptr;
}

bool Parser::parserProgress::isKeyword(int id){
    if(!in_range(0))return false;
    if(get()->type==Lexer::TOKEN_TYPE_KEYWORD&&std::static_pointer_cast<Lexer::KeywordToken>(get())->get_keyword_type()==id){
        location++;
        return true;
    }
    return false;
}

std::shared_ptr<Lexer::KeywordToken> Parser::parserProgress::isKeyword(std::vector<int> ids){
    if(!in_range(0))return nullptr;
    if(get()->type==Lexer::TOKEN_TYPE_KEYWORD){
        int id=std::static_pointer_cast<Lexer::KeywordToken>(get())->get_keyword_type();
        for(int id2:ids){
            if(id==id2){
                auto temp=get();
                location++;
                return std::static_pointer_cast<Lexer::KeywordToken>(temp);
            }
        }
    }
    return nullptr;
}

void Parser::Parser::parse(const std::vector<std::shared_ptr<Lexer::Token>> &data){
    parserProgress progress {data:data,location:0};
}
