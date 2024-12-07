#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "my_ioctl_driver.h"

#define DEVICE_FILE "/dev/my_ioctl_device"

int main() {
    int fd;
    struct my_data data;
    int arr[5] = {10, 20, 30, 40, 50};

    fd = open(DEVICE_FILE, O_RDWR);
    if (fd < 0) {
        perror("Không mở được thiết bị");
        return EXIT_FAILURE;
    }

    // Cấp phát bộ nhớ trên kernel
    if (ioctl(fd, IOCTL_ALLOCATE_BUFFER) < 0) {
        perror("Không cấp phát được bộ nhớ");
    }

    // Đặt dữ liệu
    data.id = 1;
    strcpy(data.name, "Example Data");
    data.dynamic_array = arr;
    data.array_size = 5;

    if (ioctl(fd, IOCTL_SET_DATA, &data) < 0) {
        perror("Không đặt được dữ liệu");
    } else {
        printf("Dữ liệu đã được đặt\n");
    }

    // Lấy dữ liệu
    if (ioctl(fd, IOCTL_GET_DATA, &data) < 0) {
        perror("Không lấy được dữ liệu");
    } else {
        printf("Dữ liệu nhận được:\n");
        printf("ID: %d\n", data.id);
        printf("Name: %s\n", data.name);
        printf("Array: ");
        for (int i = 0; i < data.array_size; i++) {
            printf("%d ", data.dynamic_array[i]);
        }
        printf("\n");
    }

    // Giải phóng bộ nhớ trên kernel
    if (ioctl(fd, IOCTL_FREE_BUFFER) < 0) {
        perror("Không giải phóng được bộ nhớ");
    }

    close(fd);
    return EXIT_SUCCESS;
}
