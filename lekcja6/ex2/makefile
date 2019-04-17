# Main makefile
CC=g++
CFLAGS=-c -Wall

main: main.o dbgPrint.o
	$(CC) obj/main.o obj/dbgPrint.o -o bin/$@

main.o: main.cpp main.h
	$(CC) $(CFLAGS) $< -o obj/$@

dbgPrint.o: dbgPrint.cpp dbgPrint.h
	$(CC) $(CFLAGS) $< -o obj/$@

.PHONY: clean
clean:
	rm -f *.o main
	rm -f obj/*
	rm -f bin/*
