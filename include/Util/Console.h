#ifndef CONSOLE_H
#define CONSOLE_H

namespace Console{
    void clear();
    void init();
    bool kbhit();
    int getch();
    void changeDir(std::string newdir);
}

#endif // CONSOLE_H
