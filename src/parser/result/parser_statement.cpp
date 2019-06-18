#include "parser_statement.h"

Parser::Statement::Statement(std::shared_ptr<ParserResultPart> stmt,ParserStatementType_t sttype):statement(stmt),type(sttype){
    
}
