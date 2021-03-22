#include "parser.h"

void split_line(vector *words, char buffer[])
{
        char* token = strtok(buffer, "\n\t []{}<>=-*+/\%!&|^.,:;()."); 

        while (token != NULL) { 
                /*
                */
                printf("%s\n", token);
                insert_string(words, token);
                token = strtok(NULL, "\n\t []{}<>=-*+/\%!&|^.,:;()."); 

        }
        /*
        */
        insert_string(words, "\n");
}

void split_defines(vector *words, char buffer[])
{
        char* token = strtok(buffer, "\n\t "); 

        while (token != NULL) { 
                /*
                printf("%s\n", token);
                */
                insert_string(words, token);
                token = strtok(NULL, "\n\t  "); 
        }
        /*
        */
}


void replace_values()
{

}

void compute_defines(h_table *table, vector *words)
{       
        char aux[LINE_SIZE];
        int aux_size = 0;
        int i = 0;
        
        memset(aux, 0, LINE_SIZE);

        if (words->size < 3) {
                return
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
                        printf("Valoarea este:  %s\n", value);

                }
                if (i < words->size - 1) {
                        aux[aux_size] = ' ';
                        aux_size++;
                }
        }

        insert_pair(table, get_element(words, 1), aux);
}



void read_file(h_table *table, char *input_filename, char *output_filename)
{
        FILE *input_fp, output_fp;
        char buffer[LINE_SIZE];
        char buffer_copy[LINE_SIZE];
        char computed_string[LINE_SIZE]; 
        int i = 0;


        input_fp = fopen(input_filename, "r");
        if (input_fp == NULL)
                fprintf(stderr, "Cannot open %s file!\n", input_filename);

        while (!feof(input_fp)) {

                /* read one line from file */
                memset(buffer, 0, LINE_SIZE);
                fgets(buffer, LINE_SIZE, input_fp);
                memcpy(buffer_copy, buffer, LINE_SIZE);

                vector *words = create_vector(5);
                for (i = 0; i < strlen(buffer); i++) {
                        if (strncmp(buffer + i , "#define", 7) == 0) {
                                split_defines(words, buffer);
                                /*
                                printf("\n");
                                compute_defines(table, words);
                                */
                                compute_defines(table, words);
                                print_vector(words);
                                break;
                        }
                }
                delete_vector(words);

                

                /*
                split_buffer(words, buffer_copy);
                printf("%s", buffer);
                *
        print_vector(words);
                */
        }

        fclose(input_fp);
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