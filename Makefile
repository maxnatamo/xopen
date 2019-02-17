CC = gcc

SRC = server.c client.c
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall

all: options server client

options:
	@echo Build options:
	@echo "CLFAGS	= $(CFLAGS)"
	@echo "CC	= $(CC)"
	@echo

.c.o:
	$(CC) -c $(CFLAGS) $<

xopen: server.o client.o
	$(CC) -o $@ server.o client.o $(CFLAGS)

clean:
	rm -f server client $(OBJ)

install:
	cp -f server /usr/local/bin/xopen
	cp -f client /usr/local/bin/xopen-client

uninstall:
	rm -f /usr/local/bin/xopen
	rm -f /usr/local/bin/xopen-client
