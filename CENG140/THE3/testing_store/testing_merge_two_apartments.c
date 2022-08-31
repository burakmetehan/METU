#include <stdio.h>
#include <stdlib.h>
#include "input_taker.h"

#define NEXT(p) ((p) -> next)
#define PREV(p) ((p) -> prev)
#define NAME(p) ((p) -> name)


/* in file
7
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
0
5 BURAK 30
0
4 mete 35
0
6 Tuncel 45
0
1 X
1 Z
1 Y
1 Q
5 BURAK
1 X
4 mete
6 Tuncel
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
	int apartment_number=0, name_len;
	char *apartment_name_1, *apartment_name_2;
	
	head = input_apartment_list(&apartment_number);
	print_street(head, apartment_number);

	/* merge_two_apartments() testing [INPUT FORM IS SAME WITH remove_apartment()] */
	apartment_name_1 = remove_apartment_input(&name_len);
	apartment_name_2 = remove_apartment_input(&name_len);
	head = merge_two_apartments(head, apartment_name_1, apartment_name_2);
	print_street(head, --apartment_number);


	apartment_name_1 = remove_apartment_input(&name_len);
	apartment_name_2 = remove_apartment_input(&name_len);
	head = merge_two_apartments(head, apartment_name_1, apartment_name_2);
	print_street(head, --apartment_number);
	

	apartment_name_1 = remove_apartment_input(&name_len);
	apartment_name_2 = remove_apartment_input(&name_len);
	head = merge_two_apartments(head, apartment_name_1, apartment_name_2);
	print_street(head, --apartment_number);

	apartment_name_1 = remove_apartment_input(&name_len);
	apartment_name_2 = remove_apartment_input(&name_len);
	head = merge_two_apartments(head, apartment_name_1, apartment_name_2);
	print_street(head, --apartment_number);

	return 0;
}
