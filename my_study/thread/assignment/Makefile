# Tên file nhị phân
TARGET = program

# Đường dẫn thư mục
SRC_DIR = src
INC_DIR = include
STATIC_LIB_DIR = static_lib
DYN_LIB_DIR = dym_lib

# Các tệp nguồn và tiêu đề
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Cờ biên dịch
CFLAGS = -I$(INC_DIR) -pthread
LDFLAGS = -L$(STATIC_LIB_DIR) -L$(DYN_LIB_DIR)
LIBS = -linput -lwrite -lread

# Biên dịch chương trình chính
$(TARGET): $(OBJS) $(STATIC_LIB_DIR)/libinput.a $(STATIC_LIB_DIR)/libwrite.a $(STATIC_LIB_DIR)/libread.a $(DYN_LIB_DIR)/libinput.so $(DYN_LIB_DIR)/libwrite.so $(DYN_LIB_DIR)/libread.so
	gcc $(CFLAGS) main.c -o $(TARGET) $(LDFLAGS) $(LIBS) -Wl,-rpath,$(DYN_LIB_DIR)

# Biên dịch thư viện tĩnh
$(STATIC_LIB_DIR)/libinput.a: $(SRC_DIR)/input.o | $(STATIC_LIB_DIR)
	ar rcs $(STATIC_LIB_DIR)/libinput.a $(SRC_DIR)/input.o

$(STATIC_LIB_DIR)/libwrite.a: $(SRC_DIR)/write.o | $(STATIC_LIB_DIR)
	ar rcs $(STATIC_LIB_DIR)/libwrite.a $(SRC_DIR)/write.o

$(STATIC_LIB_DIR)/libread.a: $(SRC_DIR)/read.o | $(STATIC_LIB_DIR)
	ar rcs $(STATIC_LIB_DIR)/libread.a $(SRC_DIR)/read.o

# Biên dịch thư viện động
$(DYN_LIB_DIR)/libinput.so: $(SRC_DIR)/input.o | $(DYN_LIB_DIR)
	gcc -shared -fPIC -o $(DYN_LIB_DIR)/libinput.so $(SRC_DIR)/input.o

$(DYN_LIB_DIR)/libwrite.so: $(SRC_DIR)/write.o | $(DYN_LIB_DIR)
	gcc -shared -fPIC -o $(DYN_LIB_DIR)/libwrite.so $(SRC_DIR)/write.o

$(DYN_LIB_DIR)/libread.so: $(SRC_DIR)/read.o | $(DYN_LIB_DIR)
	gcc -shared -fPIC -o $(DYN_LIB_DIR)/libread.so $(SRC_DIR)/read.o

# Tạo thư mục nếu chưa tồn tại
$(STATIC_LIB_DIR):
	mkdir -p $(STATIC_LIB_DIR)

$(DYN_LIB_DIR):
	mkdir -p $(DYN_LIB_DIR)

# Quy tắc biên dịch tệp .o từ .c
%.o: %.c | $(STATIC_LIB_DIR) $(DYN_LIB_DIR)
	gcc $(CFLAGS) -fPIC -c $< -o $@

# Clean project
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)
	rm -f $(STATIC_LIB_DIR)/*.a
	rm -f $(DYN_LIB_DIR)/*.so
