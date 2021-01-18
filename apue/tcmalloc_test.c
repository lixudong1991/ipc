#include "apue.h"
#include <sys/time.h>
#include <time.h>
#define TESTCOUNT 10000000
void gettime_ns()
{
        struct tm *tmp;
        struct timespec ts;
        char buff[100];
        int ms,us,ns;
        clock_gettime(CLOCK_REALTIME,&ts);
        tmp=localtime(&ts.tv_sec);
        if(strftime(buff,sizeof(buff),"%F %A %X",tmp)==0)
                printf("buff length too small\n");
        ms=ts.tv_nsec/1000000;
        us=(ts.tv_nsec%1000000)/1000;
        ns=(ts.tv_nsec%1000000)%1000;
        snprintf(buff+strlen(buff),sizeof(buff)-strlen(buff),":%ld:%ld:%ld",ms,us,ns);
        printf("time: %s\n",buff);

}
int main()
{
	char *ptr;
	gettime_ns();
	for(int i=0;i<TESTCOUNT;i++)
	{
		ptr=malloc(1024*1000);
		if(ptr)
		{
			memset(ptr,0,1024*1000);
			free(ptr);
		}else 
			err_sys("malloc error");

	}
	gettime_ns();
}
