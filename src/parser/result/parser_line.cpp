#include "parser_line.h"

Parser::Line::Line(std::shared_ptr<ParserResultPart> ptr,ParserLineType_t ptype):contents(ptr),type(ptype){
    
}
