CC=g++
CFLAGS=-c -Wall
SRCDIR:=src
OBJDIR:=obj
DSTDIR:=..

all: build install

build: $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $^ -o $@

install: $(patsubst $(SRCDIR)/%.cpp,$(DSTDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

$(DSTDIR)/%.o: $(OBJDIR)/%.o
	cp -f $^ $@ 

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(BINDIR) $(OBJDIR)/*.o $(DSTDIR)/*.o

