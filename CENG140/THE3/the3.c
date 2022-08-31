#include <stdio.h>
#include <stdlib.h>
#include "the3.h"


/* Macros */
#define NEXT(p) ((p) -> next)
#define PREV(p) ((p) -> prev)

#define NAME(p) ((p) -> name)
#define LIST(p) ((p) -> flat_list)
#define MAX_BAND(p) ((p) -> max_bandwidth)

#define ID(p) ((p) -> id)
#define INIT_BAND(p) ((p) -> initial_bandwidth)
#define IS_EMPTY(p) ((p) -> is_empty)


/* Helper Functions */
int str_compare(char *str1, char *str2){ /* Returns 1 if the strings are equal; otherwise, returns 0 */
	for(; *str1==*str2 && *str1 != 0 && *str2 != 0; str1++, str2++);

	if(*str1 == *str2) return 1;
	else return 0;
}


int total_bandwidth(Flat *head){
	int res=0;
	for(; head; head = NEXT(head)) res += INIT_BAND(head);
	return res;
}


void flat_free(Flat *flat_head){
	Flat *temp = flat_head;
	while(flat_head){
		temp = NEXT(flat_head);
		free(flat_head);
		flat_head = temp;
	}
}


Apartment* find_last_apartment(Apartment *head){ /* Return a pointer to last apartment */
	Apartment *last_apartment = head;
	
	if(head == NULL) return NULL;

	while(NEXT(last_apartment) != head) last_apartment = NEXT(last_apartment);
	return last_apartment;	
}


Apartment* search_apartment(Apartment *head, char *apartment_name){
	while(!str_compare(NAME(head), apartment_name)) head = NEXT(head);
	return head;
}


Flat* find_flat(Flat *flat_lst, int flat_id){ /* Returns pointer of flat if the given flat_id is in given flat_lst */
	for(; flat_lst && ID(flat_lst) != flat_id; flat_lst = NEXT(flat_lst));

	if(flat_lst) /* flat_lst is not NULL */
		return flat_lst;
	else /* flat_lst is NULL */
		return NULL;
}


Apartment* search_flat(Apartment *head, int searched_flat_id, Flat **searched_flat){ /* Searching a specified flat in the given apartment list */
	/*
	This function search the the given searched_flat_id.
	Taking head pointer and the address of searched_flat which is the address of the searched_flat_id.
	Function returns the pointer of the apartment that contains the searched_flat.
	*/
	while(1)
	{
		*searched_flat = find_flat(LIST(head), searched_flat_id);
		if(*searched_flat){ /* given flat_id is found */
			return head;
		}
		else{
			head = NEXT(head);
		}
	}
}


/* THE 3 Functions */
Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth){
	Apartment *new_apartment, *new_head = head;

	/* Allocation and assigning values of new apartment */
	new_apartment = malloc(sizeof(Apartment));
	
	NAME(new_apartment) = apartment_name;
	MAX_BAND(new_apartment) = max_bandwidth;
	LIST(new_apartment) = NULL;
	
	/* Arranging links */
	if(index){ /* Index is not 0, so head is not NULL */
		while(--index) head = NEXT(head); /* Finding the node just before the given index */
		NEXT(new_apartment) = NEXT(head);
		NEXT(head) = new_apartment;
	}
	else if(head){ /* Index is 0, head is not NULL */
		NEXT(new_apartment) = head;
		new_head = new_apartment;
		/* 
		Since, new apartmement needs to be inserted in first index, I need to change the NEXT info of the last element.
		I need to traverse until the end of the street and change its NEXT to new_head 
		To achieve this, I can compare the NEXT info of the apartment with the head.
		*/
		head = find_last_apartment(head); /* Finding the last apartment */
		NEXT(head) = new_head; /* head is at the end of the apartment list */
	}
	else{ /* The apartment list is NULL */
		new_head = new_apartment;
		NEXT(new_head) = new_head;
	}

	return new_head;
}


void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth){
	int used_bandwidth;
	Flat *new_flat, *temp_flat;

	/* Finding the correct apartment and calculating used bandwidth */
	head = search_apartment(head, apartment_name);

	used_bandwidth = total_bandwidth(LIST(head));
	temp_flat = LIST(head);
	
	/* Finding the given index and inerting the new flat */
	new_flat = malloc(sizeof(Flat) * 1);
	
	ID(new_flat) = flat_id;
	IS_EMPTY(new_flat) = 0;

	if((used_bandwidth+initial_bandwidth) > MAX_BAND(head)) INIT_BAND(new_flat) = MAX_BAND(head) - used_bandwidth;
	else INIT_BAND(new_flat) = initial_bandwidth;
	
	/* Inserting the new_flat */
	if(index){ /* Index is not 0, so flat_list is not NULL */
		while(--index) temp_flat = NEXT(temp_flat); /* Traversing until just before the given index */

		/* Arranging the Links */
		NEXT(new_flat) = NEXT(temp_flat);
		PREV(new_flat) = temp_flat;
			
		NEXT(temp_flat) = new_flat;	
		
		if(NEXT(new_flat) != NULL) PREV(NEXT(new_flat)) = new_flat;
		else;
	}
	else{ /* Index is 0 */
		NEXT(new_flat) = temp_flat;
		PREV(new_flat) = NULL;
		
		if(temp_flat != NULL) PREV(temp_flat) = new_flat; /* If initial flat_list is not empty */
		else;
		
		LIST(head) = new_flat;
	}
}


Apartment* remove_apartment(Apartment* head, char* apartment_name){
	Apartment *new_head = head, *remove_apart;

	if(str_compare(NAME(head), apartment_name)){ /* Removing the head apartment */
		remove_apart = head;

		/* Removing apartment from the apartment list */
		if(str_compare(NAME(NEXT(head)), apartment_name)){
			/* if there is one apartment, name of the next apartment will be same with the given apartment name */
			new_head = NULL;
		}
		else{
			new_head = NEXT(head);			
			head = find_last_apartment(head); /* Reaching the last element */
			NEXT(head) = new_head; /* Connecting Last Item to the new head */
		}		
		
		/* Freeing the apartment */
		if(LIST(remove_apart) != NULL){
			flat_free(LIST(remove_apart)); /* Freeing Flat List */
			LIST(remove_apart) = NULL;
		}
		else;

		free(remove_apart); /* Freeing Apartment */
	}
	else{ /* Removing any other apartment */
		while(!str_compare(NAME(NEXT(head)), apartment_name)) head = NEXT(head); /* Searching the previous apartment */
		
		remove_apart = NEXT(head); /* Assigning the apartment that will be removed */
		NEXT(head) = NEXT(remove_apart); /* Connecting Following Item the previous node */
		
		/* Freeing the apartment */
		if(LIST(remove_apart) != NULL){
			flat_free(LIST(remove_apart)); /* Freeing Flat List */
			LIST(remove_apart) = NULL;
		}
		else;
		
		free(remove_apart); /* Freeing Apartment */
	}

	return new_head;
}


void make_flat_empty(Apartment* head, char* apartment_name, int flat_id){
	Flat *flat_lst;
	
	head = search_apartment(head, apartment_name); /* Finding the apartment */
	for(flat_lst = LIST(head); ID(flat_lst) != flat_id; flat_lst = NEXT(flat_lst)); /* Finding flat */

	IS_EMPTY(flat_lst) = 1;
	INIT_BAND(flat_lst) = 0;
}


int find_sum_of_max_bandwidths(Apartment* head){
	if(head == NULL)
		return 0;
	else{
		Apartment *temp = head;
		int sum = 0;
		
		for(; NEXT(temp) != head; temp = NEXT(temp)) sum += MAX_BAND(temp);
		return sum + MAX_BAND(temp); /* Adding the last apartment */
	}
}


Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2){
	Apartment *apartment_1, *apartment_2;
	Flat *flat_list_1, *flat_list_2;

	apartment_1 = search_apartment(head, apartment_name_1);
	apartment_2 = search_apartment(head, apartment_name_2);

	flat_list_1 = LIST(apartment_1);
	flat_list_2 = LIST(apartment_2);

	if(flat_list_1 && flat_list_2){ /* Both LIST is not empty */
		while(NEXT(flat_list_1)) flat_list_1 = NEXT(flat_list_1); /* Traversing end of the flat_list_1 */
		
		/* Linking/Moving the second list */
		NEXT(flat_list_1) = flat_list_2;
		PREV(flat_list_2) = flat_list_1;

		MAX_BAND(apartment_1) += MAX_BAND(apartment_2);

		LIST(apartment_2) = NULL;
		head = remove_apartment(head, apartment_name_2); /* Removing apartment_2 */
	}
	else if(flat_list_2 == NULL){ 
		/* If the flat_list_2 is NULL, nothing will be change in flat_list_1,
		even if the flat_list_1 is NULL. Just need to remove apartment_2 */
		MAX_BAND(apartment_1) += MAX_BAND(apartment_2);
		head = remove_apartment(head, apartment_name_2);
	}
	else{ 
		/* If flat_list_1 is NULL and flat_list_2 is not NULL, then this block will work. */
		LIST(apartment_1) = flat_list_2; /* Assigning flat_list_2 to apartment_1 */
		MAX_BAND(apartment_1) += MAX_BAND(apartment_2);

		LIST(apartment_2) = NULL;
		head = remove_apartment(head, apartment_name_2); /* Removing apartment_2 */
	}

	return head;
}


void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list){
	Apartment *new_aparment=head, *move_apartment;	
	Flat *prev_flat, *shifting_flat, *move_flat;
	/* 
	prev_flat: flat just before flat_id_to_shift
	shifting_flat: flat_id_to_shift that will be shifted
	move_flat: a kind of temp pointer to store the items of the flat_id_list
	*/	
	int i;

	new_aparment = search_apartment(new_aparment, new_apartment_name); /* Finding the new_apartment */
	shifting_flat = LIST(new_aparment);

	while(ID(shifting_flat) != flat_id_to_shift) shifting_flat = NEXT(shifting_flat); /* Finding the pointer of the previous flat */
	prev_flat = PREV(shifting_flat);

	for(i=0; 0 < flat_id_list[i]; i++){
		move_apartment = search_flat(head, flat_id_list[i], &move_flat); /* Finding the pointer that points item of flat_id_list */
		/* Now, 
		move_apartment points to apartment that contains the given flat_id;
		move_flat points to the given flat_id.
		*/

		/* Arranging the data of NEXT and PREV nodes */
		if(NEXT(move_flat)){ /* NEXT is a flat */
			PREV(NEXT(move_flat)) = PREV(move_flat);
		}else; /* NEXT is not a flat */
		
		if(PREV(move_flat)){ /* PREV is a flat */
			NEXT(PREV(move_flat)) = NEXT(move_flat);
		}
		else{ /* PREV is NULL which means move_flat is the first item of flat_list */
			LIST(move_apartment) = NEXT(move_flat);
		}
	
		/* Moving the node to expected position */
		if(prev_flat == NULL){
			LIST(new_aparment) = move_flat;
			PREV(move_flat) = prev_flat;
			NEXT(move_flat) = NULL;
			prev_flat = move_flat;
		}
		else{
			NEXT(prev_flat) = move_flat;
			PREV(move_flat) = prev_flat;
			NEXT(move_flat) = NULL;
			prev_flat = move_flat;
		}

		MAX_BAND(move_apartment) -= INIT_BAND(move_flat);
		MAX_BAND(new_aparment) += INIT_BAND(move_flat);
	}

	PREV(shifting_flat) = prev_flat;
	NEXT(prev_flat) = shifting_flat;

	return;
}
