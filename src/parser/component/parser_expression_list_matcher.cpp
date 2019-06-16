#include "parser_expression_list_matcher.h"

#include "symbols_keywords.h"

#include "parser_expression_matcher.h"
#include "my_except.h"

//ExpressionList = Expression , { symbol ',' , Expression } ;

std::shared_ptr<Parser::ExpressionList> Parser::ExpressionListMatcher::makeMatch(parserProgress &p){
    std::vector<std::shared_ptr<Expression>> list{ExpressionMatcher().makeMatch(p)};
    while(1){
        int location_backup;
        try{
            location_backup=p.location;
            if(p.isSymbol(SYMBOL_COMMA)){
                list.push_back(ExpressionMatcher().makeMatch(p));
            }else{
                return std::make_shared<ExpressionList>(list);
            }
        }catch(MyExcept::NoMatchException &e){
            p.location=location_backup;
            return std::make_shared<ExpressionList>(list);
        }
    }
}
