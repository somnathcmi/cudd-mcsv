OBJS = $(SRC)/apply.o $(SRC)/op.o $(SRC)/exist.o $(SRC)/existRename.o mc.o 
CODES = $(SRC)/apply.c $(SRC)/op.c $(SRC)/exist.c $(SRC)/existRename.c 
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
DOTFL = foo_viz.dot
PDF = blib-test.pdf
LCUDD = -lcudd
SRC = ./src
INCLUDE = -I./

first : 
	make -s all

all: $(CODES)
	make -s clean
	$(CC) $(CFLAGS) $(INCLUDE) $(CODES)
	mv *.o $(SRC)/
	make -s blib-test
	make -s message

message :
	echo "========================================================================="
	echo "sample test executable 'blib-test' is created."
	echo "blib-test contain 2-bit counter example with increment by 1 and increment by 2 transation relations."
	echo "sample outputs will be produced after executing the 'blib-test'"
	echo "========================================================================="

blib-test : $(CODES) blib-test.c mc.c
	make -s blib-test.o
	make -s mc.o
	$(CC) $(LFLAGS) blib-test.o $(OBJS) -o blib-test $(LCUDD)

apply.o: apply.c
	$(CC) $(CFLAGS) apply.c

op.o: op.c
	$(CC) $(CFLAGS) op.c

blib-test.o: blib-test.c blib.h
	$(CC) $(CFLAGS) blib-test.c

mc.o: mc.c blib.h
	$(CC) $(CFLAGS) mc.c

clean:
	rm -f $(OBJS) *~ blib-test $(DOTFL) $(PDF) blib-test.o

$(DOTFL): blib-test
	./blib-test

$(PDF): $(DOTFL)
	dot -T pdf $(DOTFL) > $(PDF)
