#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/bug.h>

MODULE_AUTHOR("Naumchuk Olexandr");
MODULE_DESCRIPTION("Laboratory work 6");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int param = 1;

module_param(param, uint, S_IRUGO);

MODULE_PARM_DESC(param, "Num of 'Hello, World!'will be printed");

struct event_list {
    struct list_head list;
    ktime_t event_time;
};

static struct list_head event_list_head;

static LIST_HEAD(event_list_head);

void new_event(void);

static int __init hello_init(void)
{
    if (param == 0 || (param >= 5 && param <= 10)) {
        printk(KERN_WARNING "Parameter is 0 or between 5 and 10");  
    }
    BUG_ON(param > 10);
//
//    if (param > 10) {
//        printk(KERN_ERR "Parameter is too large");
//        return -EINVAL;
//    }
    int i;
    for (i = 0; i < param; i++) {
        printk(KERN_EMERG "Hello, World!\n");
        new_event();
    }
  return 0;
}

static void __exit hello_exit(void) {
  struct event_list *md, *tmp;
  list_for_each_entry_safe(md, tmp, &event_list_head, list) {
    printk(KERN_EMERG "Time: %lld\n", md->event_time);
    list_del(&md->list);
    kfree(md);
  }
}

void new_event(void) {
    struct event_list *element = NULL;
    element = NULL;
    element->event_time = ktime_get();
    list_add_tail(&element->list, &event_list_head);
}

module_init(hello_init);
module_exit(hello_exit);
