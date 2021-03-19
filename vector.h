#include<stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct vector {
        char **arr;
        int size;
        int capacity;
} vector;

vector *create_vector();
void insert_string(vector *v, char *str);
void delete_vector(vector *v);        
void print_vector(vector *v);