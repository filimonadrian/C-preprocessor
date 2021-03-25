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

int create_table(h_table **table)
{
        int i = 0;
        /* create table */
        *table = malloc(sizeof(struct h_table));
        if (table == NULL)
                return 12;
        /* create all entries for the table */
        (*table)->entries = malloc(TABLE_SIZE * sizeof(struct entry_t *));
        if ((*table)->entries == NULL)
                return 12;

        /* set all entries to NULL */
        for (i = 0; i < TABLE_SIZE; i++)
                (*table)->entries[i] = NULL;

        return 0;
}

int create_pair(char *key, char *value, entry_t **entry)
{
        /* create an entry */
        *entry = malloc(sizeof(entry_t));

        if ((*entry) == NULL)
                return 12;

        (*entry)->key = malloc(strlen(key) + 1);
        if ((*entry)->key == NULL)
                return 12;

        (*entry)->value = malloc(strlen(value) + 1);
        if ((*entry)->value == NULL)
                return 12;

        memset((*entry)->key, 0, strlen(key) + 1);
        memset((*entry)->value, 0, strlen(value) + 1);

        memcpy((*entry)->key, key, strlen(key));
        memcpy((*entry)->value, value, strlen(value));
        (*entry)->next = NULL;

        return 0;
}

/* insert a new pair */
int insert_pair(h_table *table, char *key, char *value)
{
        unsigned int hashcode = 0;
        entry_t *prev_neigh = NULL;
        entry_t *trailer = NULL;
        int ret = 0;

        hashcode = hash(key);

        /* insert entry if does not already exist a slot with its hashcode */
        trailer = table->entries[hashcode];
        if (trailer == NULL) {
                ret = create_pair(key, value, &table->entries[hashcode]);
                if (ret)
                        return 12;
                return 0;
        }

        /* if the entry exists in the list of a slot don't update the value */
        while (trailer != NULL) {
                if (strcmp(trailer->key, key) == 0) {
                        return 0;
                }

                prev_neigh = trailer;
                trailer = prev_neigh->next;
        }

        ret = create_pair(key, value, &prev_neigh->next);
        if (ret)
                return 12;

        return 0;
}

void insert_entry(h_table *table, entry_t *entry)
{
        unsigned int hashcode = 0;
        entry_t *prev_neigh = NULL;
        entry_t *trailer = NULL;

        if (entry == NULL) {
                return;
        }

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
                        return;
                }

                prev_neigh = entry;
                entry = entry->next;
                index_list++;
        }
}

void delete_table(h_table *table)
{
        int i = 0;

        for (i = 0; i < TABLE_SIZE; i++) {
                entry_t *aux = NULL;

                aux = table->entries[i];
                while (table->entries[i]) {
                        aux = table->entries[i];
                        table->entries[i] = table->entries[i]->next;
                        /* free space for entry */
                        free(aux->key);
                        free(aux->value);
                        free(aux);
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
