#include "../unpipc.h"
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

void clientWork(int pipein,int pipeou)
{
    size_t len;
    ssize_t n;
    char    buff[MAXLINE];
    Fgets(buff,MAXLINE,stdin);
    len=strlen(buff);
    if(buff[len-1] == '\n')
        len--;
    Write(pipeou,buff,len);
    while((n=Read(pipein,buff,MAXLINE))>0)
        Write(STDOUT_FILENO,buff,n);
}
int main(int argc,char **argv)
{
    int readfd,writefd;
    writefd=Open(FIFO1,O_WRONLY,0);
    readfd=Open(FIFO2,O_RDONLY,0);
    clientWork(readfd,writefd);
    Close(readfd);
    Close(writefd);
    Unlink(FIFO1);
    Unlink(FIFO2);
    exit(0);
}
