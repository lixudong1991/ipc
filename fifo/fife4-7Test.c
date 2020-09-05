#include "fifo.h"
int main(int argc,char** argv)
{

    int readfifo,dummyfd,flags;
    struct stat statbuf;
    char buff[100]={0};
    memset(&statbuf,0,sizeof(struct stat));
    if((mkfifo(SERV_FIFO,FILE_MODE) < 0)&&(errno != EEXIST))
        err_sys("can't create %s",SERV_FIFO);
    readfifo = Open(SERV_FIFO,O_RDONLY|O_NONBLOCK,0);
    dummyfd = Open(SERV_FIFO,O_WRONLY,0);
    Write(dummyfd,argv[1],strlen(argv[1]));
    if(stat(readfifo, &statbuf)==0)
       printf("st_size: %d\n",statbuf.st_size);
    Read(readfifo,buff,100);
    printf("%s\n",buff);
    Close(dummyfd);
    Close(readfifo);
    Unlink(SERV_FIFO);
}

