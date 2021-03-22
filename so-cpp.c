#include "so-cpp.h"



entry_t* parse_symbol_mapping(char *str)
{
        size_t key_mapping = 0;
        size_t value_size = 0;
        size_t str_size = strlen(str);
        size_t i = 0;

        entry_t *entry = malloc(sizeof(entry_t));

        for (i = 0; i < str_size; i++) {
                if (str[i] == '=') {
                        /* set flag for mapping */
                        key_mapping = 1;
                        
                        /* copy key in entry and append '\0' */
                        entry->key = malloc((i + 1) * sizeof(char));
                        memset(entry->key, 0, i + 1);
                        memcpy(entry->key, str, i);
                        
                        /* entry->key[i] = '\0';
                         *strncpy(entry->key, str, i);
                         */
                        
                        /* copy value in entry and append '\0' */
                        value_size = str_size - i;
                        entry->value = malloc(value_size * sizeof(char));
                        memset(entry->value, 0, value_size);
                        memcpy(entry->value, str + i + 1, str_size);
                        /* entry->value[value_size - 1] = '\0'; */
                        break;
                }
        }

        /* if the string does not contain '=' means the value is empty */
        if (key_mapping == 0) {
                /* copy in key entire received string */ 
                entry->key = malloc((str_size + 1) * sizeof(char));
                /*
                 *strcpy(entry->key, str);
                 */
                memcpy(entry->key, str, str_size);
                entry->key[str_size] = '\0';

                /* and make value an empty char array */
                entry->value = malloc(sizeof(char));
                entry->value[0] = '\0';
        }

        return entry;
}


void parse_path(vector *paths, char *str)
{
        insert_string(paths, str);
}

void parse_filename(char **filename, char *str)
{
        if (*filename == NULL) {
                *filename = malloc(strlen(str) * sizeof(char));
                memcpy(*filename, str, strlen(str));
        } else {
                fprintf(stderr, "Multiple definitions of file!\n");
        }
}

void read_arguments(h_table *table, vector *paths,
                    char **output_file, char **input_file,
                    int argc, char **argv)
{

        int i = 0;
        entry_t *entry = NULL;

        while (i < argc) {
                /* printf("%s\n", argv[i]); */

                /* if it's case -D */
                if (strcmp(argv[i], "-D") == 0) {
                        i++;
                        entry = parse_symbol_mapping(argv[i]);
                        insert_entry(table, entry);
                        /* printf("%s\n", argv[i]); */

                } else if (strncmp(argv[i], "-D", 2) == 0) {
                        
                        entry = parse_symbol_mapping(argv[i] + 2);
                        insert_entry(table, entry);

                        /* printf("%s\n", argv[i] + 2); */
                } else if (strcmp(argv[i], "-I") == 0) {
                        i++;
                        parse_path(paths, argv[i]);

                } else if (strncmp(argv[i], "-I", 2) == 0) {
                        parse_path(paths, argv[i] + 2);
                
                } else if (strcmp(argv[i], "-o") == 0) {
                        i++;
                        parse_filename(output_file, argv[i]);
                } else if (strncmp(argv[i], "-o", 2) == 0) {
                        parse_filename(output_file, argv[i] + 2);
                } else if (i > 0) {
                        parse_filename(input_file, argv[i]);
                }
                
                i++;

                /*
                 *print_string_decimal(entry->value);
                 *print_string_decimal(entry->key);
                 */
        }
}

int main(int argc, char **argv)
{
        
        int i = 0;
        entry_t *entry = NULL;
        char *output_filename = NULL;
        char *input_filename = NULL;

        vector *paths = create_vector(2);
        vector *words = create_vector(8);
        h_table *table = create_table();
        

        read_arguments(table, paths, &output_filename, &input_filename, argc, argv);

        if (input_filename != NULL) {
                printf("%s\n", input_filename);
        }

        if (output_filename != NULL)
                printf("%s\n", output_filename);


        read_file(table, input_filename, output_filename);

        printf("Tabelul este: \n");
        print_table(table);

        /*
         *

        print_vector(words);
         */

        /*
        print_vector(paths);
        print_table(table);


        printf("%s\n", output_file);
        
        char *aux = malloc(aux_size * sizeof(char));
        memset(aux, 0, aux_size);
        size_t aux_size = LINE_SIZE;
        */



        free(input_filename);
        free(output_filename);
        delete_vector(paths);
        delete_vector(words);
        delete_table(table); 


        return 0;
}

