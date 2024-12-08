CC = /home/minh/Desktop/Working_space/IPC_CAM/mips-gcc472-glibc216-64bit/bin/mips-linux-uclibc-gnu-gcc
CFLAGS += -I /home/minh/Desktop/Working_space/IPC_CAM/mips-gcc472-glibc216-64bit/lib/gcc/mips-linux-gnu/4.7.2/uclibc -Iinc -pthread
SRC = src/ipc_message_queue.c src/ipc_shared_memory.c src/ipc_pipe.c
OBJ = $(SRC:.c=.o)

all: main

main: main.c $(OBJ)
	$(CC) -o main main.c $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ) main
