#ifndef PARSER_LINE_MATCHER_H
#define PARSER_LINE_MATCHER_H

#include <memory>
#include "parser_component.h"
#include "parser_line.h"

namespace Parser{
    class LineMatcher:BaseComponent{
        public:
            std::shared_ptr<Line> makeMatch(parserProgress&);
    };
}

#endif // PARSER_LINE_MATCHER_H
