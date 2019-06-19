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
            Definition(std::shared_ptr<VarType> type);
            std::shared_ptr<VarType> type;
            std::vector<std::pair<ParserDefinitionType_t,std::shared_ptr<ParserResultPart>>> definitions;
        protected:
        private:
    };
}

#endif // PARSER_DEFINITION_H
