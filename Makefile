SRC=main.c
CC=gcc
PROG=breakout
LDFLAGS= -lraylib -lm

$(PROG): $(SRC)
	$(CC) $(SRC) -o $(PROG) $(LDFLAGS)