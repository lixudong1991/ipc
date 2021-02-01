#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo)
{
	struct passwd *rootpwd;
	printf("in signal handler\n");
	if((rootpwd=getpwnam("root"))==NULL)
		err_sys("getpwnam(root) error");
	printf("call alarm\n");
}

int main()
{
	struct passwd *ptr;
	signal(SIGALRM,my_alarm);
	alarm(1);
	int i=0;
	for(;;){
		if((ptr=getpwnam("lxd"))==NULL)
			err_sys("getpwnam error");
		if(strcmp(ptr->pw_name,"lxd")!=0)
			printf("return value corrupted!,pw_name!=%s\n",ptr->pw_name);
	}
}
