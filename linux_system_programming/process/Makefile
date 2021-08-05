.PHONY: all clean

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
CFLAGS = -Wall -pthread

all: $(PROGS)

%: %.c
		$(CC) -g $(CFLAGS) -o $@ $<
clean:
		rm -f $(PROGS)