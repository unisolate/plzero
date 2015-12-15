# TODO
CC = clang
PROG = plzero
SRCDIR = src
OBJDIR = obj
BINDIR = bin
CFLAGS = -Wall

SRC = $(SRCDIR)/plzero.c $(SRCDIR)/lexer.c $(SRCDIR)/parser.c $(SRCDIR)/interpreter.c
OBJ = $(SRC:.c=.o)

all: $(PROG)

$(PROG): $(OBJ)
	@mkdir -p ${BINDIR}
	$(CC) $(CFLAGS) -o $(BINDIR)/$(PROG) $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p ${OBJDIR}
	$(CC) -c -o $@ $<

test: plzero
	$(BINDIR)/$(PROG) test/test.pl0 > test/test.out
	diff test/test.out test/test-std.out

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o