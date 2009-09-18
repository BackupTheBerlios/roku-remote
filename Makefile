.SUFFIXES :
PROJNAME := simple-verlet
DISTEXTRA := LICENCE README
OBJDIR := obj
BINDIR := bin
SRCDIR := src
INCDIR := include

LDFLAGS := -lX11 -lXtst
CFLAGS := -pedantic -Wall -g -I$(INCDIR) -O2 -std=c99
CXXFLAGS := $(CFLAGS)
CC := gcc -c $(CFLAGS)
LD := gcc $(LDFLAGS)
FLEX := flex

BINS := roku
rokuOBJS := socket command irman

.PHONY: all
all : $(BINS)

.PHONY : clean
clean :
	@echo "  RMDIR      $(OBJDIR)"
	@rm -rf $(OBJDIR)
	@echo "  RMDIR      $(BINDIR)"
	@rm -rf $(BINDIR)

.PHONY : help
help :
	@echo "Binaries:"
	@echo "  $(BINS)"
	@echo
	@echo "Other targets:"
	@echo "  help - Prints this help message"
	@echo "  clean - Removes all generated files"
	@echo "  $(OBJDIR)/file.o - Build a single object"
	@echo "  info - Prints a list of variables"

.PHONY : info
info :
	@echo "CC	- '$(CC)'"
	@echo "LD	- '$(LD)'"
	@echo "CFLAGS	- '$(CFLAGS)'"
	@echo "LDFLAGS	- '$(LDFLAGS)'"

.PHONY : dist
dist :
	@echo "  DIST      $(PROJNAME).tar.gz"
	@mkdir -- "$(PROJNAME)"
	@cp -Rv -- $(SRCDIR) $(INCDIR) $(DISTEXTRA) Makefile "$(PROJNAME)" > /dev/null
	@tar -czf "$(PROJNAME).tar.gz" -- "$(PROJNAME)" > /dev/null
	@rm -Rf -- "$(PROJNAME)" > /dev/null

$(OBJDIR) $(BINDIR) :
	@echo "  MKDIR      $@"
	@mkdir -p $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	@echo "  CC         $@"
	@$(CC) -MMD -MP -o $@ $<

$(SRCDIR)/%.c : $(SRCDIR)/%.l
	@echo "  FLEX       $@"
	@$(FLEX) -o $@ $^

-include $(addprefix $(OBJDIR)/, $(addsuffix .d, $(foreach BIN, $(BINS), $($(BIN)OBJS))))

.SECONDEXPANSION :
$(BINS) : $$(addprefix $(BINDIR)/, $$@)

$(addprefix $(BINDIR)/, $(BINS)) : $$(addprefix $(OBJDIR)/, $$(addsuffix .o, $$($$(notdir $$@)OBJS))) | $(BINDIR)
	@echo "  LD         $@"
	@$(LD) -o $@ $(filter-out $(BINDIR), $^) $(LDFLAGS)
