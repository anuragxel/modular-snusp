CC = g++
CFLAGS = -std=c++11 -Wall -O3
DFLAGS = -std=c++11 -Wall -g
PROG = snusp

SRCS = SNUSP.cpp main.cpp
LIBS =
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

all: $(PROG)

$(PROG):        $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) -c $(SRCS)
	$(CC) -o $(PROG) *.o $(LIBS)

clear:
	rm -f *.o

clean:
	rm -f $(PROG) *.o

debug:		$(SRCS)
	$(CC) $(DFLAGS) $(LIBS) -c $(SRCS)
	$(CC) -g -o $(PROG) *.o $(LIBS)

static:		$(SRCS)
	$(CC) $(DFLAGS) $(LIBS) -static -c $(SRCS)
	$(CC) -static -g -o $(PROG) *.o $(LIBS)

install:	$(PROG)
	@echo "Installing program to $(DESTDIR)$(BINDIR) ..."
	@mkdir -p $(DESTDIR)$(BINDIR)
	@install -pm0755 $(PROG) $(DESTDIR)$(BINDIR)/$(TARGET) || \
		echo "Failed. Try "make PREFIX=~ install" ?"
