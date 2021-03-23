#define LINE_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "hashtable.h"

void split_line(vector *words, char buffer[]);
void split_defines(vector *words, char buffer[]);
int read_file(h_table *table, char *input_filename, char *output_filename);
void read_line(FILE *file, char *buffer);
void compute_defines(h_table *table, vector *words, char *key);
void replace_word(char *str, char *result, char *old_word, char *new_word, int start_index);
char *compute_code(h_table *table, vector *words, char buffer[]);
void compute_undef(h_table *table, vector *words);
void compute_if(h_table *table, vector *words, int *condition);