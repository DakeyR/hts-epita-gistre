CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -g

all: hello

hello:printf.o hello.o aux.o
	${LINK.c} -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o hello
