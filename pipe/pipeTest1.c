#include "../unpipc.h"
int main()
{
    int pipe1[2],pipe2[2],n,n1;
    char buff[1024],buff1[1024];
    pid_t childpid;
    Pipe(pipe1);
    Pipe(pipe2);
    if((childpid=Fork())==0)
    {
        Close(pipe1[1]);
        Close(pipe2[0]);
        n=Read(pipe1[0],buff,1024);
        buff[n]=0;
        Write(pipe2[1],buff,n);
        exit(0);
    }
    Close(pipe1[0]);
    Close(pipe2[1]);
    n1=Read(STDIN_FILENO,buff1,1024);
    Write(pipe1[1],buff1,n1);
    n1=Read(pipe2[0],buff1,1024);
    buff1[n1]=0;
    Write(STDOUT_FILENO,buff1,n1);
    Waitpid(childpid,NULL,0);
    exit(0);
}
