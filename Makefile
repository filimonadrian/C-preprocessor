CC=gcc
CFLAGS=-Wall -std=c89

hashtable: hashtable.c
	$(CC) $(CFLAGS) hashtable.c