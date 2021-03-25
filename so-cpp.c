#include "so-cpp.h"

int parse_symbol_mapping(char *str, entry_t **entry)
{
        size_t key_mapping = 0;
        size_t value_size = 0;
        size_t str_size = strlen(str);
        size_t i = 0;
        char key[LINE_SIZE], value[LINE_SIZE];
        int ret = 0;

        memset(key, 0, LINE_SIZE);
        memset(value, 0, LINE_SIZE);

        for (i = 0; i < str_size; i++) {
                if (str[i] == '=') {
                        /* set flag for mapping */
                        key_mapping = 1;

                        /* copy key in entry and append '\0' */
                        memcpy(key, str, i);

                        /* copy value in entry and append '\0' */
                        value_size = str_size - i - 1;

                        memcpy(value, str + i + 1, value_size);
                        ret = create_pair(key, value, entry);
                        if (ret)
                                return ret;
                        break;
                }
        }

        /* if the string does not contain '=' means the value is empty */
        if (key_mapping == 0) {
                /* copy in key entire received string */
                memcpy(key, str, str_size);
                ret = create_pair(key, "", entry);
                if (ret)
                        return ret;
        }

        return 0;
}


void parse_path(vector *paths, char *str)
{
        insert_string(paths, str);
}

int parse_filename(char **filename, char *str)
{
        if (*filename == NULL) {
                *filename = malloc((strlen(str) + 1) * sizeof(char));
                if (filename == NULL)
                        exit(12);

                memset(*filename, 0, strlen(str) + 1);
                memcpy(*filename, str, strlen(str));
        } else {
                fprintf(stderr, "Multiple definitions of file!\n");
        }

        return 0;
}

int read_arguments(h_table *table, vector *paths,
                    char **output_file, char **input_file,
                    int argc, char **argv)
{
        int i = 0;
        int counter = 0;
        int ret = 0;
        entry_t *entry = NULL;

        while (i < argc) {
                /* if it's case -D */
                if (strcmp(argv[i], "-D") == 0) {
                        i++;
                        ret = parse_symbol_mapping(argv[i], &entry);
                        if (ret)
                                return ret;
                        insert_entry(table, entry);

                } else if (strncmp(argv[i], "-D", 2) == 0) {
                        ret = parse_symbol_mapping(argv[i] + 2, &entry);
                        if (ret)
                                return ret;
                        insert_entry(table, entry);

                } else if (strcmp(argv[i], "-I") == 0) {
                        i++;
                        parse_path(paths, argv[i]);

                } else if (strncmp(argv[i], "-I", 2) == 0) {
                        parse_path(paths, argv[i] + 2);

                } else if (strcmp(argv[i], "-o") == 0) {
                        i++;
                        ret = parse_filename(output_file, argv[i]);
                        if (ret)
                                return ret;

                } else if (strncmp(argv[i], "-o", 2) == 0) {
                        ret = parse_filename(output_file, argv[i] + 2);
                        if (ret)
                                return ret;
                } else if (i > 0) {
                        if (counter == 0) {
                                ret = parse_filename(input_file, argv[i]);
                                if (ret)
                                        return ret;
                        } else if (counter == 1) {
                                ret = parse_filename(output_file, argv[i]);
                                if (ret)
                                        return ret;
                        } else {
                                return 1;
                        }
                        counter++;
                }

                i++;
        }

        return 0;
}

int main(int argc, char **argv)
{
        char *output_filename = NULL;
        char *input_filename = NULL;
        vector *paths = NULL;
        vector *words = NULL;
        h_table *table = NULL;
        int ret = 0;

        ret = create_vector(&paths, 8);
        if (ret)
                goto free_memory;

        ret = create_vector(&words, 8);
        if (ret)
                goto free_memory;

        ret = create_table(&table);
        if (ret)
                goto free_memory;


        ret = read_arguments(table, paths, &output_filename, &input_filename, argc, argv);
        if (ret > 0)
                goto free_memory;

        if (input_filename == NULL) {
                ret = parse_filename(&input_filename, "stdin");
                if (ret)
                        goto free_memory;
        }

        if (output_filename == NULL) {
                ret = parse_filename(&output_filename, "stdout");
                if (ret)
                        goto free_memory;
        }

        ret = process_files(table, paths, input_filename, output_filename);
        if (ret > 0)
                goto free_memory;

free_memory:
        free(input_filename);
        free(output_filename);
        delete_vector(paths);
        delete_vector(words);
        delete_table(table);


        return ret;
}

