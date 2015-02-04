CC = g++
CFLAGS = -std=c++11 -Wall -O3
PROG = snuspInterpreter

SRCS = SNUSP.cpp main.cpp
LIBS =

all: $(PROG)

$(PROG):        $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) -c *.cpp
	$(CC) -o $(PROG) *.o $(LIBS)

clear:
	rm -f *.o

clean:
	rm -f $(PROG) *.o

debug:		$(SRCS)
	$(CC) $(CFLAGS) $(LIBS) -c -g *.cpp
	$(CC) -g -o $(PROG) *.o $(LIBS)
