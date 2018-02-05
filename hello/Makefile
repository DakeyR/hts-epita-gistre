CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99

all: hello

hello:printf.o hello.o
	${LINK.c} -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o hello
