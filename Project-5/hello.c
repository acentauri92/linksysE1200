#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("Dheeraj Reddy");
MODULE_DESCRIPTION("Hello, world module for the E1200 v2 Router");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("1.0");

static int __init helloworld_init(void){
    printk(KERN_INFO "Hello, World!\n");
    return 0;
}

static void __exit helloworld_exit(void)
{
printk(KERN_INFO "Goodbye, world\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);