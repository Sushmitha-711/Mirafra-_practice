#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>

dev_t my_dev_num;
struct cdev my_cdev;
int major,minor;
static int my_open(struct inode *inode,struct file *file);
static int my_release(struct inode *inode,struct file *file);
static ssize_t my_read(struct file *file,char __user *buff,size_t len,loff_t *offset);
static ssize_t my_write(struct file *file,const char *buff,size_t len,loff_t *offset);

static struct file_operations fops =
{
	.owner        =         THIS_MODULE,
	.open         =        	my_open,
	.release      =         my_release,
	.read         =         my_read,
	.write        =         my_write,
};

static int my_open(struct inode *inode,struct file *file)
{
	printk("Opened successfully\n");
	return 0;
}
static int my_release(struct inode *inode,struct file *file)
{
	printk("Closed successfully\n");
	return 0;
}
static ssize_t my_write(struct file *file,const char __user *buff,size_t len,loff_t *offset)
{
	printk("wrote successfully\n");
	printk("THE DATA IS:%s\n",buff);
	return 0;
}
static ssize_t my_read(struct file *file,char __user *buff,size_t len,loff_t *offset)
{
	printk("read successfully\n");
	printk("The Data is:%s\n",buff);
	return 0;
}
static int __init my_init(void)
{
	/*int register_chrdev_region(dev_t first, unsigned int count, const char *name);*/
	int ret;
	ret=register_chrdev_region(240,1,"my_device");
	if(ret<0)
	{
		printk(KERN_INFO"failed to creat device number\n");
		return ret;
	}
	my_dev_num=MKDEV(240,0);
	major=MAJOR(my_dev_num);
	minor=MINOR(my_dev_num);
	printk("major num:%d\tninor num:%d\n",major,minor);
	/*void cdev_init(struct cdev *cdev, const struct file_operations *fops);*/
	cdev_init(&my_cdev,&fops);
	/*int cdev_add(struct cdev *cdev, dev_t dev, unsigned int count);*/
	if(cdev_add(&my_cdev,my_dev_num,1)<0)
	{
		printk("Failed to add the device to the system\n");
		return 0;
	}
return 0;
}
static void __exit my_exit(void)
{
	/*void cdev_del(struct cdev *cdev);*/
	cdev_del(&my_cdev);
	/*void unregister_chrdev_region(dev_t first, unsigned int count);*/
	unregister_chrdev_region(240,1);
	printk(KERN_INFO"device removed successfully\n");
}
module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MIRAFRA");
MODULE_DESCRIPTION("Character Device Driver");

