#include "console.h"
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <conio.h>

namespace Console{
    HANDLE hStdOut;

    void waitInput(){
        if(getch()==224)getch();
    }

    void clear() {
        unsigned long temp;
        CONSOLE_SCREEN_BUFFER_INFO s;
        GetConsoleScreenBufferInfo(hStdOut,&s);
        FillConsoleOutputCharacter(hStdOut,' ',s.dwSize.X*s.dwSize.Y,{0,0},&temp);
        FillConsoleOutputAttribute(hStdOut, s.wAttributes,s.dwSize.X*s.dwSize.Y,{0,0},&temp);
        SetConsoleCursorPosition(hStdOut,{0,0});
    }

    void init(){
        hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
        if(hStdOut==INVALID_HANDLE_VALUE){
            std::cout<<"Error getting stdout handle";
            exit(1);
        }
    }
}
