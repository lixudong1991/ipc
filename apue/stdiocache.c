#include "apue.h"
#include <fcntl.h>
void pr_stdio(const char *, FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
int buffer_size(FILE *);
void dump_fl(const char* name,int v)
{
	int val=v;
        if((val=fcntl(val,F_GETFL,0))<0)
                err_sys("fcntl error");
	printf("%s: ",name);
        switch (val & O_ACCMODE) {
        case O_RDONLY:
                printf("read only");
                break;
        case O_WRONLY:
                printf("write only");
                break;
        case O_RDWR:
                printf("read write");
                break;
        default:
                err_dump("unknown access mode");
        }
        if (val & O_APPEND)
        printf(", append");
        if (val & O_NONBLOCK)
        printf(", nonblocking");
        if (val & O_SYNC)
        printf(", synchronous writes");
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
        if (val & O_FSYNC)
        printf(", synchronous writes");
#endif
        putchar('\n');

}

void dumpstdio()
{
	int ifd=fileno(stdin),ofd=fileno(stdout),efd=fileno(stderr);
	FILE *fp;
	printf("stdin:%d,stdout:%d,stderr:%d\n",ifd,ofd,efd);
	dump_fl("stdin",ifd);
	dump_fl("stdout",ofd);
	dump_fl("stderr",efd);	
	fputs("enter any character\n", stdout);
	if (getchar() == EOF)
		err_sys("getchar error");
	fputs("one line to standard error\n", stderr);
	pr_stdio("stdin", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);	
	if ((fp = fopen("/etc/passwd", "r")) == NULL)
		err_sys("fopen error");
	if (getc(fp) == EOF)
		err_sys("getc error");
	pr_stdio("/etc/passwd", fp);
	fclose(fp);
}
int main()
{
	FILE *file;
	char cache[4096]={0},data[4096]={0};
	dumpstdio();
	if((file=fopen("temp.txt","r+"))==NULL)
		err_sys("open file error");
	if(setvbuf(file,cache,_IOFBF,sizeof(cache))!=0)
		err_sys("setvbuf error");
	pr_stdio("temp.txt",file);
	int readsize=fread(data,1,1024,file);
	exit(0);
}

void
pr_stdio(const char *name, FILE *fp)
{
	printf("stream = %s, ", name);
	if (is_unbuffered(fp))
		printf("unbuffered");
	else if (is_linebuffered(fp))
		printf("line buffered");
	else /* if neither of above */
		printf("fully buffered");
	printf(", buffer size = %d\n", buffer_size(fp));
}
/*
 * * The following is nonportable.
 * */
#if defined(_IO_UNBUFFERED)
int
is_unbuffered(FILE *fp)
{
	return(fp->_flags & _IO_UNBUFFERED);
}
int
is_linebuffered(FILE *fp)
{
	return(fp->_flags & _IO_LINE_BUF);
}
int
buffer_size(FILE *fp)
{
	return(fp->_IO_buf_end - fp->_IO_buf_base);
}
#elif defined(__SNBF)
int
is_unbuffered(FILE *fp)
{
	return(fp->_flags & __SNBF);
}
int
is_linebuffered(FILE *fp)
{
	return(fp->_flags & __SLBF);
}
int
buffer_size(FILE *fp)
{
	return(fp->_bf._size);
}
#elif defined(_IONBF)
#ifdef _LP64
#define _flag __pad[4]
#define _ptr __pad[1]
#define _base __pad[2]
#endif
int
is_unbuffered(FILE *fp)
{
	return(fp->_flag & _IONBF);
}
int
is_linebuffered(FILE *fp)
{
	return(fp->_flag & _IOLBF);
}
int
buffer_size(FILE *fp)
{
#ifdef _LP64
	return(fp->_base - fp->_ptr);
#else
	return(BUFSIZ); /* just a guess */
#endif
}
#else
	#error unknown stdio implementation!
#endif		
