#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
char read_buff[100],write_buff[100];
int main()
{
	int n,fd=open("/dev/chardev",O_RDWR);
	if(fd==-1)
	{
		printf("open failled\n");
		return 0;
	}
	while(1)
	{
		printf("Enter 1)writing\n2)reading\n3)exit\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1:printf("ENter any string \n");
			       scanf("%s",write_buff);
			       write(fd,write_buff,sizeof(write_buff));
			       break;
			case 2:read(fd,read_buff,sizeof(read_buff));
			       printf("%s\n",read_buff);
			       break;
			case 3:exit(0);
		}
	}
	close(fd);
}
