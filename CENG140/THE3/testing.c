#include <stdio.h>
#include <stdlib.h>
#include "input_taker.h"

#define NEXT(p) ((p) -> next)
#define PREV(p) ((p) -> prev)
#define NAME(p) ((p) -> name)


/* Tester Input Format
-Initial Aparment and Flat Lists Data

-Functions Data as follows:
	-add_apartment():
		-data of new apartment: name_len, name, max_bandwidth
		-index
	
	-add_flat():
		-if previous apartment will be used
			flat_index, flat_id, initial bandwidth
		-else
			len of name of the apartment, name of the apartment, flat_index, flat_id, initial bandwidth

	-remove_apartment():



*/


char* add_apartment_input(int *name_len, int* max_band, int* index){
	char *name;

	scanf("%d", name_len);
	name = str_input(*name_len);
	scanf("%d", max_band);
	scanf("%d", index);

	return name;
}


char * add_flat_input(int *name_len, int *flat_index, int *flat_id, int *init_bandwidth){
	char *name;
	scanf("%d", name_len);
	name = str_input(*name_len);
	scanf("%d", flat_index);
	scanf("%d", flat_id);
	scanf("%d", init_bandwidth);
	return name;
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


char* merge_two_apartments_input(int *name_len){
	char *name;
	scanf("%d", name_len);
	name = str_input(*name_len);
	return name;
}


char* relocate_flats_to_same_apartment_input(int *name_len, int *flat_id_to_shift, int *flat_id_list_len, int **flat_id_list){
	char *name;
	int i;

	scanf("%d", name_len);
	name = str_input(*name_len);

	scanf("%d", flat_id_to_shift);
	scanf("%d", flat_id_list_len);

	*flat_id_list = malloc(sizeof(int) * (*flat_id_list_len)+1);

	for(i = 0; i < *flat_id_list_len; i++){
		scanf("%d", &(*flat_id_list)[i]);
	}	
	(*flat_id_list)[i] = 0;

	return name;
}


#define FUNCTION_1_CASE_NUMBER 6
#define FUNCTION_2_CASE_NUMBER 16
#define FUNCTION_3_CASE_NUMBER 8
#define FUNCTION_4_CASE_NUMBER 6
#define FUNCTION_5_CASE_NUMBER 2
#define FUNCTION_6_CASE_NUMBER 8
#define FUNCTION_7_CASE_NUMBER 10

int main(void){
	Apartment *head=NULL;
	int apartment_number=0, i;

	int max_bandwidth, index;
	int name_len, flat_index, flat_id, init_bandwidth;
	int flat_id_to_shift, flat_id_list_len, *flat_id_list=NULL;
	char *apartment_name_1, *apartment_name_2;
	char *new_apartment_name, *name;
	
	/* Testing Function_1 */
	for(i=0; i < FUNCTION_1_CASE_NUMBER; i++){
		head = input_apartment_list(&apartment_number);
		name = add_apartment_input(&name_len, &max_bandwidth, &index);
		head = add_apartment(head, index, name, max_bandwidth);
		print_street_2(head, 1, i+1);
	}

	/* Testing Function_2 */
	for(i=0; i < FUNCTION_2_CASE_NUMBER; i++){
		head = input_apartment_list(&apartment_number);
		name = add_flat_input(&name_len, &flat_index, &flat_id, &init_bandwidth);
		add_flat(head, name, flat_index, flat_id, init_bandwidth);
		print_street_2(head, 2, i+1);
	}

	/* Testing Function_3 */
	for(i=0; i < FUNCTION_3_CASE_NUMBER; i++){
		head = input_apartment_list(&apartment_number);
		name = remove_apartment_input(&name_len);
		head = remove_apartment(head, name);
		print_street_2(head, 3, i+1);
	}

	/* Testing Function_4 */
	for(i=0; i < FUNCTION_4_CASE_NUMBER; i++){
		head = input_apartment_list(&apartment_number);
		name = make_flat_empty_input(&name_len, &flat_id);
		make_flat_empty(head, name, flat_id);
		print_street_2(head, 4, i+1);
	}

	printf("\nFunction 5 (Sum of Max Bandwidth) Outputs:\n");
	/* Testing Function_5 */
	for(i=0; i < FUNCTION_5_CASE_NUMBER; i++){
		head = input_apartment_list(&apartment_number);
		printf("\tCase_%d: %d\n", i+1, find_sum_of_max_bandwidths(head));
	}

	/* Testing Function_6 */
	for(i=0; i < FUNCTION_6_CASE_NUMBER; i++){
		head = input_apartment_list(&apartment_number);
		apartment_name_1 = merge_two_apartments_input(&name_len);
		apartment_name_2 = merge_two_apartments_input(&name_len);
		head = merge_two_apartments(head, apartment_name_1, apartment_name_2);
		print_street_2(head, 6, i+1);
	}

	/* Testing Function_7 */
	for(i=0; i < FUNCTION_7_CASE_NUMBER; i++){
		head = input_apartment_list(&apartment_number);
		new_apartment_name = relocate_flats_to_same_apartment_input(&name_len, &flat_id_to_shift, &flat_id_list_len, &flat_id_list);
		relocate_flats_to_same_apartment(head, new_apartment_name, flat_id_to_shift, flat_id_list);
		print_street_2(head, 7, i+1);
	}

	return 0;
}
