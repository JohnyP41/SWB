# Main makefile
CC:=g++
CFLAGS:=-c -Wall
OBJDIR:=obj
BINDIR:=bin
SRCDIR:=src
OUTDIR:=out

LIBBASEDIR:=lib
# Thanks to the structure of this makefile, we just need to add lib names in the line below; All the rest will be handled by subsequent makefiles and scripts.
LIBDIRS:=libPrint
LIBS:= $(addprefix $(LIBBASEDIR)/, $(LIBDIRS))
LIBS:= $(addsuffix .a, $(LIBS))

all: build install

install: $(OUTDIR)/main

$(OUTDIR)/main: |$(OUTDIR)
	# TODO - FILL ME! Normally you would copy out the executable and resources to destination folder. For exercise sake, copy it out to out dir - remember about checking if it exists.

build: $(BINDIR)/main

$(BINDIR)/main: $(OBJDIR)/main.o $(LIBS)
	$(CC) $^ -o $@

#Before creating any objects (| - order-only prequisities - items on the right of | will be checked before items on the left), be sure that dirs are created.
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(LIBBASEDIR)/%.a:	
	@$(MAKE) -C $(LIBBASEDIR)/$*/

.PHONY:clean

clean:
	# TODO - FILL ME! Add removal of object files and binaries. 
#Run clean for every makefile in subdirectories. && is needed to interpret multiple commands in one line, true - to end the command with "&& true".
	@$(foreach path,$(LIBDIRS), $(MAKE) clean -C $(LIBBASEDIR)/$(path) &&) true 

	
