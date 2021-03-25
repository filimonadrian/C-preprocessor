#include "vector.h"

int create_vector(vector **v, int capacity)
{
        *v = malloc(sizeof(vector));
        if (*v == NULL)
                exit(12);

        (*v)->size = 0;
        (*v)->capacity = capacity;
        (*v)->arr = malloc((*v)->capacity * sizeof(char *));
        if ((*v)->arr == NULL)
                exit(12);
        return 0;
}

int insert_string(vector *v, char *str)
{
        if (v->size == v->capacity - 1) {
                v->capacity = v->capacity * 2;
                v->arr = realloc(v->arr, v->capacity * sizeof(char *));
                if (v->arr == NULL)
                        exit(12);
        }

        v->arr[v->size] = malloc((strlen(str) + 1) * sizeof(char));
        if (v->arr[v->size] == NULL)
                exit(12);

        memset(v->arr[v->size], 0, strlen(str) + 1);
        memcpy(v->arr[v->size], str, strlen(str));
        v->size++;
        return 0;
}

char *get_element(vector *v, int index)
{
        if (v != NULL && v->arr != NULL && v->arr[index] != NULL)
                return v->arr[index];

        return NULL;       
}

void delete_vector(vector *v)
{
        int i = 0;

        for (i = 0; i < v->size; i++)
                free(v->arr[i]);

        free(v->arr);
        free(v);
        v = NULL;
}

void print_vector(vector *v)
{
        int i = 0;

        for (i = 0; i < v->size; i++)
                printf("%s ", v->arr[i]);

        printf("\n");
}
