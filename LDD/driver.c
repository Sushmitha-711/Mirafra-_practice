#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
static int __init start(void)
{
	printk("start\n");
	return 0;
}
static void __exit end(void)
{
	printk("end\n");
}
module_init(start);
module_exit(end);
