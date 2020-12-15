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

	if (count == 0 || (count >= 5 && count <= 10))
		pr_warn("WARNING\nThe parameter is between 5 and 10 or 0");
	BUG_ON(count > 10);

	for (i = 0 ; i < count; i++) 
	{
		//kmalloc вызывающая функция выполняет
		//системный вызов от имени процесса
		tail = kmalloc(sizeof(struct list_item), GFP_KERNEL); 
		if (i == 5)
		    tail = 0; // начебто kmalloc повернув 0
		if(ZERO_OR_NULL_PTR(tail))
			goto error;
		tail->time = ktime_get();
		list_add_tail(&(tail->list_node), &my_list_head);
		pr_info("Hello world\n");
	}

	return 0;

error:
	{
		struct list_item *md, *tmp;
		pr_err("kmalloc out of memory");
		list_for_each_entry_safe(md, tmp, &my_list_head, list_node) {
			list_del(&md->list_node);
			kfree(md);
		}
		BUG(); // hello_init+0xa4/0x1000 e7f001f2
		return -ENOMEM;
	}
	
}

static void __exit hello_exit(void)
{
	struct list_item *md, *tmp;

	list_for_each_entry_safe(md, tmp, &my_list_head, list_node) {
		pr_info("time: %lld\n", md->time);
		list_del(&md->list_node);
		kfree(md);
	}
	BUG_ON(!list_empty(&my_list_head));
}

module_init(hello_init);
module_exit(hello_exit);
