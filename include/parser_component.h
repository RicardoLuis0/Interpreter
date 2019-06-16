#ifndef PARSER_COMPONENT_H
#define PARSER_COMPONENT_H

#include <vector>
#include <memory>
#include "parser.h"
#include "parser_result_part.h"

namespace Parser{
    class BaseComponent{
        public:
            //virtual std::shared_ptr<ParserResultPart> makeGenericMatch(parserProgress&)=0;//throws on no match
        protected:
    };
}
#endif // PARSER_COMPONENT_H
