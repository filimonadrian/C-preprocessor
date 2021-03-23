#include "parser.h"

void split_line(vector *words, char buffer[])
{
        char* token = strtok(buffer, "\n\t []{}<>=-*+/\%!&|^.,:;()."); 
        while (token != NULL) { 
                /*
                printf("%s\n", token);
                */
                if (strcmp(token, "\n") != 0)
                        insert_string(words, token);

                token = strtok(NULL, "\n\t []{}<>=-*+/\%!&|^.,:;()."); 

        }
        /*
        insert_string(words, "\n");
        */
}

void split_defines(vector *words, char buffer[])
{
        char* token = strtok(buffer, "\n\t \\"); 

        while (token != NULL) { 
                /*
                printf("%s\n", token);
                */
                insert_string(words, token);
                token = strtok(NULL, "\n\t  \\"); 
        }
        /*
        */
}

void compute_defines(h_table *table, vector *words)
{       
        char aux[LINE_SIZE];
        int aux_size = 0;
        int i = 0;
        
        memset(aux, 0, LINE_SIZE);

        if (words->size < 3) {
                return;
        }

        if (words->size == 3) {
                insert_pair(table, words->arr[1], words->arr[2]);
                return;
        }

        for (i = 2; i < words->size; i++) {
                char *word = get_element(words, i);
                char *value = NULL;
                
                if (word[0] == '(') {
                        value = get_value(table, word + 1);
                        aux[aux_size] = '(';
                        aux_size++;
                } else {
                        value = get_value(table, word);
                }

                if (value == NULL) {
                        memcpy(aux + aux_size, word , strlen(word));
                        aux_size += strlen(word);
                } else {
                        memcpy(aux + aux_size, value, strlen(value));
                        aux_size += strlen(value);
                        /*
                        printf("Valoarea este:  %s\n", value);
                        */
                }
                if (i < words->size - 1) {
                        aux[aux_size] = ' ';
                        aux_size++;
                }
        }

        insert_pair(table, get_element(words, 1), aux);
}

void replace_word(char *str, char *result, char *old_word, char *new_word, int start_index)
{
        int new_word_size = strlen(new_word);
        int old_word_size = strlen(old_word);
        int result_size = strlen(str) + strlen(new_word) - strlen(old_word);
        
        /*
        char *result;
        result = malloc(strlen(str) + strlen(new_word) - strlen(old_word));
        return result;
        */
        
        memset(result, 0, result_size);
        memcpy(result, str, start_index + 1);
        memcpy(result + start_index + 1, new_word, new_word_size);
        memcpy(result + start_index + 1 + new_word_size,
                str + start_index + old_word_size + 1, 
                strlen(str) - start_index + old_word_size);
}

char *compute_code(h_table *table, vector *words, char buffer[])
{
        int i = 0;
        int size_counter = 0;
        char result[LINE_SIZE];
        memset(result, 0, LINE_SIZE);

        for (i = 0; i < words->size; i++) {
                char *key = get_element(words, i);
                
                if (strncmp(key, "//", 2) == 0) {
                        break;
                }
                /*
                if (key[0] == '"') {
                        while (i < words->size) {
                                if (key[strlen(key) - 1] == '"')
                                        break;
                                i++;
                        }
                }
                */

                char *value = get_value(table, key);
                if (value != NULL) {
                        char *aux = strstr(buffer, key);
                        if (aux)
                                size_counter = aux - buffer - 1;
                        replace_word(buffer, result, key, value, size_counter);
                        memcpy(buffer, result, LINE_SIZE);
                }
        }

        /*
        printf("%s", buffer);
        */
        return buffer;

}

int read_file(h_table *table, char *input_filename, char *output_filename)
{
        FILE *input_fp, *output_fp;
        char buffer[LINE_SIZE];
        char buffer_copy1[LINE_SIZE];
        char buffer_copy2[LINE_SIZE];
        char computed_string[LINE_SIZE];

        if (strcmp(input_filename, "stdin") == 0) {
                input_fp = stdin;
        } else {
                input_fp = fopen(input_filename, "r");
        }

        if (input_fp == NULL) {
                fprintf(stderr, "Cannot open %s file!\n", input_filename);
                return 1;
        }

        if (strcmp(output_filename, "stdout") == 0) {
                output_fp = stdout;
        } else {
                output_fp = fopen(output_filename, "w");
        }

        if (output_fp == NULL) {
                fprintf(stderr, "Cannot open %s file!\n", output_filename);
                return 1;
        }


        while (!feof(input_fp)) {

                vector *define_words = create_vector(5);
                vector *code_words = create_vector(5);
                
                /* read one line from file */
                memset(buffer, 0, LINE_SIZE);
                fgets(buffer, LINE_SIZE, input_fp);
                memcpy(buffer_copy1, buffer, LINE_SIZE);
                memcpy(buffer_copy2, buffer, LINE_SIZE);

                
                split_defines(define_words, buffer_copy1);
                split_line(code_words, buffer_copy2);

                if (define_words->size > 0 && 
                        strncmp(get_element(define_words, 0), "#define", 7) == 0) {

                        compute_defines(table, define_words);
                        /*
                         *print_vector(words);
                         */
                        
                } else {
                        /*
                        print_vector(code_words);
                        printf("%s", computed_string);
                        */
                        memset(computed_string, 0, LINE_SIZE);
                        memcpy(computed_string, 
                                compute_code(table, code_words, buffer), 
                                LINE_SIZE);
                        
                        fwrite(computed_string, strlen(computed_string), 1, output_fp);

                }

                delete_vector(define_words);
                delete_vector(code_words);

                /*
                split_buffer(words, buffer_copy);
                printf("%s", buffer);
                *
                print_vector(words);
                */
        }

        fclose(input_fp);
        fclose(output_fp);
        return 0;
}

void read_line(FILE *file, char *buffer)
{
        if (file == NULL)
                return;

        if (feof(file)) {
                buffer = NULL;
                return;
        }

        while (!feof(file)) {
                memset(buffer, 0, LINE_SIZE);
                fgets(buffer, LINE_SIZE, file);
        }
}
