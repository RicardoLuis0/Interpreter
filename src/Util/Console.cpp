#include "Util/Console.h"
#include <iostream>
#if defined (__WIN32__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#else
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <termios.h>
#include <cstdio>
#endif
namespace Console{

#if defined (__WIN32__)

    HANDLE hStdOut;

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

    bool kbhit(){
        return ::kbhit();
    }

    int getch(){
        char c=::getch();
        if(c==224){//ignore arrows
            ::getch();
            return 0;
        }else{
            return c;
        }
    }

    void changeDir(std::string newdir){
        SetCurrentDirectoryA(newdir.c_str());
    }

#elif defined (__linux__)

#warning operation under linux is still experimental

    void clear(){
        ::printf("\033[H\033[J");
    }

    void init(){
        //do nothing
    }

    bool kbhit(){
        timeval timeout;
        fd_set rdset;
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        timeout.tv_sec  = 0;
        timeout.tv_usec = 0;
        return select(STDIN_FILENO + 1, &rdset, NULL, NULL, &timeout);
    }

    int getch(){
        termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        while(read(STDIN_FILENO,&ch,1)==0);
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }

    void changeDir(std::string newdir){
        if(chdir(newdir.c_str()));
    }

#else

#error system not supported

#endif // __WIN32__

}
