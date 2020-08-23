#include"unpipc.h"
int main(int argc,char **argv)
{

    struct msqid_ds msgdata;
    int i,msqid;
    for(i=0;i<10;i++)
    {
        msqid = Msgget(IPC_PRIVATE,SVMSG_MODE | IPC_CREAT);
        memset(&msgdata,0,sizeof(struct msqid_ds));
        Msgctl(msqid,IPC_STAT,&msgdata);
        printf("msqid = %d ipc_perm.seq = %d\n",msqid,msgdata.msg_perm.__seq);
    
        Msgctl(msqid,IPC_RMID,NULL);
    }
}
