#ifndef MY_MESG_H
#define MY_MESG_H
#include "../unpipc.h"

#define MAXMESGDATA (PIPE_BUF-2*sizeof(long))
struct mymesg{
    long mesg_len;
    long mesg_type;
    char mesg_data[MAXMESGDATA];
};
#define MESGHDRSIZE (sizeof(struct mymesg)-MAXMESGDATA)
ssize_t mesg_send(int,struct mymesg*);
void    Mesg_send(int,struct mymesg*);
ssize_t mesg_recv(int,struct mymesg*);
ssize_t Mesg_recv(int,struct mymesg*);


#endif
