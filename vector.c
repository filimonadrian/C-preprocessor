#include "vector.h"


vector *create_vector(int capacity) {
        vector *v = malloc(sizeof(vector));
        v->size = 0;
        v->capacity = capacity;
        v->arr = malloc(v->capacity * sizeof(char*));

        return v;
}

void insert_string(vector *v, char *str) {
        if (v->size == v->capacity - 1) {
                v->capacity = v->capacity * 2;
                v->arr = realloc(v->arr, v->capacity * sizeof(char*));
        }

        v->arr[v->size] = malloc(strlen(str) * sizeof(char));
        memcpy(v->arr[v->size], str, strlen(str));
        /*
        strcpy(v->arr[v->size], str);
        */
        v->size++;  
}


void delete_vector(vector *v) {
        int i = 0;

        for (i = 0; i < v->size; i++) {
                free(v->arr[i]);
        }

        free(v->arr);
        free(v);
}

void print_vector(vector *v) {
        int i = 0;

        for (i = 0; i < v->size; i++) {
                printf("%s ", v->arr[i]);
        }

        printf("\n");
}