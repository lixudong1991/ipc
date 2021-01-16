#include "apue.h"
#include <sys/time.h>
#include <time.h>
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
void gettime_us()
{
	struct tm *tmp;
        struct timeval tv;
        char buff[100];
        gettimeofday(&tv,NULL);
        tmp=localtime(&tv.tv_sec);
        if(strftime(buff,sizeof(buff),"%F %A %X",tmp)==0)
                printf("buff length too small\n");
        snprintf(buff+strlen(buff),sizeof(buff)-strlen(buff),":%d:%d",tv.tv_usec/1000,tv.tv_usec%1000);
        printf("time: %s\n",buff);
}	
int main()
{
	gettime_us();
	gettime_ns();
	exit(0);
}
