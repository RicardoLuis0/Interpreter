#ifndef PRINTF_H
#define PRINTF_H

#include <cstdlib>
#include <vector>

#include "Printf/ValueContainer.h"

namespace Printf{

    /*
        usage:
            param=%[length][.precision][type]{position}
                
                %% is escape for percent
                
                length:
                    number, padding/max characters to print,
                    if preceded by 0 and a number fill missing characters with 0, else fill with spaces, leading zero ignored if non-numeric,
                    if a string, prints only n characters, filling with spaces,
                    if a nubmer, prints at least n characters, but if the number is larger than n characters, prints the whole number
                
                precision:
                    number, precision for floating point numbers, ignored if non-floating point
                
                type 'c':
                    print number as character (casted to char or unsigned char), ignored if non-integral
                
                type 'f':
                    print number as fixed floating point, ignored if non-floating point
                
                type 'x':
                    print nubmer as hex, ignored if non-numeric
                
                type 'X':
                    print nubmer as uppercase hex, ignored if non-numeric
                
                type 'e':
                    print number as lowercase scientific notation, ignored if non-numeric
                
                type 'E':
                    print number as uppercase scientific notation, ignored if non-numeric
                
                position:
                    index of parameter in arglist, will not increment parameter index for non-positioned params
            
        example:
            printf("%3{}",99)
                :' 99'
            
            printf("%03{}",99)
                :'099'
            
            printf("%2{}",9999)
                :'9999'
            
            printf("%{2}",11,12)
                :'12'
            
            printf("%{}",'A')
                :'65'
            
            printf("%c{}",'A')
                :'A'
            
    */

    int vprintf(const std::string & fmt,std::vector<std::shared_ptr<ValueContainer>> args);

    std::string vsprintf(const std::string & fmt,std::vector<std::shared_ptr<ValueContainer>> args);

    struct pass{template<typename...Args>explicit pass(Args&&...){}};//variadic expansion helper, from https://stackoverflow.com/a/23859730

    template<typename... Tn> std::vector<std::shared_ptr<ValueContainer>> to_vc_p_vector(Tn... targs){
        std::vector<std::shared_ptr<ValueContainer>> temp;
        pass {(temp.push_back(as_vcp(targs)),0)...};
        return temp;
    }

    template<typename... Tn> std::string sprintf(const std::string & fmt,Tn... targs){
        return vsprintf(fmt,to_vc_p_vector(targs...));
    }

    template<typename... Tn> int printf(const std::string & fmt,Tn... targs){
        return vprintf(fmt,to_vc_p_vector(targs...));
    }

}

#endif // PRINTF_H
