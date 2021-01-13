#include "apue.h"
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
char strbuff[MAXLINE];
char*  printfile(const char *name,struct stat *fst)
{
	char *ptr,buf[20];
	int maxlen=70;
	memset(strbuff,0,MAXLINE);
	memset(strbuff,0x20,maxlen);
	if(S_ISREG(fst->st_mode))
		ptr="regular";
	else if(S_ISDIR(fst->st_mode))
		ptr="dir";
	else if(S_ISCHR(fst->st_mode))
		ptr="chardeive";
	else if(S_ISBLK(fst->st_mode))
		ptr="blockdevice";
	else if(S_ISFIFO(fst->st_mode))
		ptr="fifo";
	else if(S_ISLNK(fst->st_mode))
		ptr="symlink";
	else if(S_ISSOCK(fst->st_mode))
		ptr="socket";
	else 
		ptr="unknown";
	//strcpy(strbuff,ptr);
	//snprintf(strbuff+maxlen,MAXLINE-maxlen,"  %d  %d  %ld",fst->st_uid,(int)fst->st_gid,(long)fst->st_size);
	memcpy(strbuff,name,strlen(name));
	memcpy(strbuff+22,ptr,strlen(ptr));
	snprintf(buf,20,"%d",fst->st_uid);
	memcpy(strbuff+36,buf,strlen(buf));
	snprintf(buf,20,"%d",fst->st_gid);
	memcpy(strbuff+44,buf,strlen(buf));
	snprintf(buf,20,"%ld",fst->st_size);
	memcpy(strbuff+52,buf,strlen(buf));
	snprintf(buf,20,"%d",fst->st_nlink);
	memcpy(strbuff+64,buf,strlen(buf));
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
		memset(strbuff,0,MAXLINE);
		memset(strbuff,0x20,70);
		memcpy(strbuff,"name",4);
	        memcpy(strbuff+22,"type",4);
                memcpy(strbuff+36,"uid",3);
       		 memcpy(strbuff+44,"gid",3);
       		 memcpy(strbuff+52,"size",4);
        	memcpy(strbuff+64,"linksum",7);	
		printf("%s\n",strbuff);
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
					printf("%s\n",printfile(dirp->d_name,&filest));
				}
			}
		}
		else
			printf("%s\n",printfile(pat,&filest));			
	}
	free(pat);
	close(dirfd);	
	closedir(dp);
	exit(0);
}
