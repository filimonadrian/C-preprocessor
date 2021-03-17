#include "so-cpp.h"

int main() {

        h_table *table = create_table();

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

        delete_table(table);

        return 0;
}