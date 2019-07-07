#ifndef INTERPRETER_UTIL_DEFINES_MISC_H
#define INTERPRETER_UTIL_DEFINES_MISC_H

#define MAP_HAS(map,key) (map.find(key)!=map.end())

#define MAP_FIND(map,key)auto iter=map.find(key);if(iter!=map.end())

#define MAP_GET(map,key,other) MAP_FIND(map,key){return iter->second;}else{return other;}

#define MAP_SET(map,key,val,other) MAP_FIND(map,key){iter->second=val;}else{other;}

#endif // INTERPRETER_UTIL_DEFINES_MISC_H
