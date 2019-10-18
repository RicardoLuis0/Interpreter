#include "parser_statement.h"

using namespace Parser;

Statement::Statement(std::shared_ptr<ParserResultPart> stmt,ParserStatementType_t sttype,int ls,int le):ParserResultPart(ls,le),statement(stmt),type(sttype){
    
}
