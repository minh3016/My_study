#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include "my_ioctl_driver.h"

#define DEVICE_NAME "my_ioctl_device"
#define CLASS_NAME "my_ioctl_class"

// Các biến toàn cục
static int major;
static struct class* ioctl_class = NULL;
static struct device* ioctl_device = NULL;

static struct my_data device_data;  // Lưu trữ dữ liệu của thiết bị

// Hàm `ioctl` để xử lý các lệnh
static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    struct my_data user_data;
    int *temp_array;

    switch (cmd) {
        case IOCTL_GET_DATA:
            if (copy_to_user((struct my_data*)arg, &device_data, sizeof(device_data))) {
                return -EFAULT;
            }
            printk(KERN_INFO "GET_DATA: Đã gửi dữ liệu tới user-space\n");
            break;

        case IOCTL_SET_DATA:
            if (copy_from_user(&user_data, (struct my_data*)arg, sizeof(user_data))) {
                return -EFAULT;
            }

            // Giải phóng mảng cũ nếu cần
            kfree(device_data.dynamic_array);

            // Cấp phát mảng mới
            device_data.array_size = user_data.array_size;
            device_data.dynamic_array = kmalloc(device_data.array_size * sizeof(int), GFP_KERNEL);
            if (!device_data.dynamic_array) {
                return -ENOMEM;
            }

            // Sao chép dữ liệu từ user-space
            if (copy_from_user(device_data.dynamic_array, user_data.dynamic_array, device_data.array_size * sizeof(int))) {
                kfree(device_data.dynamic_array);
                return -EFAULT;
            }
            strncpy(device_data.name, user_data.name, sizeof(device_data.name));
            device_data.id = user_data.id;

            printk(KERN_INFO "SET_DATA: Đã nhận dữ liệu từ user-space\n");
            break;

        case IOCTL_ALLOCATE_BUFFER:
            if (device_data.dynamic_array) {
                printk(KERN_WARNING "BUFFER đã tồn tại\n");
                return -EEXIST;
            }
            device_data.dynamic_array = kmalloc(100 * sizeof(int), GFP_KERNEL);
            if (!device_data.dynamic_array) {
                return -ENOMEM;
            }
            device_data.array_size = 100;
            printk(KERN_INFO "ALLOCATE_BUFFER: Đã cấp phát bộ nhớ\n");
            break;

        case IOCTL_FREE_BUFFER:
            kfree(device_data.dynamic_array);
            device_data.dynamic_array = NULL;
            device_data.array_size = 0;
            printk(KERN_INFO "FREE_BUFFER: Đã giải phóng bộ nhớ\n");
            break;

        default:
            return -ENOTTY;
    }

    return 0;
}

// Cấu trúc file operations
static struct file_operations fops = {
    .unlocked_ioctl = device_ioctl,
};

// Khởi tạo module
static int __init ioctl_module_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "Không thể đăng ký thiết bị\n");
        return major;
    }

   ioctl_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(ioctl_class)) {
        unregister_chrdev(major, DEVICE_NAME);
        printk(KERN_ALERT "Không thể đăng ký lớp thiết bị\n");
        return PTR_ERR(ioctl_class);
    }

    ioctl_device = device_create(ioctl_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    if (IS_ERR(my_ioctl_device)) {
        class_destroy(my_ioctl_class);
        unregister_chrdev(major, DEVICE_NAME);
        printk(KERN_ALERT "Không thể tạo thiết bị\n");
        return PTR_ERR(ioctl_device);
    }

    printk(KERN_INFO "Device được tạo với major number %d\n", major);
    return 0;
}

// Thoát module
static void __exit ioctl_module_exit(void) {
    device_destroy(ioctl_class, MKDEV(major, 0));
    class_unregister(ioctl_class);
    class_destroy(ioctl_class);
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Đã xóa device\n");
}

module_init(ioctl_module_init);
module_exit(ioctl_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("My driver ioctl");
MODULE_AUTHOR("Minh");
