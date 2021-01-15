#include "apue.h"
#include <fcntl.h>
#include <dirent.h>
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
			printf("++++++%s\n",path);
		}
		else{
			unlink(path);	
			printf("------%s\n",path);
			sum+=1;
		}
		return sum;
	}
	return 0;
	
}
int main(int argc,char *argv[])
{
	
        if(argc < 2)
		err_quit("usage: myrm <filepath>");
	printf("delete file sum:%d\n",rmfile(argv[1]));
	
}
