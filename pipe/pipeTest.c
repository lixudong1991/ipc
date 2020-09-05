#include "../unpipc.h"
void serverWork(int pipein,int pipeout)
{
    int fd;
    ssize_t n;
    char    buff[MAXLINE];
    printf("read\n");
    if((n=Read(pipein,buff,MAXLINE))==0)
        err_quit("end-of-file while reading pathname");
    buff[n]='\0';
    printf("read end\n");
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
    int pipe1[2],pipe2[2];
    pid_t childpid;
    Pipe(pipe1);
    Pipe(pipe2);
    if((childpid = Fork())==0){
        Close(pipe1[1]);
        Close(pipe2[0]);
        serverWork(pipe1[0],pipe2[1]);
        exit(0);
    }
    Close(pipe1[0]);
    Close(pipe2[1]);
    clientWork(pipe2[0],pipe1[1]);
    Waitpid(childpid,NULL,0);
    exit(0);
}
//全双工管道
/*
int main()
{
    int fd[2],n;
    char c;
    pid_t childpid;
    Pipe(fd);
    socketpair(AF_UNIX, SOCK_STREAM, 0, fd);//设置管道为全双工
    if((childpid=Fork())==0){
        sleep(3);
        if((n=Read(fd[0],&c,1))!=1)
            err_quit("child:read returned %d",n);
        printf("child read %c\n",c);
        Write(fd[0],"c",c);
        exit(0);
    }
    Write(fd[1],"p",1);
    if((n=Read(fd[1],&c,1))!=1)
        err_quit("parent: read returned %d",n);
    printf("parent read %c\n",c);
    exit(0);
}
*/
