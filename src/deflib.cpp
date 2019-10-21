#include "deflib.h"
#include <iostream>
#include "Interpreter/Function.h"
#include "Parser/VarType.h"
#include "Interpreter/TypeValue.h"
#include "Interpreter/AnyValue.h"
#include "Interpreter/StringValue.h"
#include "Interpreter/ArrayValue.h"
#include "Interpreter/IntValue.h"
#include "Interpreter/UnsignedIntValue.h"
#include "Interpreter/CharValue.h"
#include "Interpreter/UnsignedCharValue.h"
#include "Interpreter/FloatValue.h"
#include "Interpreter/PointerValue.h"

#include "MyExcept/MyExcept.h"
#include "Interpreter/valueToString.h"
#include "Printf/Printf.h"

#include <cstdlib>
#include <ctime>

#include "Util/Console.h"

#ifdef _MSC_VER

//disable c runtime deprecation warnings for MSVC

#pragma warning( disable : 4996 )

#endif

//NOTE native functions to make later
//void printvals(...) DONE;
//string sprintf(string format,...) DONE
//int printf(string format,...) DONE
//void print(string) DONE
//void putchar(int) DONE
//string getline() DONE
//int stoi(string) DONE
//float stof(string) DONE
//string to_string(any) DONE
//void cls() DONE
//int getch() DONE //only works for characters
//int getch_wasd() DONE //return arrow keys as 'wasd', might not be available on linux
//int array_size(any[]) DONE
//string get_type_name(type) DONE
//ptr<void> fopen(string filename,int write) DONE //if write true, open as "w", if write false, open as "r"
//void fclose(ptr<void>) DONE
//int fputs(string,ptr<void>) DONE
//int fputs(string,length,ptr<void>) DONE
//int fprintf(ptr<void>,string format, any ... args) DONE
//char fgetc(ptr<void>) DONE
//string fgets(unsigned int len,ptr<void>) DONE
//void fseek(ptr<void>,unsigned int location) DONE, operates as SEEK_SET
//void fseek(ptr<void>) DONE operates as SEEK_END
//int ftell(ptr<void>) DONE
//int rand() DONE

//void push_front(any[],any) TODO
//void push_back(any[],any) TODO
//any pop_front(any[]) TODO
//any pop_back(any[]) TODO
//any peek_front(any[]) TODO
//any peek_back(any[]) TODO
//void resize(any[]) TODO

static std::string escape(char c){
    switch(c) {
    case '\a':
        return "\\a";
    case '\b':
        return "\\b";
    case '\t':
        return "\\t";
    case '\n':
        return "\\n";
    case '\v':
        return "\\v";
    case '\f':
        return "\\f";
    case '\r':
        return "\\r";
    case '\\':
        return "\\\\";
    case '\"':
        return "\\\"";
    default:
        return iscntrl(c)?"":std::string(1,c);
    }
}

std::string Interpreter::valueToString(std::shared_ptr<Value> val){
    if(auto v1=std::dynamic_pointer_cast<ArrayValue>(val)){
        return v1->getString();
    }else if(auto c1=std::dynamic_pointer_cast<CharValue>(val)){
        return "'"+std::string(1,c1->get())+"'";
    }else if(auto v2=std::dynamic_pointer_cast<UnsignedCharValue>(val)){
        return std::to_string(v2->get());
    }else if(auto v3=std::dynamic_pointer_cast<IntValue>(val)){
        return std::to_string(v3->get());
    }else if(auto v4=std::dynamic_pointer_cast<UnsignedIntValue>(val)){
        return std::to_string(v4->get());
    }else if(auto v5=std::dynamic_pointer_cast<FloatValue>(val)){
        return std::to_string(v5->get());
    }else if(auto s=std::dynamic_pointer_cast<StringValue>(val)){
        std::string temp="\"";
        for(char c2:s->get()){
            temp+=escape(c2);
        }
        temp+="\"";
        return temp;
    }else if(auto p=std::dynamic_pointer_cast<PointerValue>(val)){
        return (p->get_value()?"* "+valueToString(p->get_value()):"(null)");
    }else if(auto t=std::dynamic_pointer_cast<TypeValue>(val)){
        return "type<"+t->get()->get_name()+">";
    }else{
        return "("+val->get_type()->get_name()+") unknown";
    }
}

namespace Interpreter {

    struct prepare_printf_out{
        std::string fmt;
        std::vector<std::shared_ptr<Printf::ValueContainer>> params;
    };
    static inline prepare_printf_out prepare_printf(std::vector<std::shared_ptr<Value>> args,size_t fmt_index,size_t params_start){
        prepare_printf_out out;
        out.fmt=std::dynamic_pointer_cast<StringValue>(args[fmt_index])->get();
        std::vector<std::shared_ptr<Printf::ValueContainer>> params;
        for(size_t i=params_start;i<args.size();i++){
            out.params.push_back(std::dynamic_pointer_cast<Printf::ValueContainer>(args[i]));
        }
        for(size_t i=0;i<out.fmt.size();i++){
            if(out.fmt[i]=='%'){
                for(;out.fmt[i-1]!='{';i++){
                    if(i>=out.fmt.size()||out.fmt[i]==' ')goto skip;
                }
                if(i<out.fmt.size()&&out.fmt[i]!='}'){
                    size_t start=i;
                    size_t len=0;
                    std::string ntemp;
                    for(len=0;i+len<out.fmt.size()&&out.fmt[i+len]!='}';len++){
                        ntemp+=out.fmt[i+len];
                    }
                    for(size_t i2=0;i2<out.params.size();i2++){
                        if(auto v=std::dynamic_pointer_cast<Variable>(out.params[i2])){
                            //won't work for references, since a reference's get_name will return the name of the original variable it points to
                            if(v->get_name()==ntemp){
                                out.fmt.replace(start,len,std::to_string(i2));
                                break;
                            }
                        }
                    }
                }
            }
        skip:;
        }
        return out;
    }

    class printf : public Function {

        bool is_variadic() override{
            return true;
        }

        std::shared_ptr<Type> get_variadic_type() override{
            return Type::any_type();
        }

        std::string get_name() override {
            return "printf";
        }

        std::shared_ptr<Type> get_type() override {
            return Type::int_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::string_type(),"fmt",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            prepare_printf_out data=prepare_printf(args,0,1);
            return std::make_shared<IntValue>(Printf::vprintf(data.fmt,data.params));
        }

    };

    class sprintf : public Function {

        bool is_variadic() override{
            return true;
        }

        std::shared_ptr<Type> get_variadic_type() override{
            return Type::any_type();
        }

        std::string get_name() override {
            return "sprintf";
        }

        std::shared_ptr<Type> get_type() override {
            return Type::string_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::string_type(),"fmt",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            prepare_printf_out data=prepare_printf(args,0,1);
            return std::make_shared<StringValue>(Printf::vsprintf(data.fmt,data.params));
        }
    };

    class printvals : public Function {

        bool is_variadic() override{
            return true;
        }

        std::shared_ptr<Type> get_variadic_type() override{
            return Type::any_type();
        }

        std::string get_name() override {
            return "printvals";
        }

        std::shared_ptr<Type> get_type() override {
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            for(auto v:args){
                if(auto var=std::dynamic_pointer_cast<Variable>(v)){
                    std::cout<<v->get_type()->get_name()<<" "<<var->get_name()<<" = "<<valueToString(v)<<"\n";
                }else{
                    std::cout<<"("<<v->get_type()->get_name()<<") "<<valueToString(v)<<"\n";
                }
            }
            return nullptr;
        }

    };

    class print : public Function {

        std::string get_name() override {
            return "print";
        }

        std::shared_ptr<Type> get_type() override {
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::string_type(),"str",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            //todo handle multiple types
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

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
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

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
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

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
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

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
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

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            Console::clear();
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

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<IntValue>(Console::getch());
        }

    };

    class getch_wasd : public Function{

        std::string get_name() override {
            return "getch_wasd";
        }

        std::shared_ptr<Type> get_type(){
            return Type::int_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<IntValue>(Console::getch_wasd());
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

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
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

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<IntValue>(std::dynamic_pointer_cast<ArrayValue>(args[0])->get().size());
        }

    };

    class get_type_name : public Function{

        std::string get_name() override {
            return "get_type_name";
        }

        std::shared_ptr<Type> get_type(){
            return Type::string_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::type_type(),"t",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<StringValue>(std::dynamic_pointer_cast<TypeValue>(args[0])->get()->get_name());
        }
    };

    class FILE_Value : public AnyValue {
        public:
            FILE_Value(std::string filename,int mode):FILE_Value(::fopen(filename.c_str(),mode?"w":"r")){
            }
            FILE_Value(FILE * fp):f(fp){
            }
            ~FILE_Value(){
                close();
            }
            void close(){
                if(f)::fclose(f);
                f=nullptr;
            }
            FILE * f;
    };

    class fopen : public Function {
        std::string get_name() override {
            return "fopen";
        }

        std::shared_ptr<Type> get_type(){
            return Type::pointer_type(Type::void_type());
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::string_type(),"filename",false},{Type::int_type(),"readmode",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<PointerValue>(Type::void_type(),std::make_shared<FILE_Value>(std::dynamic_pointer_cast<StringValue>(args[0])->get().c_str(),std::dynamic_pointer_cast<IntValue>(args[1])->get()));
        }

    };

    class fclose : public Function {
        std::string get_name() override {
            return "fclose";
        }

        std::shared_ptr<Type> get_type(){
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::pointer_type(Type::void_type()),"file",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            std::shared_ptr<FILE_Value> f=std::dynamic_pointer_cast<FILE_Value>(std::dynamic_pointer_cast<PointerValue>(args[0])->get_value());
            if(f){
                f->close();
            }
            return nullptr;
        }

    };

    class fputs : public Function {
        std::string get_name() override {
            return "fputs";
        }

        std::shared_ptr<Type> get_type(){
            return Type::int_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::string_type(),"str",false},{Type::pointer_type(Type::void_type()),"file",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            std::shared_ptr<FILE_Value> f=std::dynamic_pointer_cast<FILE_Value>(std::dynamic_pointer_cast<PointerValue>(args[1])->get_value());
            if(f){
                if(f->f){
                    return std::make_shared<IntValue>(::fputs(std::dynamic_pointer_cast<StringValue>(args[0])->get().c_str(),f->f));
                }
            }
            return std::make_shared<IntValue>(0);
        }

    };

    class fputs_len : public Function {
        std::string get_name() override {
            return "fputs";
        }

        std::shared_ptr<Type> get_type(){
            return Type::int_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::string_type(),"str",false},{Type::int_type(),"len",false},{Type::pointer_type(Type::void_type()),"file",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            std::shared_ptr<FILE_Value> f=std::dynamic_pointer_cast<FILE_Value>(std::dynamic_pointer_cast<PointerValue>(args[2])->get_value());
            if(f){
                if(f->f){
                    return std::make_shared<IntValue>(::fputs(std::dynamic_pointer_cast<StringValue>(args[0])->get().substr(0,std::dynamic_pointer_cast<IntValue>(args[1])->get()).c_str(),f->f));
                }
            }
            return std::make_shared<IntValue>(0);
        }

    };

    class fprintf : public Function {

        bool is_variadic() override{
            return true;
        }

        std::shared_ptr<Type> get_variadic_type() override{
            return Type::any_type();
        }

        std::string get_name() override {
            return "fprintf";
        }

        std::shared_ptr<Type> get_type() override {
            return Type::int_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::pointer_type(Type::void_type()),"file",false},{Type::string_type(),"fmt",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            std::shared_ptr<FILE_Value> f=std::dynamic_pointer_cast<FILE_Value>(std::dynamic_pointer_cast<PointerValue>(args[0])->get_value());
            if(f){
                if(f->f){
                    prepare_printf_out data=prepare_printf(args,1,2);
                    return std::make_shared<IntValue>(::fputs(Printf::vsprintf(data.fmt,data.params).c_str(),f->f));
                }
            }
            return std::make_shared<IntValue>(0);
        }

    };

    class fgetc : public Function {
        std::string get_name() override {
            return "fgetc";
        }

        std::shared_ptr<Type> get_type(){
            return Type::char_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::pointer_type(Type::void_type()),"file",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            std::shared_ptr<FILE_Value> f=std::dynamic_pointer_cast<FILE_Value>(std::dynamic_pointer_cast<PointerValue>(args[0])->get_value());
            if(f){
                if(f->f){
                    return std::make_shared<CharValue>(static_cast<char>(::fgetc(f->f)));
                }
            }
            return std::make_shared<CharValue>('\0');
        }

    };

    class fgets : public Function {
        std::string get_name() override {
            return "fgets";
        }

        std::shared_ptr<Type> get_type(){
            return Type::string_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::unsigned_int_type(),"len",false},{Type::pointer_type(Type::void_type()),"file",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            std::shared_ptr<FILE_Value> f=std::dynamic_pointer_cast<FILE_Value>(std::dynamic_pointer_cast<PointerValue>(args[1])->get_value());
            if(f){
                if(f->f){
                    std::shared_ptr<char> buf(static_cast<char*>(calloc(std::dynamic_pointer_cast<UnsignedIntValue>(args[0])->get()+1,sizeof(char))),free);
                    if(::fgets(buf.get(),std::dynamic_pointer_cast<UnsignedIntValue>(args[0])->get(),f->f)){
                        return std::make_shared<StringValue>(buf.get());
                    }else{
                        return std::make_shared<StringValue>("");
                    }
                }
            }
            return std::make_shared<StringValue>("");
        }

    };

    class fseek : public Function {
        std::string get_name() override {
            return "fseek";
        }

        std::shared_ptr<Type> get_type(){
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::pointer_type(Type::void_type()),"file",false},{Type::unsigned_int_type(),"len",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            std::shared_ptr<FILE_Value> f=std::dynamic_pointer_cast<FILE_Value>(std::dynamic_pointer_cast<PointerValue>(args[0])->get_value());
            if(f){
                if(f->f){
                    ::fseek(f->f,std::dynamic_pointer_cast<UnsignedIntValue>(args[1])->get(),SEEK_SET);
                }
            }
            return nullptr;
        }

    };

    class fseek_end : public Function {
        std::string get_name() override {
            return "fseek";
        }

        std::shared_ptr<Type> get_type(){
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::pointer_type(Type::void_type()),"file",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            std::shared_ptr<FILE_Value> f=std::dynamic_pointer_cast<FILE_Value>(std::dynamic_pointer_cast<PointerValue>(args[0])->get_value());
            if(f){
                if(f->f){
                    ::fseek(f->f,0,SEEK_END);
                }
            }
            return nullptr;
        }

    };

    class ftell : public Function {
        std::string get_name() override {
            return "ftell";
        }

        std::shared_ptr<Type> get_type(){
            return Type::int_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{Type::pointer_type(Type::void_type()),"file",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            std::shared_ptr<FILE_Value> f=std::dynamic_pointer_cast<FILE_Value>(std::dynamic_pointer_cast<PointerValue>(args[0])->get_value());
            if(f){
                if(f->f){
                    return std::make_shared<IntValue>(::ftell(f->f));
                }
            }
            return std::make_shared<IntValue>(-1);
        }

    };

    class rand : public Function {
        std::string get_name() override {
            return "rand";
        }

        std::shared_ptr<Type> get_type(){
            return Type::int_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            return std::make_shared<IntValue>(::rand());
        }

    };

    class push_front : public Function{

        std::string get_name() override {
            return "push_front";
        }

        std::shared_ptr<Type> get_type(){
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{std::make_shared<ArrayType>(Type::any_type(),-1),"arr",true},{Type::any_type(),"val",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            auto arrv=std::dynamic_pointer_cast<ArrayValue>(args[0]);
            auto arrt=std::dynamic_pointer_cast<ArrayType>(arrv->get_type());
            if(arrt->get_size()!=-1){
                throw std::runtime_error("can't push to a sized array");
            }
            auto val=args[1]->get_type()->cast(args[1],arrt->get_type());
            arrv->get().insert(arrv->get().begin(),val);
            return nullptr;
        }

    };

    class push_back : public Function{

        std::string get_name() override {
            return "push_back";
        }

        std::shared_ptr<Type> get_type(){
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{std::make_shared<ArrayType>(Type::any_type(),-1),"arr",true},{Type::any_type(),"val",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            auto arrv=std::dynamic_pointer_cast<ArrayValue>(args[0]);
            auto arrt=std::dynamic_pointer_cast<ArrayType>(arrv->get_type());
            if(arrt->get_size()!=-1){
                throw std::runtime_error("can't push to a sized array");
            }
            auto val=args[1]->get_type()->cast(args[1],arrt->get_type());
            arrv->get().push_back(val);
            return nullptr;
        }

    };

    class pop_front : public Function{

        std::string get_name() override {
            return "pop_front";
        }

        std::shared_ptr<Type> get_type(){
            return Type::any_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{std::make_shared<ArrayType>(Type::any_type(),-1),"arr",true}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            auto arrv=std::dynamic_pointer_cast<ArrayValue>(args[0]);
            auto arrt=std::dynamic_pointer_cast<ArrayType>(arrv->get_type());
            if(arrt->get_size()!=-1){
                throw std::runtime_error("can't pop a sized array");
            }else if(arrv->get().size()==0){
                throw std::runtime_error("can't pop an empty array");
            }
            auto val=arrv->get().at(0);
            arrv->get().erase(arrv->get().begin());
            return val;
        }

    };

    class pop_back : public Function{

        std::string get_name() override {
            return "pop_back";
        }

        std::shared_ptr<Type> get_type(){
            return Type::any_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{std::make_shared<ArrayType>(Type::any_type(),-1),"arr",true}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            auto arrv=std::dynamic_pointer_cast<ArrayValue>(args[0]);
            auto arrt=std::dynamic_pointer_cast<ArrayType>(arrv->get_type());
            if(arrt->get_size()!=-1){
                throw std::runtime_error("can't pop a sized array");
            }else if(arrv->get().size()==0){
                throw std::runtime_error("can't pop an empty array");
            }
            auto val=arrv->get().back();
            arrv->get().pop_back();
            return val;
        }

    };

    class peek_front : public Function{

        std::string get_name() override {
            return "peek_front";
        }

        std::shared_ptr<Type> get_type(){
            return Type::any_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{std::make_shared<ArrayType>(Type::any_type(),-1),"arr",true}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            auto arrv=std::dynamic_pointer_cast<ArrayValue>(args[0]);
            auto arrt=std::dynamic_pointer_cast<ArrayType>(arrv->get_type());
            if(arrt->get_size()!=-1){
                throw std::runtime_error("can't peek a sized array");
            }else if(arrv->get().size()==0){
                throw std::runtime_error("can't peek an empty array");
            }
            return arrv->get().at(0);
        }

    };

    class peek_back : public Function{

        std::string get_name() override {
            return "peek_back";
        }

        std::shared_ptr<Type> get_type(){
            return Type::any_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{std::make_shared<ArrayType>(Type::any_type(),-1),"arr",true}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            auto arrv=std::dynamic_pointer_cast<ArrayValue>(args[0]);
            auto arrt=std::dynamic_pointer_cast<ArrayType>(arrv->get_type());
            if(arrt->get_size()!=-1){
                throw std::runtime_error("can't peek a sized array");
            }else if(arrv->get().size()==0){
                throw std::runtime_error("can't peek an empty array");
            }
            return arrv->get().back();
        }

    };

    class resize : public Function{

        std::string get_name() override {
            return "resize";
        }

        std::shared_ptr<Type> get_type(){
            return Type::void_type();
        }

        std::vector<FunctionParameter> get_parameters() override {
            return {{std::make_shared<ArrayType>(Type::any_type(),-1),"arr",true},{Type::int_type(),"size",false}};
        }

        std::shared_ptr<Value> call(ExecFrame *,std::vector<std::shared_ptr<Value>> args) override {
            auto arrv=std::dynamic_pointer_cast<ArrayValue>(args[0]);
            auto arrt=std::dynamic_pointer_cast<ArrayType>(arrv->get_type());
            if(arrt->get_size()!=-1){
                throw std::runtime_error("can't resize a sized array");
            }
            auto val=std::dynamic_pointer_cast<IntValue>(args[1]->get_type()->cast(args[1],Type::int_type()));
            if(val->get()<0){
                throw std::runtime_error("new size too small");
            }
            if(val->get()>int(arrv->get().size())){
                int osz=arrv->get().size();
                arrv->get().resize(val->get());
                for(int i=osz;i<val->get();i++){
                    arrv->get()[i]=arrt->get_type()->make_value(arrt->get_type());
                }
            }else{
                arrv->get().resize(val->get());
            }
            return nullptr;
        }

    };

}

void Interpreter::init_deflib(DefaultFrame * d){
    srand(static_cast<unsigned int>(time(NULL)));
    d->register_function(std::make_shared<Interpreter::printf>());
    d->register_function(std::make_shared<Interpreter::sprintf>());
    d->register_function(std::make_shared<Interpreter::printvals>());
    d->register_function(std::make_shared<Interpreter::print>());
    d->register_function(std::make_shared<Interpreter::putchar>());
    d->register_function(std::make_shared<Interpreter::getline>());
    d->register_function(std::make_shared<Interpreter::stoi>());
    d->register_function(std::make_shared<Interpreter::stof>());
    d->register_function(std::make_shared<Interpreter::to_string>());
    d->register_function(std::make_shared<Interpreter::cls>());
    d->register_function(std::make_shared<Interpreter::getch>());
    d->register_function(std::make_shared<Interpreter::getch_wasd>());
    d->register_function(std::make_shared<Interpreter::array_size>());
    d->register_function(std::make_shared<Interpreter::get_type_name>());
    d->register_function(std::make_shared<Interpreter::fopen>());
    d->register_function(std::make_shared<Interpreter::fclose>());
    d->register_function(std::make_shared<Interpreter::fputs>());
    d->register_function(std::make_shared<Interpreter::fputs_len>());
    d->register_function(std::make_shared<Interpreter::fprintf>());
    d->register_function(std::make_shared<Interpreter::fgetc>());
    d->register_function(std::make_shared<Interpreter::fgets>());
    d->register_function(std::make_shared<Interpreter::fseek>());
    d->register_function(std::make_shared<Interpreter::fseek_end>());
    d->register_function(std::make_shared<Interpreter::ftell>());
    d->register_function(std::make_shared<Interpreter::rand>());
    d->register_function(std::make_shared<Interpreter::push_front>());
    d->register_function(std::make_shared<Interpreter::push_back>());
    d->register_function(std::make_shared<Interpreter::pop_front>());
    d->register_function(std::make_shared<Interpreter::pop_back>());
    d->register_function(std::make_shared<Interpreter::peek_front>());
    d->register_function(std::make_shared<Interpreter::peek_back>());
    d->register_function(std::make_shared<Interpreter::resize>());
}
