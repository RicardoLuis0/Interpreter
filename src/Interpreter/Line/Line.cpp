#include "Interpreter/Line.h"

using namespace Interpreter;


Line::Line(int i):source_line(i){
}

int Line::get_source_line(){
    return source_line;
}
