#include "apue.h"
#include <sys/resource.h>
#define doit(name) pr_limits(#name, name)
static void pr_limits(char *, int);
static char *getlimitstr(char *buff,int lim)
{
	switch(lim)
	{
	case RLIMIT_AS:
		strcpy(buff,"进程总的可用的最大空间");
		break;
	case RLIMIT_CORE:
		strcpy(buff,"core文件的最大字节数");
		break;
	case RLIMIT_CPU:
		strcpy(buff,"CPU的最大量值");
		break;
	case RLIMIT_DATA:
		strcpy(buff,"数据段的最大长度");
		break;
	case RLIMIT_FSIZE:
		strcpy(buff,"可以创建文件的最大大小");
		break;
	case RLIMIT_MEMLOCK:
		strcpy(buff,"使用mlock能够锁定在存储空间的最大长度");
		break;
	case RLIMIT_MSGQUEUE:
		strcpy(buff,"进程为POSIX消息队列可分配的最大空间");
		break;
	case RLIMIT_NICE:
		strcpy(buff,"影响调度的优先级的nice值的最大限制");
		break;
	case RLIMIT_NOFILE:
		strcpy(buff,"进程能打开的最多文件数");
		break;
	case RLIMIT_NPROC:
		strcpy(buff,"可拥有的最大子进程数");
		break;
//	case RLIMIT_NPTS:
//		strcpy(buff,"可同时打开的伪终端最大数量");
//		break;
	case RLIMIT_RSS:
		strcpy(buff,"最大驻内存集字节长度");
		break;
//	case RLIMIT_SBSIZE:
//		strcpy(buff,"任一时刻一个用户可占用的套接字缓冲区的最大长度");
//		break;
	case RLIMIT_SIGPENDING:
		strcpy(buff,"进程可排队的信号最大数量");
		break;
	case RLIMIT_STACK:
		strcpy(buff,"栈的最大大小");
		break;
//	case RLIMIT_SWAP:
//		strcpy(buff,"用户可消耗的交换空间最大字节数");
//		break;
	}
	return buff;	
}
int
main(void)
{
#ifdef RLIMIT_AS
	doit(RLIMIT_AS);
#endif
	doit(RLIMIT_CORE);
	doit(RLIMIT_CPU);
	doit(RLIMIT_DATA);
	doit(RLIMIT_FSIZE);
#ifdef RLIMIT_MEMLOCK
	doit(RLIMIT_MEMLOCK);
#endif
#ifdef RLIMIT_MSGQUEUE
	doit(RLIMIT_MSGQUEUE);
#endif
#ifdef RLIMIT_NICE
	doit(RLIMIT_NICE);
#endif
	doit(RLIMIT_NOFILE);
#ifdef RLIMIT_NPROC
	doit(RLIMIT_NPROC);
#endif
#ifdef RLIMIT_NPTS
	doit(RLIMIT_NPTS);
#endif
#ifdef RLIMIT_RSS
	doit(RLIMIT_RSS);
#endif
#ifdef RLIMIT_SBSIZE
	doit(RLIMIT_SBSIZE);
#endif
#ifdef RLIMIT_SIGPENDING
	doit(RLIMIT_SIGPENDING);
#endif
	doit(RLIMIT_STACK);
#ifdef RLIMIT_SWAP
	doit(RLIMIT_SWAP);
#endif
#ifdef RLIMIT_VMEM
	doit(RLIMIT_VMEM);
#endif
	exit(0);
}
static void
pr_limits(char *name, int resource)
{
	struct rlimit limit;
	unsigned long long lim;
	char strbuff[256]={0};
	if (getrlimit(resource, &limit) < 0)
		err_sys("getrlimit error for %s", name);
	printf("%-14s %s: ", name,getlimitstr(strbuff,resource));
	if (limit.rlim_cur == RLIM_INFINITY) {
		printf("(infinite)无限制 ");
	} else {
		lim = limit.rlim_cur;
		printf("%10lld ", lim);
	}
	if (limit.rlim_max == RLIM_INFINITY) {
		printf("(infinite)无限制 ");
	} else {
		lim = limit.rlim_max;
		printf("%10lld", lim);
	}
	putchar((int)'\n');
}
