#include "Interpreter_Test.h"

class Print_Function : public Native_Function_Call{

    std::string get_name() override {
        return "print";
    }

    std::shared_ptr<Parser::VarType> get_type() override {
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

std::shared_ptr<Interpreter_Line_Run_Result> Interpreter_IfStatement::run(std::shared_ptr<Interpreter_ExecFrame> context){
    std::shared_ptr<Interpreter_Value> val=condition->eval(context);
    if(is_string(val->get_type()))throw std::runtime_error("string is not valid condition");
    bool do_code=false;
    if((is_int(val->get_type())&&std::dynamic_pointer_cast<Int_Value>(val)->get())||(is_float(val->get_type())&&std::dynamic_pointer_cast<Float_Value>(val)->get())){
        do_code=true;
    }
    if(do_code){
        return code->run(context);
    }else{
        return std::make_shared<Interpreter_Line_Run_Result_None>();
    }
}

std::shared_ptr<Interpreter_Line_Run_Result> Interpreter_ForStatement::run(std::shared_ptr<Interpreter_ExecFrame> context){
    pre->run(context);
    if(is_string(condition->final_type))throw std::runtime_error("string is not valid condition");
    std::shared_ptr<Interpreter_Value> val;
    while(1){
        val=condition->eval(context);
        bool do_code=false;
        if((is_int(val->get_type())&&std::dynamic_pointer_cast<Int_Value>(val)->get())||(is_float(val->get_type())&&std::dynamic_pointer_cast<Float_Value>(val)->get())){
            do_code=true;
        }
        if(do_code){
            std::shared_ptr<Interpreter_Line_Run_Result> r=code->run(context);
            if(!IS(r,Interpreter_Line_Run_Result_None))return r;
        }
        inc->run(context);
    }
    return std::make_shared<Interpreter_Line_Run_Result_None>();
}

std::shared_ptr<Interpreter_Line_Run_Result> Interpreter_WhileStatement::run(std::shared_ptr<Interpreter_ExecFrame> context){
    if(is_string(condition->final_type))throw std::runtime_error("string is not valid condition");
    std::shared_ptr<Interpreter_Value> val;
    while(1){
        val=condition->eval(context);
        bool do_code=false;
        if((is_int(val->get_type())&&std::dynamic_pointer_cast<Int_Value>(val)->get())||(is_float(val->get_type())&&std::dynamic_pointer_cast<Float_Value>(val)->get())){
            do_code=true;
        }
        if(do_code){
            std::shared_ptr<Interpreter_Line_Run_Result> r=code->run(context);
            if(!IS(r,Interpreter_Line_Run_Result_None))return r;
        }
    }
    return std::make_shared<Interpreter_Line_Run_Result_None>();
}

std::shared_ptr<Interpreter_Line_Run_Result> Interpreter_ReturnStatement::run(std::shared_ptr<Interpreter_ExecFrame> context){
    return std::make_shared<Interpreter_Line_Run_Result_Return>(value->eval(context));
}

Interpreter_IfStatement::Interpreter_IfStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::IfStatement> stmt){
    condition=std::make_shared<Interpreter_Expression>(context,stmt->condition);
    code=std::make_shared<Interpreter_Code>(context.get(),stmt->code);
    if(stmt->else_stmt){
        else_stmt=std::make_shared<Interpreter_Code>(context.get(),stmt->else_stmt->code);
    }
}

Interpreter_ForStatement::Interpreter_ForStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::ForStatement> stmt){
    pre=std::make_shared<Interpreter_Expression>(context,stmt->pre);
    condition=std::make_shared<Interpreter_Expression>(context,stmt->condition);
    inc=std::make_shared<Interpreter_Expression>(context,stmt->inc);
    code=std::make_shared<Interpreter_Code>(context.get(),stmt->code);
}

Interpreter_WhileStatement::Interpreter_WhileStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::WhileStatement> stmt){
    condition=std::make_shared<Interpreter_Expression>(context,stmt->condition);
    code=std::make_shared<Interpreter_Code>(context.get(),stmt->code);
}

Interpreter_ReturnStatement::Interpreter_ReturnStatement(std::shared_ptr<Interpreter_Frame> context,std::shared_ptr<Parser::ReturnStatement> stmt){
    value=std::make_shared<Interpreter_Expression>(context,stmt->value);
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

