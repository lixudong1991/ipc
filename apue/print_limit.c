#include "apue.h"
#include <limits.h>
int main(int argc,char *argv[])
{
	size_t psize=0;
	char *pat=path_alloc(&psize);
	printf("exec函数的参数最大长度: 	   %ld\n",sysconf(_SC_ARG_MAX));
	printf("可用atexit函数登记的最大函数的个数:%ld\n",sysconf(_SC_ATEXIT_MAX));
	printf("每个实际用户ID的最大进程数:   %ld  %ld\n",_POSIX_CHILD_MAX,sysconf(_SC_CHILD_MAX));
	printf("每秒时钟滴答数:			   %ld\n",sysconf(_SC_CLK_TCK));
	printf("每个进程最大打开的文件的数目:  %ld %ld\n",open_max(),sysconf(_SC_OPEN_MAX));
	printf("每个进程可使用的信号量的最大个数:  %ld\n",sysconf(_SC_SEM_NSEMS_MAX));
	printf("信号量的最大值: 		   %ld\n",sysconf(_SC_SEM_VALUE_MAX));
	printf("每个进程可排队信号的最大个数:      %ld\n",sysconf(_SC_SIGQUEUE_MAX));
	printf("相对路径名的最大长度:		   %ld\n",pathconf(".",_PC_PATH_MAX));
	printf("文件名的最大长度:		   %ld\n",pathconf(".",_PC_NAME_MAX));
	printf("可原子的写入PIPE的最大字节数:	   %ld\n",pathconf(".",_PC_PIPE_BUF));
	printf("是否截断文件名和路径名的长度:      %ld\n",_POSIX_NO_TRUNC);
	printf("posix version %ld\n",sysconf(_SC_VERSION));
	printf("xsi version %ld\n",sysconf(_SC_XOPEN_VERSION));
	printf("路径的最大长度:%ld\n当前目录: %s\n",psize,getcwd(pat,psize));
	printf("int,long,指针和off_t是32位:              %ld\n",sysconf(_SC_V7_ILP32_OFF32));
	printf("int,long,指针类型是32位,off_t至少是64位: %ld\n",sysconf(_SC_V7_ILP32_OFFBIG));
//	printf("int是32位,long,指针,off_t是64位:         %ld\n",sysconf(_SC_V7_LP64_OFF64));
//	printf("int是32位,long,指针和off_t至少是64位:    %ld\n",sysconf(_SC_V7_LP64_OFFBIG))

}
