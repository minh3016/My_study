#ifndef MY_IOCTL_DRIVER_H
#define MY_IOCTL_DRIVER_H

#include <linux/ioctl.h>

#define IOCTL_MAGIC 'a'

#define IOCTL_GET_DATA _IOR(IOCTL_MAGIC, 1, struct my_data)
#define IOCTL_SET_DATA _IOW(IOCTL_MAGIC, 2, struct my_data)
#define IOCTL_ALLOCATE_BUFFER _IO(IOCTL_MAGIC, 3)
#define IOCTL_FREE_BUFFER _IO(IOCTL_MAGIC, 4)


struct my_data {
    int id;
    char name[100];
    int *dynamic_array;
    int array_size;
};

#endif 
