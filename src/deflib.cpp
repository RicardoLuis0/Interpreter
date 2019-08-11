#include "deflib.h"
#include <iostream>
#include "interpreter_function.h"
#include "parser_var_type.h"
#include "interpreter_string_value.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "conio.h"

//NOTE native functions to make later
//void printf(string format, any ... args) TODO, varargs not implemented
//void puts(string) DONE
//void putchar(int) DONE
//string getline() DONE
//int stoi(string) DONE
//float stof(string)
//string itos(int) DONE
//string ftos(float) DONE
//void cls() DONE
//int getch() DONE
//int array_size(any[]) TODO

namespace Interpreter {
    class puts : public Function {

        std::string get_name() override {
            return "puts";
        }

        std::shared_ptr<Type> get_type() override {
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::string_type(),"str",false}};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            std::cout<<std::dynamic_pointer_cast<StringValue>(args[0])->get();
            return nullptr;
        }

    };

    class getline : public Function{

        std::string get_name() override {
            return "getline";
        }

        std::shared_ptr<Type> get_type(){
            return Type::string_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            std::string temp;
            while(std::cin.peek()=='\n')std::cin.ignore();
            std::getline(std::cin,temp,'\n');
            return std::make_shared<StringValue>(temp);
        }
    };

    class stoi : public Function{

        std::string get_name() override {
            return "stoi";
        }

        std::shared_ptr<Type> get_type(){
            return Type::int_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::string_type(),"str",false}};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            try{
                return std::make_shared<IntValue>(std::stoi(std::dynamic_pointer_cast<StringValue>(args[0])->get()));
            }catch(...){
                return std::make_shared<IntValue>(-1);
            }
        }
    };

    class itos : public Function{

        std::string get_name() override {
            return "itos";
        }

        std::shared_ptr<Type> get_type(){
            return Type::string_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::int_type(),"int",false}};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<StringValue>(std::to_string(std::dynamic_pointer_cast<IntValue>(args[0])->get()));
        }
    };

    class ftos : public Function{

        std::string get_name() override {
            return "ftos";
        }

        std::shared_ptr<Type> get_type(){
            return Type::string_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::float_type(),"float",false}};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<StringValue>(std::to_string(std::dynamic_pointer_cast<FloatValue>(args[0])->get()));
        }
    };

    class cls : public Function{

        std::string get_name() override {
            return "cls";
        }

        std::shared_ptr<Type> get_type(){
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            system("cls");
            return nullptr;
        }
    };

    class getch : public Function{

        std::string get_name() override {
            return "getch";
        }

        std::shared_ptr<Type> get_type(){
            return Type::int_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<IntValue>(::getch());
        }
    };

    class putchar : public Function{

        std::string get_name() override {
            return "putchar";
        }

        std::shared_ptr<Type> get_type(){
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::int_type(),"ch",false}};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            ::putchar(std::dynamic_pointer_cast<IntValue>(args[0])->get());
            return nullptr;
        }
    };

}

void Interpreter::init_deflib(DefaultFrame * d){
    d->register_function(std::make_shared<Interpreter::puts>());
    d->register_function(std::make_shared<Interpreter::putchar>());
    d->register_function(std::make_shared<Interpreter::getline>());
    d->register_function(std::make_shared<Interpreter::stoi>());
    d->register_function(std::make_shared<Interpreter::itos>());
    d->register_function(std::make_shared<Interpreter::ftos>());
    d->register_function(std::make_shared<Interpreter::cls>());
    d->register_function(std::make_shared<Interpreter::getch>());
}
