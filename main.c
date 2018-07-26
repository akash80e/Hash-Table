#include<stdlib.h>
#include"hash_table.c"

int main(){
	hash_table* table = NULL;
	table = new_table();
	del_table(table);

}