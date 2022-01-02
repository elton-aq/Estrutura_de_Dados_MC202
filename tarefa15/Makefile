CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: nuvem

nuvem: nuvem.c nuvem.h
	gcc $(CFLAGS) *.c -o nuvem $(LDFLAGS)

clean:
	rm -f nuvem
