#include<linux/cdev.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>

#define mem_size 1024
 #define SEEK_SET        0       /* seek relative to beginning
  of file */
 #define SEEK_CUR        1       /* seek relative to current f
 ile position */
 #define SEEK_END        2       /* seek relative to end of fi
 le */
 #define SEEK_DATA       3       /* seek to the next data */
 #define SEEK_HOLE       4       /* seek to the next hole */
 #define SEEK_MAX        SEEK_HOLE

char *bu;
dev_t cdev;
struct cdev my_cdev;
uint8_t *kernel_buffer;

static int my_open(struct inode *,struct file *);
static int my_release(struct inode *,struct file *);
static ssize_t my_read(struct file *,char __user *,size_t,loff_t *);
static ssize_t my_write(struct file *,const char __user *,size_t ,loff_t *);
 loff_t my_lseek (struct file *, loff_t, int);


static struct file_operations fops =
{
		.owner        =         THIS_MODULE,
		.open         =         my_open,
		.release      =         my_release,
		.read         =         my_read,
		.write        =         my_write,
		.llseek       =		my_lseek,
};



static int my_open(struct inode *inode,struct file *file)
{
	printk("open successfully\n");
	return 0;
}

static int my_release(struct inode *inode,struct file *file)
{
	printk("released successfully\n");
	return 0;
}


static ssize_t my_read(struct file *filp,char __user *buff,size_t len,loff_t *off)
{
	int i;
	printk("reads successfully\n");
//	printk("data is :%s\n",bu);
	for(i=0;i<len;i++)
	{
		buff[i]=bu[i+(*off)];
	}
	return i;
}


static ssize_t my_write(struct file *filp,const char __user *buff,size_t len,loff_t *off)
{	
	printk("write successfully\n");
	printk("the received data is:%s\n",buff);
	bu=(char *)buff;
	return 0;
}

loff_t my_lseek(struct file *file, loff_t off_set, int whelce)
{
	loff_t new_off_set;
	printk("lseek started\n");
	if(whelce==SEEK_SET)
	{
		new_off_set=off_set;
		
			
	}
	else if(whelce==SEEK_CUR)
	{
		new_off_set=file->f_pos+off_set;
	}
	else
	{
		new_off_set=file->f_inode->i_size+off_set;
	}
	file->f_pos=new_off_set;
	return new_off_set;
}



static int __init chr_driver_start(void)
{

	/*creating MAJOR and MINOR num*/
	if(alloc_chrdev_region(&cdev,0,1,"my_dev1")<0)
	{
		printk(KERN_INFO"major num is not created:\n");
		return -1;
	}
	printk(KERN_INFO"major num:%d  minor num:%d\n",MAJOR(cdev),MINOR(cdev));

	/*creatind cdev structure*/
	cdev_init(&my_cdev,&fops);

	/*adding char device to the system*/
	if((cdev_add(&my_cdev,cdev,1)<0))
	{
		printk(KERN_INFO"can't add the device..........\n");
	}	

	printk(KERN_INFO"device inserted properly\n");
	return 0;
}

static void __exit chr_driver_exit(void)
{
	cdev_del(&my_cdev);
	unregister_chrdev_region(cdev,1);
	printk(KERN_INFO"device removed successfully\n");
}



module_init(chr_driver_start);
module_exit(chr_driver_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("MIRAFRA");
MODULE_DESCRIPTION("Character Device Driver");
MODULE_AUTHOR("MIRAFRA");
MODULE_DESCRIPTION("Character Device Driver");
