#include "Parser/Line.h"

using namespace Parser;

Line::Line(std::shared_ptr<ParserResultPart> ptr,ParserLineType_t ptype,int ls,int le):ParserResultPart(ls,le),contents(ptr),type(ptype){
    
}
