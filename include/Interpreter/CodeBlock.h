#ifndef INTERPRETER_CODE_BLOCK_H
#define INTERPRETER_CODE_BLOCK_H

#include "Parser/CodeBlock.h"
#include "Parser/Line.h"
#include "Interpreter/Line.h"
#include "Parser/Statement.h"
#include "Parser/VariableDefinition.h"

namespace Interpreter {
    class CodeBlock : public Line {
        public:
            CodeBlock(class UserFunction * func,std::shared_ptr<Parser::CodeBlock>);//function codeblock constructor
            CodeBlock(DefaultFrame * parent,std::shared_ptr<Parser::CodeBlock>);//codeblock constructor
            CodeBlock(DefaultFrame * parent,std::shared_ptr<Parser::Line>);//single line block constructor (eg. IF statement with single line instead of block, etc)
            virtual std::shared_ptr<LineResult> run(ExecFrame * context) override;
            std::shared_ptr<ExecFrame> getContext(ExecFrame * parent);
            void varDefCallback(std::shared_ptr<Parser::VariableDefinitionItem>,std::shared_ptr<Type>,bool vla);
        protected:
            CodeBlock(std::shared_ptr<DefaultFrame> frame,std::shared_ptr<Parser::CodeBlock> b);
            std::shared_ptr<DefaultFrame> default_frame;
            std::vector<std::shared_ptr<Line>> code;
            void addLine(std::shared_ptr<Parser::Line>);
            void addStatement(std::shared_ptr<Parser::Statement>);
    };
}

#endif // INTERPRETER_BLOCK_CODE_H
