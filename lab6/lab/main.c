#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/ktime.h>

struct shvachko_list_head {
	struct shvachko_list_head *next;
	ktime_t time;
	ktime_t time1;
};

MODULE_AUTHOR("Shvachko Oleg");
MODULE_DESCRIPTION("Hello world");
MODULE_LICENSE("Dual BSD/GPL");

static struct shvachko_list_head *header;


static uint count_hw = 1;
module_param(count_hw, uint, S_IRUGO);
MODULE_PARM_DESC(count_hw, "This parameter is responsible for number of hello world printed");


static int __init initter(void)
{
  uint i = 0;
  struct shvachko_list_head *tmp1, *tmp2;

  if (count_hw == 0) {
    printk(KERN_WARNING "You cannot enter 0");
  } else if (count_hw >= 5 && count_hw <= 10) {
    printk(KERN_WARNING "You should enter number below 5");
  } else if (count_hw > 10) {
    printk(KERN_ERR "The parameter is greater than 10");
    return -EINVAL;
  }

  header = kmalloc(sizeof(struct shvachko_list_head *), GFP_KERNEL);
  tmp1 = header;
  for (i = 0; i < count_hw; i++) {
    tmp1->next = kmalloc(sizeof(struct shvachko_list_head), GFP_KERNEL);
    tmp1->time = ktime_get();
    pr_info("Hello World!");
    tmp1->time1 = ktime_get();

    tmp2 = tmp1;
    tmp1 = tmp1->next;
    }
    
    if (count_hw != 0) {
      kfree(tmp2->next);
      tmp2->next = NULL;
    }
  printk(KERN_INFO "count: %d\n", count_hw);
  return 0;
}


static void __exit exitter(void)
{
	struct shvachko_list_head *variable;
	while (header != NULL && count_hw != 0) {
	  	variable = header;
	 	pr_info("Time : %lld", variable->time);
	 	header = variable->next;
	 	pr_info("Output time : %lld", variable->time1-variable->time);
	 	kfree(variable);
	}
	if (count_hw == 0) {
		pr_info("Time is 0 because print wasn't used");
	}
	pr_info("");
}

module_init(initter);
module_exit(exitter);