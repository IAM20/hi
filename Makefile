# Compiler and compile options.
#

CC = gcc
CFLAGS = -g -Wall

#Macros specifying path for compile.
SRCS := $(wildcard src/*.c)
HEADERS := $(wildcard src/*.h)

OBJS := $(SRCS:.c=.o)

BIN = ./bin/

TARGET = 234tree
$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)$(TARGET) $(OBJS)

#Delete binary 
clean :
	rm $(BIN)$(TARGET) $(OBJS)
