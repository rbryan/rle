
CC = clang

CFLAGS = -O0 -Wall 

run: comp.c Makefile
	$(CC) $(CFLAGS) comp.c -o run

