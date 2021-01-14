#include "apue.h"
#include <fcntl.h>

int main(int argc,char *argv[])
{
	if(open(argv[1],O_RDWR)<0)
		err_sys("open error");
	if(unlink(argv[1])<0)
		err_sys("unlink error");
	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
}
