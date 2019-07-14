#ifndef INTERPRETER_UTIL_DEFINES_MISC_H
#define INTERPRETER_UTIL_DEFINES_MISC_H

#include "parser_var_type.h"

#define MAP_HAS(map,key) (map.find(key)!=map.end())

#define MAP_FIND(map,key)auto iter=map.find(key);if(iter!=map.end())

#define MAP_GET(map,key,other) MAP_FIND(map,key){return iter->second;}else{return other;}

#define MAP_SET(map,key,val,other) MAP_FIND(map,key){iter->second=val;}else{other;}

#define CHECKPTR(ptr,type) (std::dynamic_pointer_cast<type>(ptr))

inline bool is_int(std::shared_ptr<Parser::VarType> vt){
    if(vt->type==Parser::VARTYPE_PRIMITIVE){
        return (vt->primitive==Parser::PRIMITIVE_INT);
    }
    return false;
}

inline bool is_float(std::shared_ptr<Parser::VarType> vt){
    if(vt->type==Parser::VARTYPE_PRIMITIVE){
        return (vt->primitive==Parser::PRIMITIVE_FLOAT);
    }
    return false;
}

inline bool is_num(std::shared_ptr<Parser::VarType> vt){
    return is_int(vt)||is_float(vt);
}

inline bool is_string(std::shared_ptr<Parser::VarType> vt){
    if(vt->type==Parser::VARTYPE_PRIMITIVE){
        return (vt->primitive==Parser::PRIMITIVE_STRING);
    }
    return false;
}

inline std::string get_name(std::shared_ptr<Parser::VarType> vt){
    if(is_int(vt))return "int";
    if(is_float(vt))return "float";
    if(is_string(vt))return "string";
    return "unknown";
}

inline bool is_compatible(std::shared_ptr<Parser::VarType> vt1,std::shared_ptr<Parser::VarType> vt2){
    if(is_num(vt1)&&is_num(vt2))return true;
    if(is_string(vt1)&&is_string(vt2))return true;
    return false;
}

inline bool type_eq(std::shared_ptr<Parser::VarType> vt1,std::shared_ptr<Parser::VarType> vt2){
    if(vt1->type==vt2->type){
        if(vt1->type==Parser::VARTYPE_PRIMITIVE){
            if(is_int(vt1)&&is_int(vt2))return true;
            if(is_float(vt1)&&is_float(vt2))return true;
            if(is_string(vt1)&&is_string(vt2))return true;
        }else{
            return true;
        }
    }
    return false;
}

#endif // INTERPRETER_UTIL_DEFINES_MISC_H
