CFLAGS = -std=gnu99 -Wall -Wextra -O0 -D_BSD_SOURCE

CC = gcc

CFLAGS += -g
LDFLAGS += -g
LDLIBS =

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

TARGETS = memdbg

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) -o $(TARGETS) $(OBJS)

$(OBJS): %.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS) *.o *.d

