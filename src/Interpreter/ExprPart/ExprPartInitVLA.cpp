#include "Interpreter/ExprPartInitVLA.h"

using namespace Interpreter;

ExprPartInitVLA::ExprPartInitVLA(std::shared_ptr<ArrayType> a,std::string n):arr_type(a),name(n){
    
}
std::shared_ptr<Type> ExprPartInitVLA::get_type(){
    return Type::void_type();
}
std::shared_ptr<Value> ExprPartInitVLA::eval(ExecFrame * context){
    auto type=arr_type->build_vla_array_type(context);
    context->variables[name]=type->make_variable(type,name);
    return nullptr;
}
