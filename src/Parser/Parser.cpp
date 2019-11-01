#include "Parser/Parser.h"

#include "Lexer/SymbolToken.h"
#include "Lexer/KeywordToken.h"
#include "Lexer/EOFToken.h"

using namespace Parser;

parserProgress::parserProgress(const std::vector<std::shared_ptr<Lexer::Token>> &d, int l):data(d),location(l) {

}

int parserProgress::get_line(int offset){
    return get_nothrow_nonull(offset)->line;
}

bool parserProgress::in_range(int offset){
    return !(int64_t(location+offset)>=int64_t(data.size())||int64_t(location+offset)<0);//to fix signed with unsigned comparison error
}

bool parserProgress::peekType(Lexer::token_type_t id,int offset){
    if(!in_range(offset))return false;
    return (get(offset)->type==id);
}

bool parserProgress::peekSymbol(int id,int offset){
    if(!in_range(offset))return false;
    return (get(offset)->type==Lexer::TOKEN_TYPE_SYMBOL&&std::static_pointer_cast<Lexer::SymbolToken>(get(offset))->get_symbol_type()==id);
}

bool parserProgress::peekSymbol(std::vector<int> ids,int offset){
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

bool parserProgress::peekKeyword(int id,int offset){
    if(!in_range(offset))return false;
    return (get(offset)->type==Lexer::TOKEN_TYPE_KEYWORD&&std::static_pointer_cast<Lexer::KeywordToken>(get(offset))->get_keyword_type()==id);
}

bool parserProgress::peekKeyword(std::vector<int> ids,int offset){
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

std::shared_ptr<Lexer::Token> parserProgress::get(int offset){
    if(!in_range(offset))throw std::out_of_range("token out of range");
    return data[location+offset];
}

std::shared_ptr<Lexer::Token> parserProgress::get_nothrow(int offset){
    if(!in_range(offset))return nullptr;
    return data[location+offset];
}

std::shared_ptr<Lexer::Token> parserProgress::get_nothrow_nonull(int offset){
    if(!in_range(offset))return std::make_shared<Lexer::EOFToken>((location+offset>0)?data[data.size()-1]->line:0);
    return data[location+offset];
}

std::shared_ptr<Lexer::Token> parserProgress::isType(Lexer::token_type_t id){
    if(!in_range())return nullptr;
    if(get()->type==id){
        auto temp=get();
        location++;
        return temp;
    }
    return nullptr;
}

bool parserProgress::isSymbol(int id){
    if(!in_range(0))return false;
    if(get()->type==Lexer::TOKEN_TYPE_SYMBOL&&std::static_pointer_cast<Lexer::SymbolToken>(get())->get_symbol_type()==id){
        location++;
        return true;
    }
    return false;
}

std::shared_ptr<Lexer::SymbolToken> parserProgress::isSymbol(std::vector<int> ids){
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

bool parserProgress::isKeyword(int id){
    if(!in_range(0))return false;
    if(get()->type==Lexer::TOKEN_TYPE_KEYWORD&&std::static_pointer_cast<Lexer::KeywordToken>(get())->get_keyword_type()==id){
        location++;
        return true;
    }
    return false;
}

std::shared_ptr<Lexer::KeywordToken> parserProgress::isKeyword(std::vector<int> ids){
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

void parse(const std::vector<std::shared_ptr<Lexer::Token>> &){
    //parserProgress progress {data:data,location:0};
    //TODO Parser::parse
    throw std::runtime_error("unimplemented");
}

parserProgress& parserProgress::operator--(){
    location--;
    return *this;
}

parserProgress& parserProgress::operator--(int){
    location--;
    return *this;
}

parserProgress& parserProgress::operator++(){
    location++;
    return *this;
}

parserProgress& parserProgress::operator++(int){
    location++;
    return *this;
}
