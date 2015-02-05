CC = g++
CFLAGS = -std=c++11 -Wall -O3
DFLAGS = -std=c++11 -Wall -g
PROG = snuspInterpreter

SRCS = SNUSP.cpp main.cpp
LIBS =

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
