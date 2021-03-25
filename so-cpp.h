#include "parser.h"

int parse_symbol_mapping(char *str, entry_t **entry);
void parse_path(vector *paths, char *str);
int parse_filename(char **filename, char *str);
void print_string_decimal(char *str);
int read_arguments(h_table *table, vector *vector, char **output_file,
			char **input_file, int argc, char **argv);
