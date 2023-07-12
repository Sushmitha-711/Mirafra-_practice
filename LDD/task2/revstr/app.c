#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
char read_buff[100],write_buff[100];
int main()
{
	int n,fd=open("/dev/revstr",O_RDWR);
	if(fd==-1)
	{
		printf("open failled\n");
		return 0;
	}

	printf("ENter any string \n");
	scanf("%99[^\n]s",write_buff);
	write(fd,write_buff,sizeof(write_buff));
	read(fd,read_buff,100);
	printf("%s\n",read_buff);
	close(fd);
}
