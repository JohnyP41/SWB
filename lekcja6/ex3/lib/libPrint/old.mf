#TODO - Add variables here - compiler, flags...
BINDIR:=bin
SRCDIR:=src
OBJDIR:=obj
DSTDIR:=..

all: build install

build: $(OBJDIR)/libPrint.o
	#TODO - FILL ME! Create library

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(BINDIR)
	#TODO - FILL ME! Build .o file.

install: $(DSTDIR)/libPrint.a 

$(DSTDIR)/libPrint.a: $(OBJDIR)/libPrint.o
	#TODO - FILL ME! Copy lib from bin dir to destination directory - ../


clean:
	#TODO - FILL ME! Add removal of .o files and ./bin/*

