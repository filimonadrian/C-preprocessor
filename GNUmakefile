CC = gcc
CFLAGS = -g -Wall -std=c89
FILES = hashtable.c so-cpp.c vector.c parser.c
OBJECTS = hashtable.o so-cpp.o vector.o parser.o

build: $(OBJECTS)
	$(CC) -o so-cpp $(OBJECTS) $(CFLAGS)

so-cpp.o: so-cpp.c
	$(CC) -c $^ -o $@ $(CFLAGS)

hashtable.o: hashtable.c
	$(CC) -c $^ -o $@ $(CFLAGS)

vector.o: vector.c
	$(CC) -c $^ -o $@ $(CFLAGS)

parser.o: parser.c
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	rm -f so-cpp *.o
