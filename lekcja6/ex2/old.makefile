# Main makefile
CC=g++
CFLAGS=-c -Wall

main: main.o dbgPrint.o
	$(CC) main.o dbgPrint.o -o main

main.o: main.cpp main.h
	$(CC) $(CFLAGS) main.cpp -o main.o

dbgPrint.o: dbgPrint.cpp dbgPrint.h
	$(CC) $(CFLAGS) dbgPrint.cpp -o dbgPrint.o

.PHONY: clean
clean:
	rm -rf *.o main
