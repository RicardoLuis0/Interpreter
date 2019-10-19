#include "Util/Console.h"
#include <iostream>
#if defined (__WIN32__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#endif
namespace Console{
#if defined (__WIN32__)
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
#else
    void waitInput(){
        //TODO 'pause' for linux
    }

    void clear(){
        std::cout<<"\e[3J";
    }

    void init(){
        //do nothing
    }
#endif // __WIN32__
}
