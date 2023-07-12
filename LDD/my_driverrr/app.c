#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int main()
{
	int fd,n;
	char W_buff[100],R_buff[100];
	fd=open("/dev/device",O_RDWR);
	if(fd==-1)
	{
		printf("Open failed\n");
		exit(0);
	}
	while(1)
	{
		printf("1)write to kernel\n2)read from driver\n3)exit\n");
		scanf("%d",&n);
		if(n==1)
		{
			printf("Enter the data\n");
			scanf("%s",W_buff);
			write(fd,W_buff,sizeof(W_buff));

		}
		else if(n==2)
		{
			printf("data reading ...\n");
			read(fd,R_buff,sizeof(R_buff));
			printf("done\n");
		}
		else if(n==3)
		{
			exit(1);
		}
	}

}
