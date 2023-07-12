#include<linux/cdev.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
static int my_open(struct inode *, struct file *);
static int my_release(struct inode *, struct file *);
static ssize_t my_write(struct file *, const char __user *, size_t , loff_t *);
static ssize_t my_read(struct file *, char  *, size_t , loff_t *);

char kernel_buffer[1024];
dev_t cdev;
struct cdev my_cdev;
struct class *my_class;
struct file_operations fops =
{
		.owner		=	THIS_MODULE,
		.open		=	my_open,
		.release	=	my_release,
		.write		=	my_write,
		.read		=	my_read,
};
/*static int my_open(struct inode *,struct file*);
static int my_release(struct inode *,struct file *);
static ssize_t my_read(struct file*,char *,size_t ,loff_t *);
static ssize_t my_write(struct file*,const char *,size_t ,loff_t *);*/
static int my_open(struct inode *inode,struct file *file)
{
	printk("done open\n");
	return 0;
}
static int my_release(struct inode *inode,struct file *file)
{
	printk("closed\n");
	return 0;
}
static ssize_t my_read(struct file *file,char *buff,size_t len,loff_t *offset)
{
	copy_to_user(buff,kernel_buffer,sizeof(kernel_buffer));
	printk("done reading\n");
	kernel_buffer[0]='\0';
	return len;
}
static ssize_t my_write(struct file *file,const char *buff,size_t len,loff_t *offset)
{
	copy_from_user(kernel_buffer,buff,sizeof(buff));
	printk("done write\n");
	return len;
}
static int __init start(void)
{
	/*int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, const char *name);
	 */
	if(alloc_chrdev_region(&cdev,0,1,"chardev")<0)
	{
		printk(KERN_INFO"Major number Allocation failed\n");
		return -1;
	}
	/*void  cdev_init(struct cdev *,struct file *)*/
	cdev_init(&my_cdev,&fops);
	/*int cdev_add(struct cdev *,dev_t,unsigned int)*/
	cdev_add(&my_cdev,cdev,1);


	/*struct class *class_create(struct module *owner, const char *name);*/

	my_class=class_create(THIS_MODULE,"chardev");
	/*struct device *device_create(struct class *class, struct device *parent, dev_t dev, void *drvdata, const char *fmt, ...);
	 */
	device_create(my_class,NULL,cdev,NULL,"chardev");
	printk(KERN_INFO,"device inserted successfully\n");
	return 0;
}
static void __exit end(void)
{
	/*void device_destroy(struct class *class, dev_t dev);*/
	device_destroy(my_class,cdev);
	/*void class_destroy(struct class *class);*/
	class_destroy(my_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(cdev,1);
	printk(KERN_INFO"device removed succesfully\n");
}
module_init(start);
module_exit(end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MIRAFRA");
MODULE_DESCRIPTION("character device driver");
