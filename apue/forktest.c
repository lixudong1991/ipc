#include "apue.h"
#include <unistd.h>

int globvar=6;
char buf[]="a write to stdout\n";
int main()
{
	int 	var;
	pid_t	pid;
	var=88;
	if(write(STDOUT_FILENO,	buf,sizeof(buf)-1)!=sizeof(buf)-1)
		err_sys("write error");
	printf("before fork,pid=%ld,iobuff=%lld, val=<%s>\n",getpid(),stdout->_IO_buf_base,stdout->_IO_buf_base);

	if((pid=fork())<0)
		err_sys("fork error");
	else if(pid==0){
		globvar++;
		var++;
	}else{
		sleep(2);
	}
	
	printf("pid =%ld, glob=%d,var=%d,iobuff=%lld, val=<%s>\n",(long)getpid(),globvar,var,stdout->_IO_buf_base,stdout->_IO_buf_base);
	exit(0);
}
