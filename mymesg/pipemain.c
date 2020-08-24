#include "mesg.h"
void serverWork(int pipein,int pipeout)
{
    FILE *fp;
    ssize_t n;
    struct mymesg mesg;
    mesg.mesg_type=1;
    if((n=Mesg_recv(pipein,&mesg))==0)
        err_quit("pathname missing");
    mesg.mesg_data[n]='\0';
    if((fp=fopen(mesg.mesg_data,"r"))==NULL){
        snprintf(mesg.mesg_data+n,sizeof(mesg.mesg_data)-n,":cant open, %s\n",strerror(errno));
        mesg.mesg_len=strlen(mesg.mesg_data);
        Mesg_send(pipeout,&mesg);
    }else{
        while(Fgets(mesg.mesg_data,MAXMESGDATA,fp)!=NULL){
            mesg.mesg_len=strlen(mesg.mesg_data);
            Mesg_send(pipeout,&mesg);
        }
        Fclose(fp);
    }
    mesg.mesg_len=0;
    Mesg_send(pipeout,&mesg);
}
void clientWork(int pipein,int pipeou)
{
    size_t len;
    ssize_t n;
    struct mymesg mesg;
    Fgets(mesg.mesg_data,MAXMESGDATA,stdin);
    len=strlen(mesg.mesg_data);
    if(mesg.mesg_data[len-1] == '\n')
        len--;
    mesg.mesg_len=len;
    mesg.mesg_type=1;
    Mesg_send(pipeou,&mesg);
    while((n=Mesg_recv(pipein,&mesg))>0)
        Write(STDOUT_FILENO,mesg.mesg_data,n);
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

