CC = gcc
CFLAGS = -pedantic -std=c99 -Wall -Wextra -Werror -D_POSIX_C_SOURCE
debugger: clades-cimicum.o
	$(CC) $(CFLAGS) clades-cimicum.o -o debugger

clades-cimicum.o: clades-cimicum.c
	$(CC) $(CFLAGS) -c clades-cimicum.c

clean:
	rm *.o
