#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 10000

typedef struct entry_t {
        char *key;
        char *value;
        struct entry_t *next;
} entry_t;

typedef struct h_table {
        entry_t **entries;
} h_table;

unsigned int hash (char *key);
h_table *create_table();
entry_t *create_pair(char *key, char *value);
void insert_pair(h_table *table, char *key, char *value);
void insert_entry (h_table *table, entry_t *entry);
char *get_entry(h_table *table, char *key);
void delete_entry(h_table* table, char *key);
void delete_table(h_table* table);
void print_table(h_table *table);