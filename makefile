CC = gcc
CFLAGS = -pedantic -std=c99 -Wall -Wextra -Werror -D_POSIX_C_SOURCE
debugger: clades-cimicum.o injector.o
	$(CC) $(CFLAGS) clades-cimicum.o injector.o -o debugger

clades-cimicum.o: clades-cimicum.c
	$(CC) $(CFLAGS) -c clades-cimicum.c

injector.o: injector.c
	$(CC) $(CFLAGS) -c injector.c

captcha: captcha.c
	cc captcha.c -o captcha
clean:
	rm *.o
