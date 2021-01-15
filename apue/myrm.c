#include "apue.h"
#include <fcntl.h>
#include <dirent.h>
#include <sys/time.h>
char *pathbuff;
int rmfile1()
{
	DIR *dp;
	struct stat filest;
	struct dirent   *dirp;
	int sum=0,len=0;
	if(lstat(pathbuff,&filest)==0)
	{
		if(S_ISDIR(filest.st_mode))
		{
			len=strlen(pathbuff);
			pathbuff[len++]='/';
			pathbuff[len]=0;
			if((dp = opendir(pathbuff)) == NULL)
                                err_sys("can't open %s",pathbuff);
			while((dirp = readdir(dp))!=NULL)
                        {
				if(strcmp(dirp->d_name,".")==0||strcmp(dirp->d_name,"..")==0)
					continue;
				strcpy(pathbuff+len,dirp->d_name);
				sum+=rmfile1();
                        }
			closedir(dp);
			pathbuff[len-1]=0;
			rmdir(pathbuff);
		}
		else{
			unlink(pathbuff);	
			sum+=1;
		}
		return sum;
	}
	return 0;
	
}

int rmfile(const char *path)
{
	DIR *dp;
	struct stat filest;
	struct dirent   *dirp;
	int sum=0;
	if(lstat(path,&filest)==0)
	{
		if(S_ISDIR(filest.st_mode))
		{
			
			if((dp = opendir(path)) == NULL)
                                err_sys("can't open %s",path);
			chdir(path);
			while((dirp = readdir(dp))!=NULL)
                        {
				if(strcmp(dirp->d_name,".")==0||strcmp(dirp->d_name,"..")==0)
					continue;
				sum+=rmfile(dirp->d_name);
                        }
			chdir("..");
			closedir(dp);
			rmdir(path);
		}
		else{
			unlink(path);	
			sum+=1;
		}
		return sum;
	}
	return 0;
	
}
int main(int argc,char *argv[])
{
	
	long long L1,L2;
	struct timeval tv;
        if(argc < 2)
		err_quit("usage: myrm <filepath>");
	size_t psize=0;
	pathbuff=path_alloc(&psize);
	strcpy(pathbuff,argv[1]);
       	gettimeofday(&tv,NULL);
	L1 = tv.tv_sec*1000*1000 + tv.tv_usec; 
	printf("delete file sum:%d\n",rmfile(argv[1]));
//	printf("delete file sum1:%d\n",rmfile1());
	gettimeofday(&tv,NULL);
	L2 = tv.tv_sec*1000*1000+tv.tv_usec;
	printf("use time:%lld us\n",L2-L1);
	free(pathbuff);
}
