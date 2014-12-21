#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

int num=0;
void *add(void *ar)
{
	int i=0,tmp;
	for(;i<500;i++)
	{
		tmp=num+1;
		num=tmp;
		printf("add+1,result is:%d\n",num);
	}
	return((void *)0);
}
void *sub(void *arg)
{
	int i=0,tmp;
	for(;i<500;i++)
	{
		tmp=num-1;
		num=tmp;
		printf("sub-1,result is:%d\n",num);
	}
	return((void *)0);
}
int main(int argc,char** argv)
{
	pthread_t tid1,tid2;
	int err;
	void *tret;
	err=pthread_create(&tid1,NULL,add,NULL);
	if(err!=0)
	{
	printf("pthread_create error:%s\n",strerror(err));
	exit(-1);
	}
	err=pthread_create(&tid2,NULL,sub,NULL);
	if(err!=0)
	{
		printf("pthread_create error:%s\n",strerror(err));
		exit(-1);
	}
	err=pthread_join(tid1,&tret);
	if(err!=0)
	{
		printf("can not join with thread1:%s\n",strerror(err));
		exit(-1);
	}
	printf("thread 1 exit code %d\n",(int)tret);
	err=pthread_join(tid2,&tret);
	if(err!=0)
	{
		printf("can not join with thread1:%s\n",strerror(err));
		exit(-1);
	}
	printf("thread 2 exit code %d\n",(int)tret);
	return 0;
}
