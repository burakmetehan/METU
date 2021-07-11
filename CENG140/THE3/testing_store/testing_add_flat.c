#include <stdio.h>
#include <stdlib.h>
#include "input_taker.h"

#define NEXT(p) ((p) -> next)
#define PREV(p) ((p) -> prev)
#define NAME(p) ((p) -> name)

/* in file
2
1 X 100
3
1 25 1
4 20 1
3 30 1
1 Y 125
2
2 15 1
8 10 1
1 Z 95
2
0 11 15
0 9 5
1 7 20
3 15 35
1 X 0 27 15
1 37 15
1 Y 0 47 10
1 57 5
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


int main(void){
	Apartment *head=NULL;
	int apartment_number=0, name_len, max_band, index=0;
	int flat_index, flat_id, init_bandwidth;
	char *name;

	head = input_apartment_list(&apartment_number);

	name = add_apartment_input(&name_len, &max_band, &index);
	head = add_apartment(head, index, name, max_band);
	print_street(head, ++apartment_number);

	/* add_flat() testing */
	/* First, adding flat to newly added apartment */
	add_flat_input(&flat_index, &flat_id, &init_bandwidth);

	add_flat(head, name, flat_index, flat_id, init_bandwidth);
	print_street(head, apartment_number);

	/* Second, adding new flat to newly added apartment in the beginning of the flat_list*/
	add_flat_input(&flat_index, &flat_id, &init_bandwidth);

	add_flat(head, name, flat_index, flat_id, init_bandwidth);
	print_street(head, apartment_number);

	/* Third, adding new flat to newly added apartment in the middle */
	add_flat_input(&flat_index, &flat_id, &init_bandwidth);

	add_flat(head, name, flat_index, flat_id, init_bandwidth);
	print_street(head, apartment_number);

	/* Fourth, adding new flat to newly added apartment in the end */
	add_flat_input(&flat_index, &flat_id, &init_bandwidth);

	add_flat(head, name, flat_index, flat_id, init_bandwidth);
	print_street(head, apartment_number);

	/* Fifth, adding new flat to other apartment in the beginnning */
	scanf("%d", &name_len);
	name = str_input(name_len);
	add_flat_input(&flat_index, &flat_id, &init_bandwidth);

	add_flat(head, name, flat_index, flat_id, init_bandwidth);
	print_street(head, apartment_number);

	/* Sixth, adding new flat to previous apartment in the first index */
	add_flat_input(&flat_index, &flat_id, &init_bandwidth);

	add_flat(head, name, flat_index, flat_id, init_bandwidth);
	print_street(head, apartment_number);

	/* Seventh, adding new flat to other apartment in the beginnning */
	scanf("%d", &name_len);
	name = str_input(name_len);
	add_flat_input(&flat_index, &flat_id, &init_bandwidth);

	add_flat(head, name, flat_index, flat_id, init_bandwidth);
	print_street(head, apartment_number);

	/* Eighth, adding new flat to previous apartment in the first index */
	add_flat_input(&flat_index, &flat_id, &init_bandwidth);

	add_flat(head, name, flat_index, flat_id, init_bandwidth);
	print_street(head, apartment_number);


	

	

	
 
	return 0;
}
