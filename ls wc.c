#include<unistd.h>
int fd[2];
void run_ls()
{
	dup2(fd[1],1);
	close(fd[0]);
	close(fd[1]);
	execve("/bin/ls",NULL,NULL);
}

void run_wc()
{
	dup2(fd[0],0);
	close(fd[0]);
	close(fd[1]);
	execve("/usr/bin/wc",NULL,NULL);
}

int main()
{
	pipe(fd);          //bulid pipe
	if (fork()==0)     //this is child program
		run_ls();
	else
		run_wc();    //this is parent program
	return 0;
}
