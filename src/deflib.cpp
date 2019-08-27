#include "deflib.h"
#include <iostream>
#include "interpreter_function.h"
#include "parser_var_type.h"
#include "interpreter_string_value.h"
#include "interpreter_array_value.h"
#include "interpreter_int_value.h"
#include "interpreter_unsigned_int_value.h"
#include "interpreter_char_value.h"
#include "interpreter_unsigned_char_value.h"
#include "interpreter_float_value.h"
#include "conio.h"
#include "my_except.h"

//NOTE native functions to make later
//int sprintf(string &output,string format, any ... args) TODO, varargs not implemented
//int printf(string format, any ... args) TODO
//void puts(string) DONE
//void putchar(int) DONE
//string getline() DONE
//int stoi(string) DONE
//float stof(string) DONE
//string to_string(any) DONE
//void cls() DONE
//int getch() DONE
//int array_size(any[]) DONE

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
            std::cout<<std::dynamic_pointer_cast<StringValue>(args[0]->get_type()->cast(args[0],Type::string_type()))->get();
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
                return std::make_shared<IntValue>(std::stoi(std::dynamic_pointer_cast<StringValue>(args[0]->get_type()->cast(args[0],Type::string_type()))->get()));
            }catch(...){
                return std::make_shared<IntValue>(-1);
            }
        }

    };


    class stof : public Function{

        std::string get_name() override {
            return "stof";
        }

        std::shared_ptr<Type> get_type(){
            return Type::float_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::string_type(),"str",false}};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            try{
                return std::make_shared<FloatValue>(std::stod(std::dynamic_pointer_cast<StringValue>(args[0]->get_type()->cast(args[0],Type::string_type()))->get()));
            }catch(...){
                return std::make_shared<FloatValue>(0);
            }
        }

    };

    class to_string : public Function{

        std::string get_name() override {
            return "to_string";
        }

        std::shared_ptr<Type> get_type(){
            return Type::string_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::any_type(),"val",false}};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            if(args[0]->get_type()->is(args[0]->get_type(),Type::string_type())){
                return args[0]->get_type()->cast(args[0],Type::string_type());
            }else if(args[0]->get_type()->is(args[0]->get_type(),Type::int_type())){
                return std::make_shared<StringValue>(std::to_string(std::dynamic_pointer_cast<IntValue>(args[0]->get_type()->cast(args[0],Type::int_type()))->get()));
            }else if(args[0]->get_type()->is(args[0]->get_type(),Type::unsigned_int_type())){
                return std::make_shared<StringValue>(std::to_string(std::dynamic_pointer_cast<UnsignedIntValue>(args[0]->get_type()->cast(args[0],Type::unsigned_int_type()))->get()));
            }else if(args[0]->get_type()->is(args[0]->get_type(),Type::char_type())){
                return std::make_shared<StringValue>(std::to_string(std::dynamic_pointer_cast<CharValue>(args[0]->get_type()->cast(args[0],Type::char_type()))->get()));
            }else if(args[0]->get_type()->is(args[0]->get_type(),Type::unsigned_char_type())){
                return std::make_shared<StringValue>(std::to_string(std::dynamic_pointer_cast<UnsignedCharValue>(args[0]->get_type()->cast(args[0],Type::unsigned_char_type()))->get()));

            }else if(args[0]->get_type()->is(args[0]->get_type(),Type::float_type())){
                return std::make_shared<StringValue>(std::to_string(std::dynamic_pointer_cast<FloatValue>(args[0]->get_type()->cast(args[0],Type::float_type()))->get()));
            }else{
                throw MyExcept::SyntaxError("invalid variable type "+args[0]->get_type()->get_name());
            }
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
            return {{Type::char_type(),"ch",false}};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            ::putchar(std::dynamic_pointer_cast<CharValue>(args[0]->get_type()->cast(args[0],Type::char_type()))->get());
            return nullptr;
        }

    };

    class array_size : public Function{

        std::string get_name() override {
            return "array_size";
        }

        std::shared_ptr<Type> get_type(){
            return Type::int_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{std::make_shared<ArrayType>(Type::any_type(),-1),"arr",false}};
        }

        std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<IntValue>(std::dynamic_pointer_cast<ArrayValue>(args[0])->get().size());
        }

    };

}

void Interpreter::init_deflib(DefaultFrame * d){
    d->register_function(std::make_shared<Interpreter::puts>());
    d->register_function(std::make_shared<Interpreter::putchar>());
    d->register_function(std::make_shared<Interpreter::getline>());
    d->register_function(std::make_shared<Interpreter::stoi>());
    d->register_function(std::make_shared<Interpreter::stof>());
    d->register_function(std::make_shared<Interpreter::to_string>());
    d->register_function(std::make_shared<Interpreter::cls>());
    d->register_function(std::make_shared<Interpreter::getch>());
    d->register_function(std::make_shared<Interpreter::array_size>());
}
