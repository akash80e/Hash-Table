#include<stdlib.h>
#include<string.h>
#include "hash_table.h"

static ht_item* new_item(const char *k, const char *v){
	ht_item* item = (ht_item*)malloc(sizeof(ht_item));
	item->key = strdup(k);
	item->value = strdup(v);
	return item;
}

hash_table* new_table(){
	hash_table* table = (hash_table*)malloc(sizeof(hash_table));
	table->size = 50;
	table->count = 0;
	table->items = calloc((size_t)table->size, sizeof(ht_item*));
	return table;
}

static void del_item(ht_item* item){
	free(item->key);
	free(item->value);
	free(item);
}

void del_table(hash_table* table){
	int i;
	for(i=0;i<table->size;i++){
		del_item(table->items[i]);
		free(table->items);
		free(table);
	}
}

static int ht_hash(const char* s, const int a, const int m) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i+1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

static int ht_get_hash(const char* s, const int num_buckets, const int attempt
) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}




