.PHONY: all clean

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
CFLAGS = -Wall -Werror -pthread

all: $(PROGS)

%: %.c
		$(CC) $(CFLAGS) -o $@ $<
clean:
		rm -f $(PROGS)