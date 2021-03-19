#include "so-cpp.h"

/* function to check if string has '/0' */
void print_string_decimal(char *str) {
        int i = 0;

        for (i = 0; i < strlen(str) + 1; i++) {
                printf("%d ", str[i]);
        }
        printf("\n");

        /*
        for (i = 0; i < strlen(entry->key) + 1; i++) {
                printf("%d ", entry->key[i]);
        }

        printf("\n");
        
        for (i = 0; i < strlen(entry->value) + 1; i++) {
                printf("%d ", entry->value[i]);
        }
        */
}

entry_t* parse_symbol_mapping(char *str) {

        size_t key_mapping = 0;
        size_t value_size = 0;
        size_t str_size = strlen(str);
        size_t i = 0;

        entry_t *entry = malloc(sizeof(entry));
        
        for (i = 0; i < str_size; i++) {
                if (str[i] == '=') {
                        /* set flag for mapping */
                        key_mapping = 1;
                        
                        /* copy key in entry and append '\0' */
                        entry->key = malloc((i + 1) * sizeof(char));
                        memset(entry->key, 0, i + 1);
                        strncpy(entry->key, str, i);
                        /* entry->key[i] = '\0'; */
                        
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
                strcpy(entry->key, str);
                entry->key[str_size] = '\0';

                /* and make value an empty char array */
                entry->value = malloc(1 * sizeof(char));
                entry->value[0] = '\0';
        }

        return entry;
}


void parse_path (vector *paths, char *str) {
        insert_string(paths, str);
}

void read_arguments (h_table *table, vector *vector, int argc, char **argv) {
        int i = 0;
        entry_t *entry = NULL;

        /* for (i = 1; i < argc; i++) { */
        while (i < argc) {
                /* printf("%s\n", argv[i]); */

                /* if it's case -D */
                if (strcmp(argv[i], "-D") == 0) {
                        i++;
                        entry = parse_symbol_mapping(argv[i]);
                        /* printf("%s\n", argv[i]); */

                } else if (strncmp(argv[i], "-D", 2) == 0) {
                        
                        entry = parse_symbol_mapping(argv[i] + 2);
                        /* printf("%s\n", argv[i] + 2); */
                        
                } else if (strcmp(argv[i], "-I") == 0) {

                } else if (strncmp(argv[i], "-I", 2) == 0) {

                }
                i++;

                print_string_decimal(entry->value);
                print_string_decimal(entry->key);
        }
}

int main (int argc, char **argv) {
        
        int i = 0;
        entry_t *entry = NULL;
        
        
        vector *paths =  create_vector(10);

        /* read_arguments (table, paths, argc, argv);
        
        h_table *table = create_table(); 
        char *aux = malloc(aux_size * sizeof(char));
        memset(aux, 0, aux_size);
        size_t aux_size = LINE_SIZE;
        */



        insert_string(paths, "11111");
        insert_string(paths, "22222");
        insert_string(paths, "33333");
        insert_string(paths, "44444");
        insert_string(paths, "55555");
        insert_string(paths, "666666");
        insert_string(paths, "777777");
  


        /* 
        print_vector(paths);
        
        printf("key: %s, value: %s\n", entry->key, entry->value); 
        printf("%d, %d\n", paths->size, paths->capacity);
        */

        /*
        h_table *table = create_table();
        insert_entry(table, "name1", "em");
        insert_entry(table, "name2", "russian");
        insert_entry(table, "name3", "pizza asdfasd fasd fasdf ");
        insert_entry(table, "name4", "paste");
        insert_entry(table, "name5", "merc adsfasd fasd fsad sad fdass");
        insert_entry(table, "name6", "bmw asdfasd asd fas d fs");
        insert_entry(table, "name7", "audi");
        insert_entry(table, "name7", "audix7");
        insert_entry(table, "name8", "pandemie asdfas dasf asd as f");
        insert_entry(table, "name9", "uliuuu");
        print_table(table);

        delete_table(table); 
        */
        delete_vector(paths);


        return 0;
}

