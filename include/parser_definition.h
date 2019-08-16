#ifndef PARSER_DEFINITION_H
#define PARSER_DEFINITION_H

#include <vector>
#include <memory>
#include <utility>
#include "parser_result_part.h"
#include "parser_var_type.h"

namespace Parser{
    enum ParserDefinitionType_t{
        DEFINITION_VAR,
        DEFINITION_FUNC,
    };
    class Definition : public ParserResultPart {
        public:
            Definition(ParserDefinitionType_t type,std::shared_ptr<ParserResultPart> def,int line_start,int line_end);
            ParserDefinitionType_t type;
            std::shared_ptr<ParserResultPart> def;
        protected:
        private:
    };
}

#endif // PARSER_DEFINITION_H
