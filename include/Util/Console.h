#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

namespace Console{
    void sleep(int ms);
    void clear();
    void init();
    bool kbhit();
    int getch();
    int getch_wasd();
    void changeDir(std::string newdir);
}

#endif // CONSOLE_H
