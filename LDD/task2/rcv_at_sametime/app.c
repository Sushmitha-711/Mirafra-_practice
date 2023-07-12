#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{	char write_buf[1024];
	char read_buf[1024];
	int n=3,ret,i=1;
	char buff[100];
	int fd3,fd2;
	int fd=open("/dev/device",O_RDWR);
	if(fd==-1)
	{
		printf("open is not success\n");
		exit(0);
	}
	while(i<=n)
	{


		printf("enter the string to write into the driver\n");
		scanf(" %[^\n]s",write_buf);
//		printf("data is read successfully\n\n");
		write(fd,write_buf,sizeof(write_buf));
		printf("done\n");	
i++;
	}	
	printf("data reading\n");
	read(fd,read_buf,sizeof(read_buf));
	printf("string:%s\n",read_buf);
	close(fd);	



}
