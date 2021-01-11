#include "apue.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
void test3_6()
{
	int fd;
	if((fd=open("test3_6.txt",O_RDWR|O_APPEND))<0)
		err_sys("open error: %s\n",strerror(errno));
	printf("写入%d\n",write(fd,"abcdefg",7));
	lseek(fd,10,SEEK_SET);
	printf("写入%d\n",write(fd,"hijklmn",7));
	close(fd);
}
int main()
{
	test3_6();
	if(lseek(STDIN_FILENO,0,SEEK_CUR)==-1)
		printf("cannot seek\n");
	else
		printf("seek OK\n");
	exit(0);
}
