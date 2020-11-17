#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <hello1.h>

MODULE_AUTHOR("Smirnov Nazar");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint count = 1;
module_param(count, uint, 0);
MODULE_PARM_DESC(count, "Count to print 'Hello world'");

static int __init hello_init(void)
{
	pr_info("count: %d\n", count);

	if (count == 0 || (count >= 5 && count <= 10)){
		pr_warning("WARNING\nThe parameter is between 5 and 10 or 0");
	} else if (count > 10){
		pr_err("ERROR\nThe parameter is greater than 10");
		return -EINVAL;
	} 

	print_hello(count);
	return 0;
}

static void __exit hello_exit(void)
{
}

module_init(hello_init);
module_exit(hello_exit);
