#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
#include<error.h>
char read_buff[100],write_buff[100];
int main()
{
	int n;
	int fd=open("/dev/size",O_RDWR);
	if(fd==-1)
	{
		printf("open failled\n");
		return 0;
	}

	printf("ENter any string \n");
	scanf("%99[^\n]s",write_buff);
	write(fd,write_buff,sizeof(write_buff));
	if((read(fd,read_buff,sizeof(read_buff)))<0)
	{
		perror("Failed to read\n");
			return -1;
	}
	printf("%s\n",read_buff);
	close(fd);
}
