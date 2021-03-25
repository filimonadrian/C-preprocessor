#include "parser.h"

void print_string_decimal(char *str);
entry_t *parse_symbol_mapping(char *str);
void parse_path(vector *paths, char *str);
int parse_filename(char **filename, char *str);
int read_arguments(h_table *table, vector *vector, char **output_file, char **input_file, int argc, char **argv);
