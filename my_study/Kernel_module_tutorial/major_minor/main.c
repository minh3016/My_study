#include<linux/module.h>
#include<linux/fs.h>

#define DRIVER_AUTHOR "Minh"
#define DRIVER_VERSION "1.0"
#define DRIVER_DESC "major and minor"


struct m_foo_dev
{
    /* data */
    dev_t dev_number;
}my_device;

static int __init major_minor_init(void)
{
    // dynamic allocate
   if(alloc_chrdev_region(&my_device.dev_number, 3, 3, "m-cdev") < 0)
   {
       pr_err("Alloc device number fail\n");
      return -1;
     }

    // static allocate
   //my_device.dev_number = MKDEV(200,1);//major  = 240, minor = 1
  //  if(register_chrdev_region(my_device.dev_number, 1, "m-cdev") < 0)
  //  {
  //      pr_err("Static major and minor number fail\n");
  //      return -1;
   // }
    pr_info("Major number: %d, minor number: %d", MAJOR(my_device.dev_number), MINOR(my_device.dev_number));
    pr_info("Hello major and minor module\n");
    return 0;
}

static void __exit major_minor_exit(void)
{
    unregister_chrdev_region(my_device.dev_number, 1);
    pr_info("Exit major and minor module\n");

}

module_init(major_minor_init);
module_exit(major_minor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);