cc=gcc
CFLAGS=-std=c11 -Werror -pedantic -Wextra -g -Wall
TARGET=goose
SRCS := $(notdir $(shell find $(SRC_DIR) -maxdepth 1 -name '*.c'))
OBJS := $(SRCS:%.c=%.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o $(TARGET)
