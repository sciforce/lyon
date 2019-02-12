ifndef OUT
override OUT = $(shell pwd)
endif
CC=gcc
CFLAGS=-fPIC -O2 -std=c99
TEST_LDFLAGS=$(shell pkg-config --cflags --libs check)

all:		lyon

lyon:		soscascade agc sosfilters

soscascade:	soscascade.c
		$(CC) $(CFLAGS) -c soscascade.c -o $(OUT)/soscascade.o

agc:		agc.c
		$(CC) $(CFLAGS) -c agc.c -o $(OUT)/agc.o

sosfilters:	sosfilters.c
		$(CC) $(CFLAGS) -c sosfilters.c -o $(OUT)/sosfilters.o

lib:		lyon
		$(CC) -shared $(OUT)/agc.o $(OUT)/soscascade.o $(OUT)/sosfilters.o -o $(OUT)/liblyon.so

test:		test.c lyon
		$(CC) $(CFLAGS) test.c $(OUT)/agc.o $(OUT)/soscascade.o $(OUT)/sosfilters.o -o $(OUT)/lyon_test $(TEST_LDFLAGS)
		$(OUT)/lyon_test

clean:
		rm -f $(OUT)/*.o $(OUT)/lyon_test $(OUT)/liblyon.so



