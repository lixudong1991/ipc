#include "apue.h"
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
char strbuff[MAXLINE];
char*  printfile(struct stat *fst)
{
	char *ptr;
	int maxlen=strlen("字符特殊文件");
	memset(strbuff,0,MAXLINE);
	memset(strbuff,0x20,maxlen);
	if(S_ISREG(fst->st_mode))
		ptr="普通文件";
	else if(S_ISDIR(fst->st_mode))
	{
		ptr="目录";
	}
	else if(S_ISCHR(fst->st_mode))
	{
		ptr="字符特殊文件";
	}
	else if(S_ISBLK(fst->st_mode))
	{
		ptr="块特殊文件";
	}
	else if(S_ISFIFO(fst->st_mode))
	{
		ptr="命名管道";
	}
	else if(S_ISLNK(fst->st_mode))
	{
		ptr="文件链接";
	}
	else if(S_ISSOCK(fst->st_mode))
	{
		ptr="套接字";
	}
	else 
	{
		ptr="未知";
	}
	//strcpy(strbuff,ptr);
	snprintf(strbuff+maxlen,MAXLINE-maxlen,"  %d  %d  %ld",fst->st_uid,(int)fst->st_gid,(long)fst->st_size);
	memcpy(strbuff,ptr,strlen(ptr));

	return strbuff;			
}
int main(int argc,char *argv[])
{
	DIR	*dp;
	struct dirent	*dirp;
	size_t psize=0;
	struct stat filest;
	int dirfd;
	char *pat=path_alloc(&psize);
	memset(pat,0,psize);
	memset(&filest,0,sizeof(filest));
	*pat='.';
	if(argc > 1)
		strcpy(pat,argv[1]);
		//err_quit("usage: ls directory_name");
	if(lstat(pat,&filest)==0)
	{
		if(S_ISDIR(filest.st_mode))
		{
			if((dirfd=open(pat,O_RDONLY|O_DIRECTORY))<0)
				err_sys("can't open %s dir",pat);
			if((dp = fdopendir(dirfd)) == NULL)
				err_sys("can't open %s",pat);
			while((dirp = readdir(dp))!=NULL)
			{	
				if(strcmp(dirp->d_name,".")==0||strcmp(dirp->d_name,"..")==0)
					printf("%s\n",dirp->d_name);
				else
				{
					fstatat(dirfd,dirp->d_name,&filest, AT_SYMLINK_NOFOLLOW);
					printf("%s %s\n",dirp->d_name,printfile(&filest));
				}
			}
		}
		else
			printf("%s %s\n",pat,printfile(&filest));			
	}
	free(pat);
	close(dirfd);	
	closedir(dp);
	exit(0);
}
