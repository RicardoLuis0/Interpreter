#include "parser_for_statement.h"

using namespace Parser;

ForStatement::ForStatement(std::shared_ptr<Expression> p,std::shared_ptr<VariableDefinition> vp,std::shared_ptr<Expression> c,std::shared_ptr<Expression> i,std::shared_ptr<Line> l,int ls,int le):
    ParserResultPart(ls,le),
    pre(p),
    condition(c),
    inc(i),
    vardef_pre(vp),
    code(l){
        
}
