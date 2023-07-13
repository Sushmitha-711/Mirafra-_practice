#include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>
 #include<sys/types.h>
 #include<string.h>
 #include<fcntl.h>
 #include<sys/stat.h>

         char write_buf[1024];
         char read_buf[1024];
int main()
{
	 char buf[]="sree embedded";
	 int n,ret,i;
	 char buff[]="Technologies";
	 int fd3,fd2,fd;
	 fd=open("/dev/lseek",O_RDWR);
	 if(fd==-1)
	 {
		 printf("open fails\n");
		 exit(0);
	 }	 
	 for(i=0;i<1024;i++)
	 {
		 write_buf[i]='*';
	 }
	 write(fd,write_buf,sizeof(write_buf));
	 lseek(fd,10,SEEK_SET);
	 write(fd,buf,strlen(buf));
	lseek(fd,100,SEEK_SET);
	write(fd,buff,strlen(buff));
	read(fd,read_buf,1024);
	// write(1,read_buf,40);
	printf("%s\n",read_buf);
	close(fd);
	 return 0;
 }
