#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/ktime.h>
#include <hello1.h>

MODULE_AUTHOR("Shvachko Oleg");
MODULE_DESCRIPTION("Hello world");
MODULE_LICENSE("Dual BSD/GPL");

static struct list_head header = LIST_HEAD_INIT(header);


static uint count_hw = 1;
module_param(count_hw, uint, S_IRUGO);
MODULE_PARM_DESC(count_hw, "This parameter is responsible for number of hello world printed");


static int __init initter(void)
{
  return print_hello(count_hw);
}


static void __exit exitter(void)
{
	
}

module_init(initter);
module_exit(exitter);
