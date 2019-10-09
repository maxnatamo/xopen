CC = gcc

SRC = server.c client.c
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall

PREFIX ?= /usr/local

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
	install -Dm755 server $(DESTDIR)$(PREFIX)/bin/xopen
	install -Dm755 client $(DESTDIR)$(PREFIX)/bin/xopen-client

uninstall:
	rm -f $(PREFIX)/bin/xopen
	rm -f $(PREFIX)/bin/xopen-client
