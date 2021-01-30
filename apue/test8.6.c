#include "apue.h"
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	pid_t pid;
	char buff[1024];
	TELL_WAIT();
	if((pid=fork())<0)
		err_sys("fork error");
	else if(pid==0)
	{
		printf("child exit\n");
		TELL_PARENT(getppid());
		exit(0);
	}
	WAIT_CHILD();
	snprintf(buff,1024,"ps -aux | grep %d",pid);
	system(buff);
	waitpid(pid,NULL,0);
	exit(0);
}
	
