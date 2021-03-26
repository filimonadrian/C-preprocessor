#define LINE_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "hashtable.h"

int split_line(vector *words, char *buffer);
int split_defines(vector *words, char *buffer);
int compute_defines(h_table *table, vector *words, char *key);
void compute_undef(h_table *table, vector *words);
void compute_if(h_table *table, vector *words, int *condition);
void compute_ifdef(h_table *table, vector *words, int *condition);
void extract_path(char *filename, char *path);
int file_exists(char *include_file);
void create_include_path(char *dir_path, char *include_filename, char *include_path);
void read_line(FILE *file, char *buffer);
void write_line(FILE *file, char *buffer);
int compute_code(h_table *table, vector *words, char *buffer);
void replace_word(char *str, char *result, char *old_word,
			char *new_word, int start_index);
int read_write_headers(h_table *table, vector *paths, char *include_path,
			FILE *output_fp, int *condition);
int compute_include(h_table *table, vector *paths, vector *words,
			char *input_filename, FILE *output_fp, int *condition);
int compute_directives(h_table *table, vector *define_words,
			vector *code_words, vector *paths,
			char *buffer, char *input_filename,
			FILE *output_fp, int *condition);
int process_files(h_table *table, vector *paths, char *input_filename,
			char *output_filename);
void read_line(FILE *file, char *buffer);
void write_line(FILE *file, char *buffer);
