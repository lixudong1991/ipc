#include "apue.h"
#include <pwd.h>
#include <shadow.h>
#include <unistd.h>
int main()
{
	struct passwd *pwd;
	struct spwd *spwd;
	pwd=getpwuid(getuid());
	spwd=getspnam(pwd->pw_name);
	printf("uid = %d,gid = %d name=%s pwd=%s login=%s shell=%s home=%s\n",getuid(),getgid(),pwd->pw_name,spwd->sp_pwdp,getlogin(),pwd->pw_shell,pwd->pw_dir);
	exit(0);
}
