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
//半双工管道
int main(int argc,char **argv)
{
    int readfd,writefd;
    pid_t childpid;
    if((mkfifo(FIFO1,FILE_MODE)<0)&&(errno!=EEXIST))
        err_sys("can not create %s",FIFO1);
    if((mkfifo(FIFO2,FILE_MODE)<0)&&(errno!=EEXIST))
    {
        unlink(FIFO1);
        err_sys("can not create %s",FIFO2);
    }   
    if((childpid = Fork())==0){
        readfd=Open(FIFO1,O_RDONLY,0);
        writefd=Open(FIFO2,O_WRONLY,0);
        serverWork(readfd,writefd);
        exit(0);
    }
    writefd=Open(FIFO1,O_WRONLY,0);
    readfd=Open(FIFO2,O_RDONLY,0);
    clientWork(readfd,writefd);
    Waitpid(childpid,NULL,0);
    Close(readfd);
    Close(writefd);
    Unlink(FIFO1);
    Unlink(FIFO2);
    exit(0);
}
