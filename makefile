CC = gcc
CFLAGS = -Wall -o

all: run

run: projet
	./projet

projet: main.o lucasLehmerMersenne.o
	$(CC) $(CFLAGS) projet main.o lucasLehmerMersenne.o -lgmp -lm

main.o: main.c lucasLehmerMersenne.h
	$(CC) $(CFLAGS) main.o -c main.c

lucasLehmerMersenne.o: lucasLehmerMersenne.c lucasLehmerMersenne.h
	$(CC) $(CFLAGS) lucasLehmerMersenne.o -c lucasLehmerMersenne.c

clean: rm *.o projet
