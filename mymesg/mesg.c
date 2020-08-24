#include "mesg.h"

ssize_t mesg_send(int fd,struct mymesg *mptr)
{
    return  write(fd,mptr,MESGHDRSIZE+mptr->mesg_len);
}
ssize_t mesg_recv(int fd,struct mymesg* mptr)
{
    size_t len;
    ssize_t n;
    if((n=Read(fd,mptr,MESGHDRSIZE))==0)
        return 0;
    else if(n!=MESGHDRSIZE)
        err_quit("message header:expected %d,got %d",MESGHDRSIZE,n);
    if((len=mptr->mesg_len)>0)
        if((n=Read(fd,mptr->mesg_data,len))!=len)
            err_quit("message data:expected %d,got %d",len,n);
    return len;
}
void Mesg_send(int fd,struct mymesg *mptr)
{
     mesg_send(fd,mptr);
}    
ssize_t Mesg_recv(int fd,struct mymesg *mptr)
{
    return mesg_recv(fd,mptr);
}    
