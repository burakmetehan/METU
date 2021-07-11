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
1 25 1
4 20 1
3 30 1
1 Y 125
2
2 15 1
8 10 1
1 Z 95
4
9 5 1
7 20 1
11 15 1
15 35 1
1 Q 135
3
6 50 1
5 35 1
14 50 1
1 Z
1 Q
1 X
1 Y
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

int main(void){
	Apartment *head=NULL;
	int apartment_number=0, name_len;
	char *name;

	head = input_apartment_list(&apartment_number);
	print_street(head, apartment_number);

	/* remove_apartment() testing */
	name = remove_apartment_input(&name_len);
	head = remove_apartment(head, name);
	print_street(head, --apartment_number);

	name = remove_apartment_input(&name_len);
	head = remove_apartment(head, name);
	print_street(head, --apartment_number);

	name = remove_apartment_input(&name_len);
	head = remove_apartment(head, name);
	print_street(head, --apartment_number);

	name = remove_apartment_input(&name_len);
	head = remove_apartment(head, name);
	print_street(head, --apartment_number);
	
 
	return 0;
}
