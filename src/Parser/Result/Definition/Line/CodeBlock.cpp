#include "Parser/CodeBlock.h"

using namespace Parser;

CodeBlock::CodeBlock(std::vector<std::shared_ptr<Line>> l,int ls,int le):ParserResultPart(ls,le),lines(l){
}

