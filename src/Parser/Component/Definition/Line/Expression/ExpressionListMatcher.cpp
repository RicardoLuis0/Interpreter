#include "Parser/ExpressionListMatcher.h"

#include "symbols_keywords.h"

#include "Parser/ExpressionMatcher.h"
#include "MyExcept/MyExcept.h"

//ExpressionList = Expression , { symbol ',' , Expression } ;

using namespace Parser;

std::shared_ptr<ExpressionList> ExpressionListMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::vector<std::shared_ptr<Expression>> list{ExpressionMatcher().makeMatch(p)};
    while(1){
        int location_backup;
        try{
            location_backup=p.location;
            if(p.isSymbol(SYMBOL_COMMA)){
                list.push_back(ExpressionMatcher().makeMatch(p));
            }else{
                return std::make_shared<ExpressionList>(list,line_start,p.get_line(-1));
            }
        }catch(MyExcept::NoMatchException &){
            p.location=location_backup;
            return std::make_shared<ExpressionList>(list,line_start,p.get_line(-1));
        }
    }
}
