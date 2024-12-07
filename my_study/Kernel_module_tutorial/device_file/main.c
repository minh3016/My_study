#include<linux/module.h>
#include<linux/fs.h>
#include<linux/device.h>

#define DRIVER_AUTHOR "Minh"
#define DRIVER_VERSION "1.0"
#define DRIVER_DESC "device file"

struct m_foo_dev
{
    /* data */
    dev_t dev_number;
    struct class *my_class;
}my_device;

static int __init device_file_init(void)
{
    // dynamic major minor number
    if(alloc_chrdev_region(&my_device.dev_number, 0, 1, "my_dev") < 0)
    {
        pr_err("Allocate dynamic fail\n");
        return -1;
    }
    pr_info("Major = %d Minor = %d\n", MAJOR(my_device.dev_number), MINOR(my_device.dev_number));

    // create struct

    if((my_device.my_class = class_create(THIS_MODULE, "my_class")) == NULL)
    {
        pr_err("Create class fail\n");
        goto rm_device_numb;
    }
    // create device
    if((device_create(my_device.my_class, NULL, my_device.dev_number, NULL, "my_dev_class")) == NULL)
    {
        pr_err("Create device fail\n");
        goto rm_class;
    }

    printk(KERNEL_INFO "Hello, My device file module\n");
    return 0;
rm_class:
    class_destroy(my_device.my_class);
rm_device_numb:
    unregister_chrdev_region(my_device.dev_number, 1);
    return -1;

}
static void __exit device_file_exit(void)
{
    device_destroy(my_device.my_class, my_device.dev_number);
    class_destroy(my_device.my_class);
    unregister_chrdev_region(my_device.dev_number, 1);

    printk("Exit device file module\n");
}
module_init(device_file_init);
module_exit(device_file_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);