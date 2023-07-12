#include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>
 #include<sys/types.h>
 #include<string.h>
 #include<fcntl.h>
 #include<sys/stat.h>
 int main()
 {       char write_buf[40];
         char read_buf[40];
	 char buf[40];
	 int n,ret,n1;
	 char buff[100];
	 int fd3,fd2,fd;
	 fd=open("/dev/my_dev1",O_RDWR);

	 if(fd==-1)
	 {
		 printf("open fails\n");
		 exit(0);
	 }	 
	 printf("enter the string to write into the driver\n");
	 scanf(" %[^\n]s",write_buf);
	 printf("data is read successfully\n\n");
	 write(fd,write_buf,sizeof(write_buf));
	 printf("done\n");	
	 lseek(fd,8,SEEK_SET);
	 n=read(fd,read_buf,20);

	// write(1,read_buf,40);
	printf("%s\n",read_buf);
	close(fd);
	 return 0;
 }
