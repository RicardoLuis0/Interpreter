#include "Interpreter_Test.h"

#define MAP_HAS(map,key) (map.find(key)!=map.end())

#define MAP_FIND(map,key)auto iter=map.find(key);if(iter!=map.end())

#define MAP_GET(map,key,other) MAP_FIND(map,key){return iter->second;}else{return other;}

#define MAP_SET(map,key,val,other) MAP_FIND(map,key){iter->second=val;}else{other;}

#define IS(ptr,type) (typeid(*(ptr))==typeid(type))

#include <iostream>

#include "string_token.h"
#include "integer_token.h"
#include "float_token.h"
#include "symbols_keywords.h"
#include "parser_binary_operation.h"
#include "word_token.h"
#include "parser_statement.h"

using namespace Interpreter;

static bool is_int(std::shared_ptr<Parser::VarType> vt){
    if(vt->type==Parser::VARTYPE_PRIMITIVE){
        return (vt->primitive==Parser::PRIMITIVE_INT);
    }
    return false;
}

static bool is_float(std::shared_ptr<Parser::VarType> vt){
    if(vt->type==Parser::VARTYPE_PRIMITIVE){
        return (vt->primitive==Parser::PRIMITIVE_FLOAT);
    }
    return false;
}

static bool is_num(std::shared_ptr<Parser::VarType> vt){
    return is_int(vt)||is_float(vt);
}

static bool is_string(std::shared_ptr<Parser::VarType> vt){
    if(vt->type==Parser::VARTYPE_PRIMITIVE){
        return (vt->primitive==Parser::PRIMITIVE_STRING);
    }
    return false;
}

static std::string get_name(std::shared_ptr<Parser::VarType> vt){
    if(is_int(vt))return "int";
    if(is_float(vt))return "float";
    if(is_string(vt))return "string";
    return "unknown";
}

static bool is_compatible(std::shared_ptr<Parser::VarType> vt1,std::shared_ptr<Parser::VarType> vt2){
    if(is_num(vt1)&&is_num(vt2))return true;
    if(is_string(vt1)||is_string(vt2))return true;
    return false;
}

class Print_Function : public Native_Function_Call{

    std::string get_name() override {
        return "print";
    }

    std::shared_ptr<Parser::VarType> get_type(){
        return std::make_shared<Parser::VarType>(Parser::VARTYPE_VOID);
    }

    std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override {
        return {std::make_shared<Parser::FunctionDefinitionParameter>(std::make_shared<Parser::VarType>(Parser::VARTYPE_MIXED),"var")};
    }

    std::shared_ptr<Interpreter_Value> call(std::shared_ptr<Interpreter_ExecFrame> parent_frame,std::map<std::string,std::shared_ptr<Interpreter_Value>> args) override {
        std::shared_ptr<Interpreter_Value> var=args[0];
        if(IS(var,Int_Value)){
            std::cout<<std::to_string(*std::dynamic_pointer_cast<Int_Value>(var));
        }else if(IS(var,Float_Value)){
            std::cout<<std::to_string(*std::dynamic_pointer_cast<Float_Value>(var));
        }else if(IS(var,String_Value)){
            std::cout<<std::string(*std::dynamic_pointer_cast<String_Value>(var));
        }
        return nullptr;
    }
};

class ReadInt_Function : public Native_Function_Call{

    std::string get_name() override {
        return "read_int";
    }

    std::shared_ptr<Parser::VarType> get_type(){
        return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_INT);
    }

    std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override {
        return {};
    }

    std::shared_ptr<Interpreter_Value> call(std::shared_ptr<Interpreter_ExecFrame> parent_frame,std::map<std::string,std::shared_ptr<Interpreter_Value>> args) override {
        std::string temp;
        std::getline(std::cin,temp,'\n');
        return std::make_shared<Int_Value>(std::stoi(temp));
    }
};

Interpreter_ExecFrame::Interpreter_ExecFrame(std::shared_ptr<Interpreter_ExecFrame> p,std::shared_ptr<Interpreter_Frame> d):parent(p),defaults(d){
    for(auto vpair:defaults->variable_defaults){
        if(IS(vpair.second,Int_Variable)){
            std::shared_ptr<Int_Variable> var(std::dynamic_pointer_cast<Int_Variable>(vpair.second));
            variables.insert({var->get_name(),std::make_shared<Int_Variable>(var->get())});
        }else if(IS(vpair.second,Float_Variable)){
            std::shared_ptr<Float_Variable> var(std::dynamic_pointer_cast<Float_Variable>(vpair.second));
            variables.insert({var->get_name(),std::make_shared<Float_Variable>(var->get())});
        }else if(IS(vpair.second,String_Variable)){
            std::shared_ptr<String_Variable> var(std::dynamic_pointer_cast<String_Variable>(vpair.second));
            variables.insert({var->get_name(),std::make_shared<String_Variable>(var->get())});
        }else{
            throw std::runtime_error("unknown variable type in defaults");
        }
    }
}

std::shared_ptr<Interpreter_Variable> Interpreter_ExecFrame::get_variable(std::string name){
    MAP_GET(variables,name,parent?parent->get_variable(name):nullptr)
}

std::shared_ptr<Function_Call> Interpreter_ExecFrame::get_function(std::string name){
    return defaults->get_function(name);
}

Interpreter_Block::Interpreter_Block(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::CodeBlock> b):code(std::make_shared<Interpreter_Code>(context,b)){}

Interpreter_ExpressionPart_FunctionCall::Interpreter_ExpressionPart_FunctionCall(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::FunctionCall> fn):ident(fn->identifier){
    std::shared_ptr<Function_Call> fnc=context->get_function(ident);
    std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> params=fnc->get_parameters();
    std::vector<std::shared_ptr<Parser::Expression>> args=fn->arguments->expression_list;
    if(params.size()!=args.size()){
        if(params.size()>args.size()){
            throw std::runtime_error("too many arguments for function '"+fn->identifier+"'");
        }else{
            throw std::runtime_error("too few arguments for function '"+fn->identifier+"'");
        }
    }
    for(size_t i=0;i<params.size();i++){
        arguments.push_back(std::make_shared<Interpreter_Expression>(context,args[i]));
        if(!is_compatible(arguments[i]->final_type,params[i]->type)){
            throw std::runtime_error("incompatible argument type of "+get_name(arguments[i]->final_type)+" for parameter of type "+get_name(params[i]->type));
        }
    }
}

std::shared_ptr<Interpreter_Value> Interpreter_ExpressionPart_FunctionCall::call(std::shared_ptr<Interpreter_ExecFrame> context){
    std::map<std::string,std::shared_ptr<Interpreter_Value>> args;
    std::shared_ptr<Function_Call> fn=context->get_function(ident);
    std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> params=fn->get_parameters();
    for(size_t i=0;i<params.size();i++){
        args.insert({params[i]->name,arguments[i]->eval(context)});
    }
    return fn->call(context,args);
}

std::shared_ptr<Function_Call> Interpreter_ExpressionPart_FunctionCall::get(std::shared_ptr<Interpreter_ExecFrame> context){
    return context->get_function(ident);
}

std::shared_ptr<Function_Call> Interpreter_ExpressionPart_FunctionCall::get(std::shared_ptr<Interpreter_Frame> context){
    return context->get_function(ident);
}

Interpreter_ExpressionPart_Value::Interpreter_ExpressionPart_Value(int i):value(std::make_shared<Int_Value>(i)){
}

Interpreter_ExpressionPart_Value::Interpreter_ExpressionPart_Value(double d):value(std::make_shared<Float_Value>(d)){
}

Interpreter_ExpressionPart_Value::Interpreter_ExpressionPart_Value(std::string s):value(std::make_shared<String_Value>(s)){
}

Interpreter_ExpressionPart_Operator::Interpreter_ExpressionPart_Operator(int i):op(i){
}

Interpreter_ExpressionPart_Variable::Interpreter_ExpressionPart_Variable(std::shared_ptr<Interpreter_Frame> context,std::string s):ident(s){
    if(context->get_variable(ident)==nullptr)throw std::runtime_error("undefined variable "+ident);
}

std::shared_ptr<Interpreter_Variable> Interpreter_ExpressionPart_Variable::get(std::shared_ptr<Interpreter_Frame> context){
    return context->get_variable(ident);
}

std::shared_ptr<Interpreter_Variable> Interpreter_ExpressionPart_Variable::get(std::shared_ptr<Interpreter_ExecFrame> context){
    return context->get_variable(ident);
}

std::shared_ptr<Parser::VarType> Interpreter_ExpressionPart_FunctionCall::get_type(std::shared_ptr<Interpreter_Frame> context){
    return get(context)->get_type();
}
std::shared_ptr<Parser::VarType> Interpreter_ExpressionPart_Variable::get_type(std::shared_ptr<Interpreter_Frame> context){
    return get(context)->get_type();
}
std::shared_ptr<Parser::VarType> Interpreter_ExpressionPart_Value::get_type(std::shared_ptr<Interpreter_Frame> context){
    return value->get_type();
}
std::shared_ptr<Parser::VarType> Interpreter_ExpressionPart_Operator::get_type(std::shared_ptr<Interpreter_Frame> context){
    return nullptr;
}

std::shared_ptr<Interpreter_Value> Interpreter_ExpressionPart_FunctionCall::eval(std::shared_ptr<Interpreter_ExecFrame> context){
    return call(context);
}
std::shared_ptr<Interpreter_Value> Interpreter_ExpressionPart_Variable::eval(std::shared_ptr<Interpreter_ExecFrame> context){
    return get(context);
}
std::shared_ptr<Interpreter_Value> Interpreter_ExpressionPart_Value::eval(std::shared_ptr<Interpreter_ExecFrame> context){
    return value;
}
std::shared_ptr<Interpreter_Value> Interpreter_ExpressionPart_Operator::eval(std::shared_ptr<Interpreter_ExecFrame> context){
    return nullptr;
}

//0=special operator (scope resolution, member access, etc) currently unused

std::map<int,int> operator_precedence{
    {SYMBOL_ASSIGNMENT,11},
    {SYMBOL_EQUALS,5},
    {SYMBOL_NOT_EQUALS,5},
    {SYMBOL_GREATER,4},
    {SYMBOL_GREATER_EQUALS,4},
    {SYMBOL_LOWER,4},
    {SYMBOL_LOWER_EQUALS,4},
    {SYMBOL_PLUS,2},
    {SYMBOL_PLUS_ASSIGNMENT,11},
    {SYMBOL_MINUS,2},
    {SYMBOL_MINUS_ASSIGNMENT,11},
    {SYMBOL_MULTIPLY,1},
    {SYMBOL_MULTIPLY_ASSIGNMENT,11},
    {SYMBOL_DIVIDE,1},
    {SYMBOL_DIVIDE_ASSIGNMENT,11},
    {SYMBOL_LOGICAL_AND,9},
    {SYMBOL_LOGICAL_OR,10},
    {SYMBOL_BITWISE_AND,6},
    {SYMBOL_BITWISE_AND_ASSIGNMENT,11},
    {SYMBOL_BITWISE_OR,8},
    {SYMBOL_BITWISE_OR_ASSIGNMENT,11},
    {SYMBOL_BITWISE_XOR,7},
    {SYMBOL_BITWISE_XOR_ASSIGNMENT,11},
    {SYMBOL_LEFT_SHIFT,3},
    {SYMBOL_LEFT_SHIFT_ASSIGNMENT,11},
    {SYMBOL_RIGHT_SHIFT,3},
    {SYMBOL_RIGHT_SHIFT_ASSIGNMENT,11},
    {SYMBOL_PERCENT,1},
    {SYMBOL_PERCENT_ASSIGNMENT,11},
};

void Interpreter_Expression::add_expression(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::Expression> e){
    std::stack<int> op_stack;
    //parse operator precedence using shunting yard, check for undefined functions/variables
    while(1){
        if(e->type==Parser::EXPRESSION_BINARY_OPERATION){
            std::shared_ptr<Parser::BinaryOperation> op(std::static_pointer_cast<Parser::BinaryOperation>(e->contents));
            int op_num=op->binary_operator->get_symbol_type();
            if(operator_precedence[op_num]==0){
                //special handling
                e=op->term2;
            }else{
                add_term(context,op->term1);
                if(!MAP_HAS(operator_precedence,op_num))throw std::runtime_error("unknown operator");
                while(operator_precedence[op_stack.top()]>=operator_precedence[op_num]){
                    expression.push(std::make_shared<Interpreter_ExpressionPart_Operator>(op_stack.top()));
                    op_stack.pop();
                }
                op_stack.push(op_num);
                e=op->term2;
            }
        }else if(e->type==Parser::EXPRESSION_TERM){
            add_term(context,std::static_pointer_cast<Parser::ExpressionTerm>(e->contents));
            break;
        }
    }
}

void Interpreter_Expression::add_term(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::ExpressionTerm> term){
    switch(term->type){
    case Parser::EXPRESSION_TERM_EXPRESSION_GROUP:
        add_expression(context,std::static_pointer_cast<Parser::ExpressionGroup>(term->contents_p)->contents);
        break;
    case Parser::EXPRESSION_TERM_FUNCTION_CALL:
        expression.push(std::make_shared<Interpreter_ExpressionPart_FunctionCall>(context,std::static_pointer_cast<Parser::FunctionCall>(term->contents_p)));
        break;
    case Parser::EXPRESSION_TERM_IDENTIFIER:
        expression.push(std::make_shared<Interpreter_ExpressionPart_Variable>(context,std::static_pointer_cast<Lexer::WordToken>(term->contents_t)->get_literal()));
        break;
    case Parser::EXPRESSION_TERM_LITERAL_INT:
        expression.push(std::make_shared<Interpreter_ExpressionPart_Value>(int(std::static_pointer_cast<Lexer::IntegerToken>(term->contents_t)->get_integer())));
        break;
    case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
        expression.push(std::make_shared<Interpreter_ExpressionPart_Value>(std::static_pointer_cast<Lexer::FloatToken>(term->contents_t)->get_float()));
        break;
    case Parser::EXPRESSION_TERM_LITERAL_STRING:
        expression.push(std::make_shared<Interpreter_ExpressionPart_Value>(std::static_pointer_cast<Lexer::StringToken>(term->contents_t)->get_literal()));
        break;
    case Parser::EXPRESSION_TERM_UNARY_OPERATION:
        //TODO Interpreter_Expression::add_term unary
        throw std::runtime_error("unimplemented Interpreter_Expression::add_term unary");
        break;
    }
}

Interpreter_Expression::Interpreter_Expression(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::Expression> e){
    add_expression(context,e);
    final_type=check(context);
}

std::shared_ptr<Interpreter_Value> eval_op(std::shared_ptr<Interpreter_ExecFrame> context,std::stack<std::shared_ptr<Interpreter_ExpressionPart>> &st,std::shared_ptr<Interpreter_ExpressionPart_Operator> op){
    //TODO Interpreter_Expression::eval_op
    throw std::runtime_error("unimplemented Interpreter_Expression::eval_op");
}

std::shared_ptr<Interpreter_Value> Interpreter_Expression::eval(std::shared_ptr<Interpreter_ExecFrame> context){
    std::stack<std::shared_ptr<Interpreter_ExpressionPart>> temp_stack=expression;
    std::shared_ptr<Interpreter_ExpressionPart> ex=temp_stack.top();
    temp_stack.pop();
    //TODO Interpreter_Expression::eval
    throw std::runtime_error("unimplemented Interpreter_Expression::eval");
}

std::shared_ptr<Parser::VarType> Interpreter_Expression::check_op(std::shared_ptr<Interpreter_Frame> context,std::stack<std::shared_ptr<Interpreter_ExpressionPart>> &st,std::shared_ptr<Interpreter_ExpressionPart_Operator> op){
    std::shared_ptr<Interpreter_ExpressionPart> ex1=st.top();//right term
    st.pop();
    std::shared_ptr<Parser::VarType> t1;
    if(IS(ex1,Interpreter_ExpressionPart_Operator)){
        t1=check_op(context,st,std::static_pointer_cast<Interpreter_ExpressionPart_Operator>(ex1));
    }else{
        t1=ex1->get_type(context);
    }
    std::shared_ptr<Interpreter_ExpressionPart> ex2=st.top();//left term
    st.pop();
    std::shared_ptr<Parser::VarType> t2;
    if(IS(ex2,Interpreter_ExpressionPart_Operator)){
        t2=check_op(context,st,std::static_pointer_cast<Interpreter_ExpressionPart_Operator>(ex2));
    }else{
        t2=ex2->get_type(context);
    }
    if(is_string(t2)) return t2;
    if(is_string(t1)) return t1;
    if(is_int(t2)&&is_int(t1)) return t2;
    if(is_float(t2)&&is_num(t1)) return t2;
    if(is_num(t2)&&is_float(t1)) return t1;
    throw std::runtime_error("incompatible types "+get_name(t1)+" and "+get_name(t2));
}

std::shared_ptr<Parser::VarType> Interpreter_Expression::get_type(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Interpreter_ExpressionPart> ex){
    if(IS(ex,Interpreter_ExpressionPart_Operator))throw std::runtime_error("invalid object type Interpreter_ExpressionPart_Operator for Interpreter_Expression::get_type");
    return ex->get_type(context);
}

std::shared_ptr<Parser::VarType> Interpreter_Expression::check(std::shared_ptr<Interpreter_Frame> context){
    std::stack<std::shared_ptr<Interpreter_ExpressionPart>> temp_stack=expression;
    std::shared_ptr<Interpreter_ExpressionPart> ex=temp_stack.top();
    temp_stack.pop();
    std::shared_ptr<Parser::VarType> temp_type;
    if(IS(ex,Interpreter_ExpressionPart_Operator)){
        std::shared_ptr<Interpreter_ExpressionPart_Operator> op(std::static_pointer_cast<Interpreter_ExpressionPart_Operator>(ex));
        temp_type=check_op(context,temp_stack,op);
    }else{
        temp_type=get_type(context,ex);
    }
    if(temp_type&&temp_stack.size()!=0){//if the stack wasn't consumed to the end by check_op, or wasn't a single value
        throw std::runtime_error("invalid object state for Interpreter_Expression");
    }
    return temp_type;
}

Interpreter_IfStatement::Interpreter_IfStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::IfStatement> stmt){
    condition=std::make_shared<Interpreter_Expression>(context,stmt->condition);
    code=std::make_shared<Interpreter_Code>(context,stmt->code);
    if(stmt->else_stmt){
        else_stmt=std::make_shared<Interpreter_Code>(context,stmt->else_stmt->code);
    }
}

Interpreter_ForStatement::Interpreter_ForStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::ForStatement> stmt){
    pre=std::make_shared<Interpreter_Expression>(context,stmt->pre);
    condition=std::make_shared<Interpreter_Expression>(context,stmt->condition);
    inc=std::make_shared<Interpreter_Expression>(context,stmt->inc);
    code=std::make_shared<Interpreter_Code>(context,stmt->code);
}

Interpreter_WhileStatement::Interpreter_WhileStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::WhileStatement> stmt){
    condition=std::make_shared<Interpreter_Expression>(context,stmt->condition);
    code=std::make_shared<Interpreter_Code>(context,stmt->code);
}

Interpreter_ReturnStatement::Interpreter_ReturnStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::ReturnStatement> stmt){
    value=std::make_shared<Interpreter_Expression>(context,stmt->value);
}

Interpreter_Code::Interpreter_Code(std::shared_ptr<Interpreter_Frame> parent,std::shared_ptr<Parser::CodeBlock> cb):default_frame(std::make_shared<Interpreter_Frame>()){
    for(auto l:cb->lines){
        readLine(l);
    }
}

Interpreter_Code::Interpreter_Code(std::shared_ptr<Interpreter_Frame> p,std::shared_ptr<Parser::Line> l):default_frame(std::make_shared<Interpreter_Frame>(p)){
    readLine(l);
}

void Interpreter_Code::readLine(std::shared_ptr<Parser::Line> l){
    switch(l->type){
    case Parser::LINE_CODE_BLOCK:
        code.push_back(std::make_shared<Interpreter_Block>(default_frame,std::static_pointer_cast<Parser::CodeBlock>(l->contents)));
        break;
    case Parser::LINE_STATEMENT:{
            std::shared_ptr<Parser::Statement> stmt(std::static_pointer_cast<Parser::Statement>(l->contents));
            switch(stmt->type){
            case Parser::STATEMENT_IF:
                code.push_back(std::make_shared<Interpreter_IfStatement>(default_frame,std::static_pointer_cast<Parser::IfStatement>(stmt->statement)));
                break;
            case Parser::STATEMENT_WHILE:
                code.push_back(std::make_shared<Interpreter_WhileStatement>(default_frame,std::static_pointer_cast<Parser::WhileStatement>(stmt->statement)));
                break;
            case Parser::STATEMENT_FOR:
                code.push_back(std::make_shared<Interpreter_ForStatement>(default_frame,std::static_pointer_cast<Parser::ForStatement>(stmt->statement)));
                break;
            case Parser::STATEMENT_RETURN:
                code.push_back(std::make_shared<Interpreter_ReturnStatement>(default_frame,std::static_pointer_cast<Parser::ReturnStatement>(stmt->statement)));
                break;
            }
        }
        break;
    case Parser::LINE_EXPRESSION:
        code.push_back(std::make_shared<Interpreter_Expression>(default_frame,std::static_pointer_cast<Parser::Expression>(l->contents)));
        break;
    case Parser::LINE_DEFINITION:{
            std::shared_ptr<Parser::Definition> def(std::static_pointer_cast<Parser::Definition>(l->contents));
            switch(def->type){
            case Parser::DEFINITION_VAR:{//special handling for variable definition lists
                    std::shared_ptr<Parser::VariableDefinition> vdef(std::static_pointer_cast<Parser::VariableDefinition>(def->def));
                    std::shared_ptr<Parser::VarType> vt(vdef->type);
                    for(std::shared_ptr<Parser::VariableDefinitionItem> var:vdef->variables){
                        if(var->value){
                            if(var->value->type==Parser::EXPRESSION_TERM){
                                switch(std::static_pointer_cast<Parser::ExpressionTerm>(var->value->contents)->type){
                                case Parser::EXPRESSION_TERM_LITERAL_INT:
                                case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
                                case Parser::EXPRESSION_TERM_LITERAL_STRING:
                                    continue;//don't add assignment if is literal, already handled by frame defaults
                                default:
                                    break;
                                }
                            }
                            code.push_back(std::make_shared<Interpreter_Expression>(default_frame,std::make_shared<Parser::Expression>(
                                    std::make_shared<Parser::BinaryOperation>(
                                        std::make_shared<Parser::ExpressionTerm>(std::make_shared<Lexer::WordToken>(0,var->name),Parser::EXPRESSION_TERM_IDENTIFIER),
                                        std::make_shared<Lexer::SymbolToken>(0,get_symbol_data(SYMBOL_ASSIGNMENT)),
                                        var->value),Parser::EXPRESSION_BINARY_OPERATION)));//always add assignment unless literal
                        }
                    }
                }
            default:
                default_frame->add_definition(def);//always add definition to frame
                break;
            }
        }
        break;
    case Parser::LINE_EMPTY://do nothing
        break;
    }
}

std::string Interpreter_Variable::get_name(){
    return name;
}

Int_Value::Int_Value(int i):value(i){}
Int_Value::operator int&(){
    return value;
}

int& Int_Value::get(){
    return value;
}

std::shared_ptr<Parser::VarType> Int_Value::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_INT);
}

Float_Value::Float_Value(double d):value(d){}

Float_Value::operator double&(){
    return value;
}

double& Float_Value::get(){
    return value;
}

std::shared_ptr<Parser::VarType> Float_Value::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_FLOAT);
}

String_Value::String_Value(std::string s):value(s){}

String_Value::operator std::string&(){
    return value;
}

std::string& String_Value::get(){
    return value;
}

std::shared_ptr<Parser::VarType> String_Value::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_STRING);
}

Int_Variable::Int_Variable(int i):Int_Value(i){}
Float_Variable::Float_Variable(double d):Float_Value(d){}
String_Variable::String_Variable(std::string s):String_Value(s){}

Interpreted_Function_Call::Interpreted_Function_Call(std::shared_ptr<Parser::FunctionDefinition> func):function(func){}

std::string Interpreted_Function_Call::get_name(){
    return function->name;
}

std::shared_ptr<Parser::VarType> Interpreted_Function_Call::get_type(){
    return function->return_type;
}

std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> Interpreted_Function_Call::get_parameters(){
    return function->parameters;
}

std::shared_ptr<Interpreter_Value> Interpreted_Function_Call::call(std::shared_ptr<Interpreter_ExecFrame> parent_frame,std::map<std::string,std::shared_ptr<Interpreter_Value>> args){
    //TODO Interpreted_Function_Call::call
    throw std::runtime_error("unimplemented");
}

Interpreter_Frame::Interpreter_Frame(){}

Interpreter_Frame::Interpreter_Frame(std::shared_ptr<Interpreter_Frame> p):parent(p){
}

Interpreter_Frame::Interpreter_Frame(std::vector<std::shared_ptr<Parser::Definition>> deflist){
    for(std::shared_ptr<Parser::Definition>def:deflist){
        add_definition(def,true);
    }
}

void Interpreter_Frame::add_definition(std::shared_ptr<Parser::Definition> def,bool global){
    switch(def->type){
    case Parser::DEFINITION_VAR:{
            std::shared_ptr<Parser::VariableDefinition> vars(std::static_pointer_cast<Parser::VariableDefinition>(def->def));
            for(std::shared_ptr<Parser::VariableDefinitionItem> var:vars->variables){
                add_variable(vars->type,var,global);
            }
        }
        break;
    case Parser::DEFINITION_FUNC:
        add_function(std::static_pointer_cast<Parser::FunctionDefinition>(def->def));
        break;
    }
}

void Interpreter_Frame::add_function(std::shared_ptr<Parser::FunctionDefinition> func){
    interpreted_functions.insert({func->name,std::make_shared<Interpreted_Function_Call>(func)});
}

void Interpreter_Frame::add_variable(std::shared_ptr<Parser::VarType> type,std::shared_ptr<Parser::VariableDefinitionItem> var,bool global){
    if(type->type!=Parser::VARTYPE_PRIMITIVE){
        throw std::runtime_error("variables must be a primitive type");
    }
    if(var->value){
        if(var->value->type==Parser::EXPRESSION_TERM){
            std::shared_ptr<Parser::ExpressionTerm> term(std::static_pointer_cast<Parser::ExpressionTerm>(var->value->contents));
            switch(term->type){
            case Parser::EXPRESSION_TERM_LITERAL_INT:
                switch(type->primitive){
                case Parser::PRIMITIVE_INT:
                    variable_defaults.insert({var->name,std::make_shared<Int_Variable>(std::static_pointer_cast<Lexer::IntegerToken>(term->contents_t)->get_integer())});
                    break;
                case Parser::PRIMITIVE_FLOAT:
                    variable_defaults.insert({var->name,std::make_shared<Float_Variable>(std::static_pointer_cast<Lexer::IntegerToken>(term->contents_t)->get_integer())});
                    break;
                case Parser::PRIMITIVE_STRING:
                    throw std::runtime_error("cannot assign string to number");
                    break;
                case Parser::PRIMITIVE_INVALID:
                    throw std::runtime_error("invalid primitive type");
                }
                break;
            case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
                switch(type->primitive){
                case Parser::PRIMITIVE_INT:
                    variable_defaults.insert({var->name,std::make_shared<Int_Variable>(std::static_pointer_cast<Lexer::FloatToken>(term->contents_t)->get_float())});
                    break;
                case Parser::PRIMITIVE_FLOAT:
                    variable_defaults.insert({var->name,std::make_shared<Float_Variable>(std::static_pointer_cast<Lexer::FloatToken>(term->contents_t)->get_float())});
                    break;
                case Parser::PRIMITIVE_STRING:
                    throw std::runtime_error("cannot assign string to number");
                    break;
                case Parser::PRIMITIVE_INVALID:
                    throw std::runtime_error("invalid primitive type");
                }
                break;
            case Parser::EXPRESSION_TERM_LITERAL_STRING:
                switch(type->primitive){
                case Parser::PRIMITIVE_INT:
                case Parser::PRIMITIVE_FLOAT:
                    throw std::runtime_error("cannot assign number to string");
                    break;
                case Parser::PRIMITIVE_STRING:
                    variable_defaults.insert({var->name,std::make_shared<String_Variable>(std::static_pointer_cast<Lexer::StringToken>(term->contents_t)->get_string())});
                    break;
                case Parser::PRIMITIVE_INVALID:
                    throw std::runtime_error("invalid primitive type");
                }
                break;
            default:
                if(global)throw std::runtime_error("global variables can only be initiated to literals");
            }
        }
    }else{
        switch(type->primitive){
        case Parser::PRIMITIVE_INT:
            variable_defaults.insert({var->name,std::make_shared<Int_Variable>(0)});
            break;
        case Parser::PRIMITIVE_FLOAT:
            variable_defaults.insert({var->name,std::make_shared<Float_Variable>(0)});
            break;
        case Parser::PRIMITIVE_STRING:
            variable_defaults.insert({var->name,std::make_shared<String_Variable>("")});
            break;
        case Parser::PRIMITIVE_INVALID:
            throw std::runtime_error("invalid primitive type");
        }
    }
}


std::shared_ptr<Interpreter_Variable> Interpreter_Frame::get_variable(std::string name){
    MAP_GET(variable_defaults,name,parent?parent->get_variable(name):nullptr)
}

std::shared_ptr<Function_Call> Interpreter_Frame::get_function(std::string name){
    MAP_FIND(interpreted_functions,name){
        return iter->second;
    }else{
        MAP_FIND(native_functions,name){
            return iter->second;
        }else{
            return parent?parent->get_function(name):nullptr;
        }
    }
}

void Interpreter_Frame::register_native_function(std::shared_ptr<Native_Function_Call> func){
    if(MAP_HAS(native_functions,func->get_name())){
        throw std::runtime_error("Redefining Native Function "+func->get_name());
    }else{
        native_functions.insert({func->get_name(),func});
    }
}

Interpreter_Test::Interpreter_Test(std::vector<std::shared_ptr<Parser::Definition>> df){
    build_frame(df);
}

void Interpreter_Test::run(std::string entrypoint_name){
    run(std::make_shared<Interpreter_ExecFrame>(nullptr,frame),entrypoint_name);
}

void Interpreter_Test::run(std::shared_ptr<Interpreter_ExecFrame> exframe,std::string entrypoint_name){
    std::shared_ptr<Function_Call> entrypoint(exframe->get_function(entrypoint_name));
    if(entrypoint){
        if(entrypoint->get_parameters().empty()){
            entrypoint->call(exframe,std::map<std::string,std::shared_ptr<Interpreter_Value>>());
        }else{
            throw std::runtime_error(entrypoint_name+" cannot have parameters");
        }
    }
}

void Interpreter_Test::build_frame(std::vector<std::shared_ptr<Parser::Definition>> deflist){
    frame=std::make_shared<Interpreter_Frame>(deflist);
    frame->register_native_function(std::make_shared<Print_Function>());
}

