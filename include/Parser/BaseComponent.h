#ifndef PARSER_COMPONENT_H
#define PARSER_COMPONENT_H

#include <vector>
#include <memory>
#include "Parser/Parser.h"
#include "Parser/ParserResultPart.h"

namespace Parser{
    class BaseComponent{
        public:
            //virtual std::shared_ptr<ParserResultPart> makeGenericMatch(parserProgress&)=0;//throws on no match
        protected:
    };
}
#endif // PARSER_COMPONENT_H
