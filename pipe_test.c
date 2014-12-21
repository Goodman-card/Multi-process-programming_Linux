#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

#define DATA_NUM 1000

#define NUM      100

#define LIMIT    1000


int partion(int num[], int left, int right)
{
	int temp;
	int fd[2];
	int pid = -1;
	int pos = num[left];

	if (right - left > NUM)
	{
		pipe(fd);
		pid = fork();
	}

	if (pid >0)
	{
		close(fd[1]);
		read(fd[0], &left, sizeof(left));
		
		return left;
	}

	while(left < right)
	{
		while(left < right && num[right] >= pos)
		{
			right--;
		}

		temp = num[left];
		num[left] = num[right];
		num[right] = temp;
	
		while(left < right && num[left] <= pos)
		{
			left++;
		}
		temp = num[left];
        num[left] = num[right];
		num[right] = temp;
	}

	if(pid == 0)
	{
		close(fd[0]);
		write(fd[1], &left, sizeof(left));
		exit(0);
	}

	return left;

}

void qu_sort(int num[], int left, int right)
{
	int pos;

	if(left < right)
	{
		pos = partion(num, left, right);
		qu_sort(num, left, pos - 1);
		qu_sort(num, pos + 1, right);
	}
}

int main(void)
{
	unsigned int i;
	int data;
	int fd;
	int *ptr;

	fd = open("data", O_RDWR | O_CREAT, 0777);
	
	if(fd < 0)
	{
		perror("open");
		exit(0);
	}

	srand((unsigned)time(NULL));

	for(i = 0; i < DATA_NUM; i++)
	{
		data = rand() % LIMIT;
		write(fd, &data, sizeof(data));
	}
    
	ptr = mmap(NULL, DATA_NUM*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if((int)ptr == -1)
	{
		perror("mmap");
		exit(0);
	}

	qu_sort(ptr, 0, DATA_NUM-1);
	munmap(ptr, DATA_NUM*sizeof(int));
	lseek(fd, 0, SEEK_SET);

	for(i = 0; i < 200; i++)
	{
		read(fd, &data, sizeof(data));
		printf("%d",data);
	}

	printf("\n");
	close(fd);

	return 0;

}
