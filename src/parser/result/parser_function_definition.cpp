#include "parser_function_definition.h"

using namespace Parser;

FunctionDefinition::FunctionDefinition(std::shared_ptr<VarType> ret,
                                       std::shared_ptr<Lexer::WordToken> t,
                                       std::vector<std::shared_ptr<FunctionDefinitionParameter>> p,
                                       bool v,
                                       std::shared_ptr<VarType> vt,
                                       std::shared_ptr<Lexer::Token> vi,
                                       std::shared_ptr<CodeBlock> c,
                                       int ls,int le):
    ParserResultPart(ls,le),
    return_type(ret),
    name(t->get_literal()),
    parameters(p),
    variadic(v),
    variadic_type(vt),
    variadic_ident(vi),
    code(c){
        
}
