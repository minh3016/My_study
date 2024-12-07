# Tên module
obj-m += my_ioctl_driver.o

# Đường dẫn đến thư mục kernel build
KDIR := /lib/modules/$(shell uname -r)/build

# Đường dẫn đến thư mục hiện tại
PWD := $(shell pwd)

# Đối tượng mặc định (biên dịch module)
all:
	make -C $(KDIR) M=$(PWD) modules

# Dọn dẹp các file biên dịch
clean:
	make -C $(KDIR) M=$(PWD) clean

