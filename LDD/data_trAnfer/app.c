#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{	char write_buf[40];
	char read_buf[40];
	int n,ret;
	char buff[100];
	int fd3,fd2;
	int fd=open("/dev/my_dev",O_RDWR);
	if(fd==-1)
	{
		printf("open is not success\n");
		exit(0);
	}
	while(1)
	{
		printf("enter option 1-write into the kernel \n 2-read from the driver\n 3-exit");
		scanf("%d",&n);
		switch(n)
		{
			case 1 :
				printf("enter the string to write into the driver\n");
				scanf(" %[^\n]s",write_buf);
				printf("data is read successfully\n\n");
				write(fd,write_buf,sizeof(write_buf));
				printf("done\n");	
				break;
			case  2:
				printf("data reading\n");
				read(fd,read_buf,sizeof(read_buf));
				printf("done\n");
				break;
			case  3:
				close(fd);
				exit(0);
		}
	}
}
