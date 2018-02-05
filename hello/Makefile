CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -g

all: hello

hello:lookup.o hello.o aux.o gnu_hash.o
	${LINK.c} -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o hello
