#include "parser.h"

int split_line(vector *words, char *buffer)
{
	int ret = 0;
	char *token = strtok(buffer, "\n\t []{}<>=-*+/\%!&|^.,:;().");

	while (token != NULL) {
		if (strcmp(token, "\n") != 0) {
			ret = insert_string(words, token);
			if (ret)
				return ret;
		}

		token = strtok(NULL, "\n\t []{}<>=-*+/\%!&|^.,:;().");
	}
	return 0;
}

int split_defines(vector *words, char *buffer)
{
	int ret = 0;
	char *token = strtok(buffer, "\n\t ");

	while (token != NULL) {
		ret = insert_string(words, token);
		if (ret)
			return ret;

		token = strtok(NULL, "\n\t ");
	}
	return 0;
}

int compute_defines(h_table *table, vector *words, char *key)
{
	char aux[LINE_SIZE];
	int aux_size = 0;
	int i = 0;
	int ret = 0;

	memset(aux, 0, LINE_SIZE);

	if (words->size < 3)
		return 0;

	if (words->size == 3) {
		ret = insert_pair(table, words->arr[1], words->arr[2]);
		if (ret)
			return 12;
		memcpy(key, get_element(words, 1),
			strlen(get_element(words, 1)));

		return 0;
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
			memcpy(aux + aux_size, word, strlen(word));
			aux_size += strlen(word);
		} else {
			memcpy(aux + aux_size, value, strlen(value));
			aux_size += strlen(value);
		}

		if (i < words->size - 1) {
			aux[aux_size] = ' ';
			aux_size++;
		}
	}

	ret = insert_pair(table, get_element(words, 1), aux);
	if (ret)
		return 12;
	memcpy(key, get_element(words, 1), strlen(get_element(words, 1)));
	return 0;
}

void compute_undef(h_table *table, vector *words)
{
	if (words->size == 2)
		delete_entry(table, get_element(words, 1));
}

void compute_if(h_table *table, vector *words, int *condition)
{
	if (words->size == 2) {
		char *aux = get_value(table, get_element(words, 1));

		if (aux != NULL)
			*condition = atoi(aux);
		else if (aux == NULL)
			*condition = atoi(get_element(words, 1));
	}
}

void compute_ifdef(h_table *table, vector *words, int *condition)
{
	if (words->size == 2) {
		char *value = get_value(table, get_element(words, 1));

		if (value != NULL) {
			*condition = 1;
			return;
		}
	}
	*condition = 0;
}
void replace_word(char *str, char *result, char *old_word,
			char *new_word, int start_index)
{
	int new_word_size = strlen(new_word);
	int old_word_size = strlen(old_word);
	int result_size = strlen(str) + strlen(new_word) - strlen(old_word);

	memset(result, 0, result_size);
	memcpy(result, str, start_index + 1);
	memcpy(result + start_index + 1, new_word, new_word_size);
	memcpy(result + start_index + 1 + new_word_size,
		str + start_index + old_word_size + 1,
		strlen(str) - start_index + old_word_size);
}

int compute_code(h_table *table, vector *words, char *buffer)
{
	int size_counter = 0;
	int start_key = 0, start_buf = 0;
	int i = 0, valid_values = 0;
	char result[LINE_SIZE];
	char *value = NULL;

	memset(result, 0, LINE_SIZE);

	for (i = 0; i < words->size; i++) {
		char *key = get_element(words, i);

		start_key = 0;

		if (strncmp(key, "//", 2) == 0)
			break;

		/* if it's the first occurence of " */
		if (key[0] == '"') {
			start_key++;
			/* if the second " is in the same word pass it */
			if (strchr(key + 1, '"') != NULL) {
				start_buf += strlen(key);
				i++;
				break;
			}
			/* escape all words between " */
			while (i < words->size) {
				if (strchr(get_element(words, i) +
					start_key, '"') != NULL)
					break;

				start_buf += strlen(key);
				i++;
			}
		}

		value = get_value(table, key);

		if (value != NULL) {
			char *aux = strstr(buffer + start_buf, key);

			valid_values++;
			if (aux != NULL)
				size_counter = aux - buffer - 1;

			replace_word(buffer, result, key, value, size_counter);
			memcpy(buffer, result, LINE_SIZE);
		}
		start_buf += strlen(key);
	}
	return valid_values;
}

void extract_path(char *filename, char *path)
{
	size_t filename_size = strlen(filename);
	int i = 0;

	for (i = filename_size - 1; i >= 0; i--)
		if (filename[i] == '/' || filename[i] == '/')
			break;

	memcpy(path, filename, i + 1);
}

/* returns true if file exits */
int file_exists(char *include_file)
{
	FILE *fp = fopen(include_file, "r");

	if (fp != NULL) {
		fclose(fp);
		return 1;
	}
	return 0;
}

void create_include_path(char *dir_path,
			char *include_filename,
			char *include_path)
{
	strcat(include_path, dir_path);
	strcat(include_path, "/");
	strcat(include_path, include_filename);

}

int read_write_headers(h_table *table, vector *paths, char *include_path,
			FILE *output_fp, int *condition)
{
	vector *define_words = NULL;
	vector *code_words = NULL;
	FILE *include_fp = NULL;
	char buffer[LINE_SIZE];
	char buffer_copy1[LINE_SIZE];
	char buffer_copy2[LINE_SIZE];
	int ret = 0;

	include_fp = fopen(include_path, "r");
	if (include_fp == NULL) {
		fprintf(stderr, "Cannot open %s file!\n", include_path);
		return 1;
	}

	while (!feof(include_fp)) {

		ret = create_vector(&define_words, 5);
		if (ret)
			break;

		ret = create_vector(&code_words, 5);
		if (ret)
			break;

		read_line(include_fp, buffer);

		memcpy(buffer_copy1, buffer, LINE_SIZE);
		memcpy(buffer_copy2, buffer, LINE_SIZE);

		ret = split_defines(define_words, buffer_copy1);
		if (ret)
			break;

		ret = split_line(code_words, buffer_copy2);
		if (ret)
			break;

		ret = compute_directives(table, define_words, code_words,
					paths, buffer, include_path,
					output_fp, condition);
		if (ret)
			break;
	}

	fclose(include_fp);
	return ret;
}

int compute_include(h_table *table, vector *paths, vector *words,
			char *input_filename, FILE *output_fp, int *condition)
{
	char input_file_path[LINE_SIZE];
	char filename_from_include[LINE_SIZE];
	char include_path[LINE_SIZE];
	int i = 0;
	int ret = 0;

	memset(input_file_path, 0, LINE_SIZE);
	memset(filename_from_include, 0, LINE_SIZE);
	memset(include_path, 0, LINE_SIZE);

	if (strcmp(input_filename, "stdin") == 0)
		return 0;

	/* extract path from input file */
	extract_path(input_filename, input_file_path);
	if (words->size > 0) {
		char *file = get_element(words, 1);

		memcpy(filename_from_include, file + 1, strlen(file) - 2);
	}

	memcpy(include_path, input_file_path, strlen(input_file_path));
	memcpy(include_path + strlen(input_file_path),
		filename_from_include,
		strlen(filename_from_include));

	if (file_exists(include_path) == 0 && paths->size == 0)
		return 1;
	else if (file_exists(include_path) == 1)
		return read_write_headers(table, paths, include_path,
						output_fp, condition);

	/* find file in dirs received as parameter */
	for (i = 0; i < paths->size; i++) {
		memset(include_path, 0, LINE_SIZE);
		create_include_path(get_element(paths, i),
					filename_from_include, include_path);
		if (file_exists(include_path) == 1) {
			ret = read_write_headers(table, paths, include_path,
						output_fp, condition);
			if (ret)
				return ret;
		}
	}

	return 0;
}

int compute_directives(h_table *table, vector *define_words,
			vector *code_words, vector *paths,
			char *buffer, char *input_filename,
			FILE *output_fp, int *condition)
{
	int ret = 0;
	char key[LINE_SIZE];
	char buffer_copy[LINE_SIZE];
	vector *code_words1 = NULL;

	if (define_words->size <= 0)
		goto free_vectors;

	if (*condition == 0 &&
		strncmp(get_element(define_words, 0), "#endif", 6) != 0 &&
		strncmp(get_element(define_words, 0), "#elif", 5) != 0 &&
		strncmp(get_element(define_words, 0), "#else", 5) != 0) {
		goto free_vectors;
	}

	if (strncmp(get_element(define_words, 0), "#define", 7) == 0) {
		ret = compute_defines(table, define_words, key);
		if (ret)
			return ret;

	} else if (strncmp(get_element(define_words, 0), "#undef", 6) == 0) {
		compute_undef(table, define_words);

	} else if (strncmp(get_element(define_words, 0), "+", 1) == 0) {

	} else if (strncmp(get_element(define_words, 0), "#ifdef", 6) == 0) {
		compute_ifdef(table, define_words, condition);

	} else if (strncmp(get_element(define_words, 0), "#ifndef", 7) == 0) {
		compute_ifdef(table, define_words, condition);
		*condition = !(*condition);

	} else if (strncmp(get_element(define_words, 0), "#if", 3) == 0) {
		compute_if(table, define_words, condition);

	} else if (strncmp(get_element(define_words, 0), "#else", 5) == 0) {
		if (*condition == 1)
			*condition = 0;
		else
			*condition = 1;

	} else if (strncmp(get_element(define_words, 0), "#elif", 5) == 0) {
		compute_if(table, define_words, condition);

	} else if (strncmp(get_element(define_words, 0), "#endif", 6) == 0) {
		*condition = 1;

	} else if (strncmp(get_element(define_words, 0), "#include", 8) == 0) {
		ret = compute_include(table, paths, define_words,
					input_filename, output_fp, condition);
		if (ret)
			goto free_vectors;

	} else {
		int valid_values = compute_code(table, code_words, buffer);

		while (valid_values) {
			create_vector(&code_words1, 8);
			memset(buffer_copy, 0, LINE_SIZE);
			memcpy(buffer_copy, buffer, strlen(buffer));
			ret = split_line(code_words1, buffer_copy);
			if (ret)
				break;
			valid_values = compute_code(table, code_words1, buffer);
			delete_vector(code_words1);
		}

		write_line(output_fp, buffer);
	}

free_vectors:
	delete_vector(define_words);
	delete_vector(code_words);

	return ret;
}


int process_files(h_table *table, vector *paths,
			char *input_filename, char *output_filename)
{
	FILE *input_fp, *output_fp;
	vector *code_words = NULL;
	vector *define_words = NULL;
	char buffer[LINE_SIZE];
	char buffer_copy1[LINE_SIZE];
	char buffer_copy2[LINE_SIZE];
	int condition = 1, ret = 0;

	if (strcmp(input_filename, "stdin") == 0)
		input_fp = stdin;
	else
		input_fp = fopen(input_filename, "r");

	if (input_fp == NULL) {
		fprintf(stderr, "Cannot open %s file!\n", input_filename);
		return 1;
	}

	if (strcmp(output_filename, "stdout") == 0)
		output_fp = stdout;
	else
		output_fp = fopen(output_filename, "w");

	if (output_fp == NULL) {
		fprintf(stderr, "Cannot open %s file!\n", output_filename);
		return 1;
	}

	while (!feof(input_fp)) {
		ret = create_vector(&define_words, 5);
		if (ret)
			break;

		ret = create_vector(&code_words, 5);
		if (ret)
			break;

		read_line(input_fp, buffer);

		memcpy(buffer_copy1, buffer, LINE_SIZE);
		memcpy(buffer_copy2, buffer, LINE_SIZE);

		ret = split_defines(define_words, buffer_copy1);
		if (ret)
			break;

		ret = split_line(code_words, buffer_copy2);
		if (ret)
			break;
		ret = compute_directives(table, define_words, code_words,
					paths, buffer, input_filename,
					output_fp, &condition);
		if (ret)
			break;
	}

	fclose(input_fp);
	fclose(output_fp);
	return ret;
}

void read_line(FILE *file, char *buffer)
{
	if (file == NULL)
		return;

	memset(buffer, 0, LINE_SIZE);
	fgets(buffer, LINE_SIZE, file);
}

void write_line(FILE *file, char *buffer)
{
	if (file == NULL)
		return;

	if (strncmp(buffer, "\n", 1))
		fwrite(buffer, strlen(buffer), 1, file);
}
