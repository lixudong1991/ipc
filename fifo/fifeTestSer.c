#include "../unpipc.h"

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

void serverWork(int pipein,int pipeout)
{
    int fd;
    ssize_t n;
    char    buff[MAXLINE];
    if((n=Read(pipein,buff,MAXLINE))==0)
        err_quit("end-of-file while reading pathname");
    buff[n]='\0';
    if((fd=open(buff,O_RDONLY))<0){
        snprintf(buff+n,sizeof(buff)-n,":cant open, %s\n",strerror(errno));
        n=strlen(buff);
        Write(pipeout,buff,n);
    }else{
        while((n=Read(fd,buff,MAXLINE))>0)
            Write(pipeout,buff,n);
        Close(fd);
    }
}
int main()
{
    int readfd,writefd;
    if((mkfifo(FIFO1,FILE_MODE)<0)&&(errno!=EEXIST))
        err_sys("can not create %s",FIFO1);
    if((mkfifo(FIFO2,FILE_MODE)<0)&&(errno!=EEXIST))
    {
        unlink(FIFO1);
        err_sys("can not create %s",FIFO2);
    }
    readfd=Open(FIFO1,O_RDONLY,0);
    writefd=Open(FIFO2,O_WRONLY,0);
    serverWork(readfd,writefd);
    Close(readfd);
    Close(writefd);
    exit(0);


}
