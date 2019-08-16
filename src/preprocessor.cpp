#include "preprocessor.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

//https://docs.microsoft.com/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output
std::string preprocess(std::string filename){
    std::stringstream ss;
    ss<<std::quoted(filename);
    std::string command="cpp -E "+ss.str();
    HANDLE stdout_rd_handle=NULL;
    HANDLE stdout_wr_handle=NULL;
    HANDLE stdin_rd_handle=NULL;
    HANDLE stdin_wr_handle=NULL;
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength=sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle=TRUE;
    saAttr.lpSecurityDescriptor=NULL;
    if(!CreatePipe(&stdout_rd_handle,&stdin_wr_handle,&saAttr,0)){
        throw std::runtime_error("stdout CreatePipe failed");
    }
    if(!SetHandleInformation(stdout_rd_handle,HANDLE_FLAG_INHERIT,0)){
        CloseHandle(stdout_wr_handle);
        CloseHandle(stdout_rd_handle);
        throw std::runtime_error("stdout_rd SetHandleInformation failed");
    }
    if(!CreatePipe(&stdin_rd_handle,&stdin_wr_handle,&saAttr,0)){
        CloseHandle(stdout_wr_handle);
        CloseHandle(stdout_rd_handle);
        throw std::runtime_error("stdin CreatePipe failed");
    }
    if(!SetHandleInformation(stdin_wr_handle,HANDLE_FLAG_INHERIT,0)){
        CloseHandle(stdin_wr_handle);
        CloseHandle(stdin_rd_handle);
        CloseHandle(stdout_wr_handle);
        CloseHandle(stdout_rd_handle);
        throw std::runtime_error("stdin_rd SetHandleInformation failed");
    }
    PROCESS_INFORMATION piProcInfo; 
    STARTUPINFO siStartInfo;
    ZeroMemory(&piProcInfo,sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo,sizeof(STARTUPINFO));
    siStartInfo.cb=sizeof(STARTUPINFO);
    siStartInfo.hStdError=stdout_wr_handle;
    siStartInfo.hStdOutput=stdout_wr_handle;
    siStartInfo.hStdInput=stdin_rd_handle;
    siStartInfo.dwFlags|=STARTF_USESTDHANDLES;
    std::cout<<"running "<<command<<"\n";
    if(!CreateProcess(NULL,(char*)command.c_str(),NULL,NULL,TRUE,0,NULL,NULL,&siStartInfo,&piProcInfo)){
        CloseHandle(stdin_wr_handle);
        CloseHandle(stdin_rd_handle);
        CloseHandle(stdout_wr_handle);
        CloseHandle(stdout_rd_handle);
        throw std::runtime_error("CreateProcess failed");
    }
    WaitForSingleObject(piProcInfo.hProcess,0);
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
    CloseHandle(stdin_wr_handle);
    CloseHandle(stdin_rd_handle);
    CloseHandle(stdout_wr_handle);
    std::string output;
    char buffer[128];
    while(true){//read pipe
        unsigned long bytes_read;
        ReadFile(stdout_rd_handle,buffer,127,&bytes_read,NULL);
        output+=std::string(buffer);
        if(bytes_read!=127){
            break;
        }
    }
    CloseHandle(stdout_rd_handle);
    return output;
}
