CC = gcc
FLAGS = -g -Wall -Wextra -std=c99 -I./db
LDFLAGS = -L./db -lDataStructures

SRCS = TcpServerController.c \
TcpConnectionAcceptor.c \
TcpServerDb.c \
TcpConnectionHandler.c \
test_app.c \
TcpConnectionRecord.c \
network_utils.c

OBJS = $(patsubst %.c, build/%.o, $(SRCS))
TARGET = test_app
TCP_CLIENT_TARGET = tcp_client

TEST_DIR = tests
TEST_SRCS = $(TEST_DIR)/test_network_utils.c network_utils.c
TEST_BIN  = build/test_network_utils

all: $(TARGET) $(TCP_CLIENT_TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LDFLAGS)

$(TCP_CLIENT_TARGET): tcp_client.c
	$(CC) $(FLAGS) -o $@ $^

build/%.o: %.c | build
	$(CC) $(FLAGS) -c -o $@ $<

build:
	mkdir -p build



test: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRCS) | build
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -rf build $(TARGET) $(TCP_CLIENT_TARGET)

.PHONY: all clean test
