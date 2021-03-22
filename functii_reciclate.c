/* function to check if string has '/0' */
void print_string_decimal(char *str)
{
        int i = 0;

        for (i = 0; i < strlen(str) + 1; i++) {
                printf("%d ", str[i]);
        }
        printf("\n");

        /*
        for (i = 0; i < strlen(entry->key) + 1; i++)
                printf("%d ", entry->key[i]);

        printf("\n");
        
        for (i = 0; i < strlen(entry->value) + 1; i++)
                printf("%d ", entry->value[i]);
         */
}




        /* 

        
        printf("key: %s, value: %s\n", entry->key, entry->value); 
        printf("%d, %d\n", paths->size, paths->capacity);
        */

        /*
        h_table *table = create_table();

        insert_string(paths, "11111");
        insert_string(paths, "22222");
        insert_string(paths, "33333");
        insert_string(paths, "44444");
        insert_string(paths, "55555");
        insert_string(paths, "666666");
        insert_string(paths, "777777");

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

        */



void compute_defines(h_table *table, char buffer[], vector *words)
{       
        char aux[LINE_SIZE];
        int aux_size = 0;
        int i = 0;
        
        if (words->size == 3) {
                insert_pair(table, words->arr[1], words->arr[2]);
                return;
        }
        
        if (words->size > 3) {
        }

        for (i = 2; i < words->size; i++) {
                char *word = get_element(words, i);
                char *value = NULL;
                
                if (word[0] == '(') {
                        value = table.get_value(table, word + 1);
                        aux[aux_size] = '(';
                        aux_size++;
                } else {
                        value = table.get_value(table, word);
                }

                if (value == NULL) {
                        memcpy(aux + aux_size, word + aux_size, strlen(value));
                } else {
                        memcpy(aux + aux_size, value, strlen(value));
                        aux_size += strlen(value);

                }
        }

        insert_pair(table, get_element(words, 1), aux);

}




void compute_defines(h_table *table, char buffer[], int start_index)
{       
        char value[LINE_SIZE];
        char key[LINE_SIZE];
        int key_size = 0;
        int value_size = 0;
        int i = 0;
        int key_start_index = 0, key_end_index = 0;
        int value_start_index = 0, value_end_index = 0;

        /*
        for (i = start_index; i < strlen(buffer); i++) {
                if (buffer[i] > 'a' && buffer[i] < 'z' ||
                        buffer[i] > 'A' && buffer[i] < 'Z' ||
                        buffer[i] == '_') {
                                
                        if (key_start_index == 0) {
                                key_start_index = i;
                                key_end_index = i;
                        } else if (i == key_end_index - 1) {
                                key_end_index = i;
                        } else {
                                key_size = key_end_index - key_start_index;
                                memset(key, 0, LINE_SIZE);
                                memcpy(key, buffer + key_start_index, key_size);
                        }

                }
        }

        for (i = key_end_index + 1; i < strlen(buffer); i++) {
                if (buffer[i] > 'a' && buffer[i] < 'z' ||
                        buffer[i] > 'A' && buffer[i] < 'Z' ||
                        buffer[i] == '_') {
                                
                        if (value_start_index == 0) {
                                value_start_index = i;
                                value_end_index = i;
                        } else if (i == value_end_index - 1) {
                                value_end_index = i;
                        } else {
                                value_size = value_end_index - value_start_index;
                                memset(value, 0, LINE_SIZE);
                                memcpy(value, buffer + value_start_index, value_size);
                        }

                }
        }

*/

        if (words->size == 3) {
                insert_pair(table, words->arr[1], words->arr[2]);
                return;
        }
        
        if (words->size > 3) {
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
                        memcpy(aux + aux_size, word + aux_size, strlen(value));
                } else {
                        memcpy(aux + aux_size, value, strlen(value));
                        aux_size += strlen(value);

                }
        }

        insert_pair(table, get_element(words, 1), aux);

}



void compute_defines(h_table *table, vector* words, char buffer[], int start_index)
{       
        char value[LINE_SIZE];
        char key[LINE_SIZE];
        int value_size = 0;
        int i = 0;
        int key_start_index = 0, key_end_index = 0;
        int value_start_index = 0, value_end_index = 0;


        
        char *key = strstr(buffer, get_element(words, 1));
        int key_size = strlen(get_element(words, 1));


        char *val_start = strstr(buffer, get_element(words, 2));
        char value[LINE_SIZE];
        memcpy(value, val_start, CEPULA MEA PPUN ACI IICAIADSADAS;
        
        for (i = start_index; i < strlen(buffer); i++) {
                if (buffer[i] > 'a' && buffer[i] < 'z' ||
                        buffer[i] > 'A' && buffer[i] < 'Z' ||
                        buffer[i] == '_') {
                                
                        if (key_start_index == 0) {
                                key_start_index = i;
                                key_end_index = i;
                        } else if (i == key_end_index - 1) {
                                key_end_index = i;
                        } else {
                                key_size = key_end_index - key_start_index;
                                memset(key, 0, LINE_SIZE);
                                memcpy(key, buffer + key_start_index, key_size);
                        }

                }
        }

        for (i = key_end_index + 1; i < strlen(buffer); i++) {
                if (buffer[i] > 'a' && buffer[i] < 'z' ||
                        buffer[i] > 'A' && buffer[i] < 'Z' ||
                        buffer[i] == '_') {
                                
                        if (value_start_index == 0) {
                                value_start_index = i;
                                value_end_index = i;
                        } else if (i == value_end_index - 1) {
                                value_end_index = i;
                        } else {
                                value_size = value_end_index - value_start_index;
                                memset(value, 0, LINE_SIZE);
                                memcpy(value, buffer + value_start_index, value_size);
                        }

                }
        }



        if (words->size == 3) {
                insert_pair(table, words->arr[1], words->arr[2]);
                return;
        }
        
        if (words->size > 3) {
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
                        memcpy(aux + aux_size, word + aux_size, strlen(value));
                } else {
                        memcpy(aux + aux_size, value, strlen(value));
                        aux_size += strlen(value);

                }
        }

        insert_pair(table, get_element(words, 1), aux);

}


