#include "Parser/ParserResultPart.h"

using namespace Parser;

ParserResultPart::ParserResultPart(int ls,int le):line_start(ls),line_end(le){
}

std::string ParserResultPart::get_indent(int depth){
    return depth>0?"|   "+get_indent(depth-1):"";
}
