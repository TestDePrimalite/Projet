CC = gcc
CFLAGS = -Wall -o

all: run

run: projet
	./projet

projet: main.o lucasLehmerMersenne.o lucasLehmerRiesel.o certificatPratt.o pocklington.o
	$(CC) $(CFLAGS) projet main.o lucasLehmerMersenne.o lucasLehmerRiesel.o certificatPratt.o pocklington.o -lgmp -lm

main.o: main.c lucasLehmerMersenne.h lucasLehmerRiesel.h certificatPratt.h pocklington.h
	$(CC) $(CFLAGS) main.o -c main.c

lucasLehmerMersenne.o: lucasLehmerMersenne.c lucasLehmerMersenne.h
	$(CC) $(CFLAGS) lucasLehmerMersenne.o -c lucasLehmerMersenne.c
	
lucasLehmerRiesel.o: lucasLehmerRiesel.c lucasLehmerRiesel.h
	$(CC) $(CFLAGS) lucasLehmerRiesel.o -c lucasLehmerRiesel.c

certificatPratt.o: certificatPratt.c certificatPratt.h
	$(CC) $(CFLAGS) certificatPratt.o -c certificatPratt.c

pocklington.o: pocklington.c pocklington.h certificatPratt.h
	$(CC) $(CFLAGS) pocklington.o -c pocklington.c

clean:
	rm *.o projet
