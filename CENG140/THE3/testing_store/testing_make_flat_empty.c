#include <stdio.h>
#include <stdlib.h>
#include "input_taker.h"

#define NEXT(p) ((p) -> next)
#define PREV(p) ((p) -> prev)
#define NAME(p) ((p) -> name)

/* in file
4
1 X 105
3
1 25 0
4 20 0
3 30 0
1 Y 125
2
2 15 0
8 10 0
1 Z 95
4
9 5 0
7 20 0
11 15 0
15 35 0
1 Q 135
3
6 50 0
5 35 0
14 50 0
1 X 4
1 X 1
1 Y 8
1 Z 15
1 Q 14
*/

char* add_apartment_input(int *name_len, int* max_band, int* index){
	char *name;

	scanf("%d", name_len);
	name = str_input(*name_len);
	scanf("%d", max_band);
	scanf("%d", index);

	return name;
}


void add_flat_input(int *flat_index, int *flat_id, int *init_bandwidth){
	scanf("%d", flat_index);
	scanf("%d", flat_id);
	scanf("%d", init_bandwidth);
}


char* remove_apartment_input(int *name_len){
	char *name;
	scanf("%d", name_len);
	name = str_input(*name_len);
	return name;
}


char* make_flat_empty_input(int *name_len, int *flat_id){
	char *name;
	
	scanf("%d", name_len);
	name = str_input(*name_len);
	scanf("%d", flat_id);

	
	return name;
}

int main(void){
	Apartment *head=NULL;
	int apartment_number=0, name_len, flat_id;
	char *name;

	head = input_apartment_list(&apartment_number);
	print_street(head, apartment_number);

	/* make_flat_empty() testing */
	name = make_flat_empty_input(&name_len, &flat_id);
	make_flat_empty(head, name, flat_id);
	print_street(head, apartment_number);

	name = make_flat_empty_input(&name_len, &flat_id);
	make_flat_empty(head, name, flat_id);
	print_street(head, apartment_number);
	
	name = make_flat_empty_input(&name_len, &flat_id);
	make_flat_empty(head, name, flat_id);
	print_street(head, apartment_number);

	name = make_flat_empty_input(&name_len, &flat_id);
	make_flat_empty(head, name, flat_id);
	print_street(head, apartment_number);
	
	name = make_flat_empty_input(&name_len, &flat_id);
	make_flat_empty(head, name, flat_id);
	print_street(head, apartment_number);
 
	return 0;
}
