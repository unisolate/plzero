CC = clang
PROG = plzero
SRCDIR = src
OBJDIR = obj
BINDIR = bin
CFLAGS = -Wall

SRC = plzero.c lexer.c parser.c interpreter.c
OBJ = $(SRC:.c=.o)

all: $(PROG)

$(PROG): $(addprefix $(OBJDIR)/, $(OBJ))
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(PROG) $(addprefix $(OBJDIR)/, $(OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(PROG)
	$(BINDIR)/$(PROG) test/test.pl0 > test/test.txt
	diff test/test.txt test/test-std.txt

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/$(PROG)