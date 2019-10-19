#ifndef PARSER_RESULT_PART_H
#define PARSER_RESULT_PART_H

namespace Parser{
    class ParserResultPart{
        public:
            ParserResultPart(int line_start,int line_end);
            virtual ~ParserResultPart()=0;
            int line_start;
            int line_end;
        protected:
        private:
    };
}

#endif // PARSER_RESULT_PART_H
