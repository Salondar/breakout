SRC=main.c
CC=gcc
PROG=breakout
CFLAGS = -g
LDFLAGS= -lraylib -lm

$(PROG): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(PROG) $(LDFLAGS)