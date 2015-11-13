CC = clang
PROG = pl0
BINDIR = bin
SRCDIR = src
CFLAGS = -I$(SRCDIR) -Wall
INC = lex.h
OBJ = lex.o

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(PROG)

%.o: %.c $(INC)

test: ./$(BINDIR)/pl0
	./$(BINDIR)/pl0 ./test/test.pl0

.PHONY: clean

clean:
	rm -f $(BINDIR)/*.o
