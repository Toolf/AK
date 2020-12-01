#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>

#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>

#include <hello1.h>

struct list_item {
	ktime_t time;
	ktime_t time_finish;
	struct list_head list_node;
};

static struct list_head my_list_head = LIST_HEAD_INIT(my_list_head);

MODULE_AUTHOR("Smirnov Nazar");
MODULE_DESCRIPTION("Hello1 lib");
MODULE_LICENSE("Dual BSD/GPL");


static void print_hello(uint n)
{
	uint i = 0;
	struct list_item *tail;

	for (i = 0; i < n; i++) {
		tail = kmalloc(sizeof(struct list_head), GFP_KERNEL);
		tail->time = ktime_get();
		pr_info("Hello world\n");
		tail->time_finish = ktime_get();
		list_add_tail(&(tail->list_node), &my_list_head);
	}
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("Hello1 hi");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct list_item *md, *tmp;

	list_for_each_entry_safe(md, tmp, &my_list_head, list_node) {
		pr_info("deltatime: %lld\n", md->time_finish - md->time);
		list_del(&md->list_node);
		kfree(md);
	}

	BUG_ON(!list_empty(&my_list_head));
}

module_init(hello1_init);
module_exit(hello1_exit);
