#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init simp_module_init(void) {
    printk(KERN_INFO "Simple kernel module: INIT kernel module\n");
    return 0;
}

static void __exit simp_module_exit(void) {
    printk(KERN_INFO "Simple kernel module: EXIT kernel module\n");
}

module_init(simp_module_init);
module_exit(simp_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Minh");
MODULE_DESCRIPTION("A simple Linux kernel module example.");
MODULE_VERSION("1.0");
