CC=gcc
CFLAGS=-fPIC -O2
TEST_LDFLAGS=$(shell pkg-config --cflags --libs check)

all:		lyon

lyon:		soscascade agc sosfilters

soscascade:	soscascade.c
		$(CC) $(CFLAGS) -c soscascade.c

agc:		agc.c
		$(CC) $(CFLAGS) -c agc.c

sosfilters:	sosfilters.c
		$(CC) $(CFLAGS) -c sosfilters.c

lib:		lyon
		$(CC) -shared agc.o soscascade.o sosfilters.o -o liblyon.so

test:		test.c lyon
		$(CC) $(CFLAGS) test.c agc.o soscascade.o sosfilters.o -o lyon_test $(TEST_LDFLAGS)
		./lyon_test

clean:
		rm -f *.o lyon_test liblyon.so



