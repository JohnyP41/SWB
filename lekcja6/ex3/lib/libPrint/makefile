CC=g++
CFLAGS=-c -Wall

BINDIR=bin
SRCDIR=src
OBJDIR=obj
DSTDIR=..

all: build install

build: $(OBJDIR)/libPrint.o
	ar rvs libPrint.a $<

$(OBJDIR)/libPrint.o: $(SRCDIR)/libPrint.cpp libPrint.h
	$(CC) $(CFLAGS) $< -o $@

install: $(DSTDIR)/libPrint.a 

$(DSTDIR)/libPrint.a: $(OBJDIR)/libPrint.o
	cp $< $@

.PHONY: clean
clean:
	rm -f *.a *.o
	rm -f obj/*
	rm -f bin/*

