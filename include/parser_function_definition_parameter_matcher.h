#ifndef PARSER_FUNCTION_DEFINITION_PARAMETER_MATCHER_H
#define PARSER_FUNCTION_DEFINITION_PARAMETER_MATCHER_H


#include <memory>
#include "parser_component.h"
#include "parser_function_definition_parameter.h"

namespace Parser{
    class FunctionDefinitionParameterMatcher:BaseComponent{
        public:
            std::shared_ptr<FunctionDefinitionParameter> makeMatch(parserProgress&);
    };
}

#endif // PARSER_FUNCTION_DEFINITION_PARAMETER_MATCHER_H
