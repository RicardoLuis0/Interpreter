#ifndef PARSER_LINE_MATCHER_H
#define PARSER_LINE_MATCHER_H

#include <memory>
#include "Parser/BaseComponent.h"
#include "Parser/Line.h"

namespace Parser{
    class LineMatcher:BaseComponent{
        public:
            std::shared_ptr<Line> makeMatch(parserProgress&);
    };
}

#endif // PARSER_LINE_MATCHER_H
