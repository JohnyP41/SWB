# Main makefile
CC:=g++
CFLAGS:=-c -Wall
OBJDIR:=obj
BINDIR:=bin
SRCDIR:=src

LIBBASEDIR:=libs
LIBDIRS:=libswbmath
LIBS:= $(patsubst $(LIBBASEDIR)/$(LIBDIRS)/$(SRCDIR)/%.cpp,$(LIBBASEDIR)/%.o,$(wildcard $(LIBBASEDIR)/$(LIBDIRS)/$(SRCDIR)/*.cpp))
LIBS:= $(LIBS) $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp)) 

all: build install

install: $(BINDIR)/cw7_dom1

build: $(LIBBASEDIR) $(BINDIR)/cw7_dom1 

$(BINDIR)/cw7_dom1: $(LIBS)
	$(CC) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY:$(LIBBASEDIR)
$(LIBBASEDIR):	
	@$(MAKE) -C $(LIBBASEDIR)/$(LIBDIRS)/

.PHONY:clean

clean:
	rm -rf $(BINDIR) $(OBJDIR) 
	@$(foreach path,$(LIBDIRS), $(MAKE) clean -C $(LIBBASEDIR)/$(path) &&) true 

	
