#include "hashtable.h"

/* djb2 by Dan Bernstein */
unsigned int hash(char *key)
{
        unsigned long hash = 5381;
        int c;

        while ((c = *key++)) {
                /* hash * 33 + c */
                hash = ((hash << 5) + hash) + c;
        }

        return hash % TABLE_SIZE;
}

h_table *create_table(void)
{
        int i = 0;
        /* create table */
        h_table *table = malloc(sizeof(struct h_table));

        /* create all entries for the table */
        table->entries = malloc(TABLE_SIZE * sizeof(struct entry_t *));

        /* set all entries to NULL */
        for (i = 0; i < TABLE_SIZE; i++)
                table->entries[i] = NULL;

        return table;
}

entry_t *create_pair(char *key, char *value)
{
        /* create an entry */
        entry_t *entry = malloc(sizeof(entry_t));

        entry->key = malloc(strlen(key) + 1);
        entry->value = malloc(strlen(value) + 1);
        memset(entry->key, 0, strlen(key) + 1);
        memset(entry->value, 0, strlen(value) + 1);

        memcpy(entry->key, key, strlen(key));
        memcpy(entry->value, value, strlen(value));
        /*
        strcpy(entry->key, key);
        strcpy(entry->value, value);
        */
        entry->next = NULL;

        return entry;
}

/* insert a new pair or update the value for an existent key */
void insert_pair(h_table *table, char *key, char *value)
{
        unsigned int hashcode = 0;
        entry_t *prev_neigh = NULL;
        entry_t *trailer = NULL;

        hashcode = hash(key);

        /* insert entry if does not already exist a slot with its hashcode */
        trailer = table->entries[hashcode];
        if (trailer == NULL) {
                table->entries[hashcode] = create_pair(key, value);
                return;
        }

        /* update the value if the entry exists in the list of a slot*/
        while (trailer != NULL) {
                if (strcmp(trailer->key, key) == 0) {
                        free(trailer->value);
                        trailer->value = malloc(strlen(value) + 1);
                        memset(trailer->value, 0, strlen(value) + 1);
                        memcpy(trailer->value, value, strlen(value));
                        return;
                }

                prev_neigh = trailer;
                trailer = prev_neigh->next;
        }

        prev_neigh->next = create_pair(key, value);

}

void insert_entry(h_table *table, entry_t *entry)
{
        unsigned int hashcode = 0;
        entry_t *prev_neigh = NULL;
        entry_t *trailer = NULL;

        hashcode = hash(entry->key);

        /* insert entry if does not already exist a slot with its hashcode */
        trailer = table->entries[hashcode];
        if (trailer == NULL) {
                table->entries[hashcode] = entry;
                return;
        }

        
        /* update the value if the entry exists in the list of a slot*/
        while (trailer != NULL) {
                if (strcmp(trailer->key, entry->key) == 0) {
                        free(trailer->value);
                        free(trailer->key);
                        entry->next = trailer->next;
                        trailer = entry;
                        return;
                }
                
                prev_neigh = trailer;
                trailer = prev_neigh->next;
        }

        prev_neigh->next = entry;
}

char *get_value(h_table *table, char *key)
{
        entry_t *entry = NULL; 
        int hashcode = 0;

        hashcode = hash(key);
        entry = table->entries[hashcode];

        if (entry == NULL)
                return NULL;

        /* traverse the list and check if the keys correspond */
        while (entry != NULL) {
                if (strcmp(entry->key, key) == 0)
                        return entry->value;
                
                entry = entry->next;
        }

        return NULL;
}


void delete_entry(h_table *table, char *key)
{
        int hashcode = 0;
        int index_list = 0; 
        entry_t *entry = NULL;
        entry_t *prev_neigh = NULL;

        hashcode = hash(key);
        entry = table->entries[hashcode];

        if (entry == NULL)
                return;

        while (entry != NULL) {
                if (strcmp(entry->key, key) == 0) {
                        /* head list without neighbours */
                        if (entry->next == NULL && index_list == 0)
                                table->entries[hashcode] = NULL;

                        /* head list with neighbours */
                        if (entry->next != NULL && index_list == 0)
                                table->entries[hashcode] = entry->next;

                        /* middle item in list */
                        if (entry->next != NULL && index_list != 0)
                                prev_neigh->next = entry->next;

                        /* last item in list */
                        if (entry->next == NULL && index_list != 0)
                                prev_neigh->next = NULL;

                        /* free space for entry */
                        free(entry->key);
                        free(entry->value);
                        free(entry);
                }

                prev_neigh = entry;
                entry = entry->next;
                index_list++;
        }
}

void delete_table(h_table *table)
{
        entry_t *entry = NULL;
        entry_t *aux = NULL;
        int i = 0;

        for (i = 0; i < TABLE_SIZE; i++) {
                if (table->entries[i] != NULL) {
                        entry = table->entries[i];
                        while (entry != NULL) {
                                aux = entry;
                                entry = entry->next;
                                /* free space for entry */
                                free(aux->key);
                                free(aux->value);
                                free(aux);
                        }
                }
        }
        free(table->entries);
        free(table);
}

void print_table(h_table *table)
{
        int i = 0;
        entry_t *entry = NULL;
        

        for (i = 0; i < TABLE_SIZE; i++) {
                entry = table->entries[i];

                if (entry == NULL)
                        continue;

                printf("slot[%d]: ", i);

                while (entry != NULL) {
                        printf("%s = _%s_ ", entry->key, entry->value);
                        entry = entry->next;
                }

                printf("\n");
        }
}
