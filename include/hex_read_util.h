#ifndef HEX_READ_UTIL_H
#define HEX_READ_UTIL_H

constexpr bool is_hex(char c){
    return ((c>='0'&&c<='9')||(c>='A'&&c<='F')||(c>='a'&&c<='f'));
}
constexpr int get_hex(char c){
    return ((c>='0'&&c<='9')?(c-'0'):(c>='A'&&c<='F')?((c-'A')+10):(c>='a'&&c<='f')?((c-'a')+10):0);
}

#endif // HEX_READ_UTIL_H
