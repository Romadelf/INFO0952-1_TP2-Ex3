SRCS = crypto.c main.c imageIO.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = crypto

CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean run

clean:
	$(RM) $(OBJS) $(PROG)

run: $(PROG)
	./$(PROG)

crypto.o: crypto.c imageIO.h crypto.h
imageIO.o: imageIO.c imageIO.h
main.o: main.c crypto.h imageIO.h
