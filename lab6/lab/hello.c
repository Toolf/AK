#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>

struct list_item {
	ktime_t time;
	struct list_head list_node;
};

static struct list_head my_list_head = LIST_HEAD_INIT(my_list_head);


MODULE_AUTHOR("Smirnov Nazar");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Count to print 'Hello world'");

static int __init hello_init(void)
{
	uint i = 0;
	struct list_item *tail;

	pr_info("count: %d\n", count);

	if (count == 0 || (count >= 5 && count <= 10)) {
		pr_warn("WARNING\nThe parameter is between 5 and 10 or 0");
	} else if (count > 10) {
		pr_err("ERROR\nThe parameter is greater than 10");
		return -EINVAL; // ellegal input value
	}

	for (i = 0 ; i < count; i++) {
		tail = kmalloc(sizeof(struct list_head), GFP_KERNEL);
		tail->time = ktime_get();
		list_add_tail(&(tail->list_node), &my_list_head);
		pr_info("Hello world\n");
	}

	return 0;
}

static void __exit hello_exit(void)
{
	struct list_item *md, *tmp;

	list_for_each_entry_safe(md, tmp, &my_list_head, list_node) {
		pr_info("time2: %lli\n", md->time);
		list_del(&md->list_node);
		kfree(md);
	}

	BUG_ON(!list_empty(&my_list_head));
}

module_init(hello_init);
module_exit(hello_exit);
