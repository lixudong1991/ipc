#include "apue.h"
#include <sys/utsname.h>

int main()
{
	struct utsname un;
	char hn[64];
	if(uname(&un)==-1)
		err_sys("uname error");
	printf("sysname:  %s\n",un.sysname);
	printf("nodename: %s\n",un.nodename);
	printf("release:  %s\n",un.release);
	printf("version:  %s\n",un.version);
	printf("machine:  %s\n",un.machine);
	gethostname(hn,sizeof(hn));
	printf("hostname: %s\n",hn);
	exit(0);		
}
