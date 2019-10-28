#ifndef PARSER_RESULT_PART_H
#define PARSER_RESULT_PART_H

#include <string>

namespace Parser{
    class ParserResultPart{
        public:
            ParserResultPart(int line_start,int line_end);
            virtual std::string getSource()=0;
            virtual void print(int depth)=0;
            int line_start;
            int line_end;
        protected:
        private:
    };
}

#endif // PARSER_RESULT_PART_H
