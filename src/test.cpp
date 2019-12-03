#include <string>
#include <vector>

struct test{
    std::string name;
    int (*fn)(void);
};

std::vector<test> tests {
};
int main(){
    for(auto t:tests){
        
    }
}
