CC=gcc
CFLAGS=-Wall -std=c89
FILES= hashtable.c so-cpp.c

so-cpp: $(FILES)
	$(CC) -o so-cpp $(FILES) $(CFLAGS)

clean:
	rm -rf so-cpp a.out