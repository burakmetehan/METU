#include <stdio.h>
#include <stdlib.h>
#include "the3.h"


/*
Needs:
Apartment List:
	-Needs to be circular linked list
		(The end apartment needs to point the head)
	-head

	-To create this list, Need to the following Inputs:
		-Number of apartment
		-Each Apartment:
			-name
			-max_bandwidth
			-apartment *next
			-flat *flat_list

Flat Lists (One for each apartment)
	-Needs to be double linked list
	-head will be assigned to *flat_list

	-To create this list, Need to the following Inputs:
		-Number of flats
		-For Each flat:
			-id
			-initial_bandwidth
			-is_empty
			-flat *next
			-flat *prev
		
*/


/* Input Format 
1. line: num = Number of Apartment
The following num block: 
	(Block can be identified with apartment name. Some lines include string/character. 
	Until the next line that contains string, lines belong to the onme apartment.)
	len of name(without '\0'), name and max_bandwidth
	number of the flats
	data for each flat: id, initial bandwidth, is_empty (number of the flats lines)
*/


/* Macros */
#define NEXT(p) ((p) -> next)
#define PREV(p) ((p) -> prev)

#define NAME(p) ((p) -> name)
#define LIST(p) ((p) -> flat_list)
#define MAX_BAND(p) ((p) -> max_bandwidth)

#define ID(p) ((p) -> id)
#define INIT_BAND(p) ((p) -> initial_bandwidth)
#define IS_EMPTY(p) ((p) -> is_empty)


/* Additional Helper Functions */
void print_street(Apartment *head, int apartment_number){
	Flat *flat;
	int i;

	if(head == NULL){
		printf("Apartment List is Empty.\n");
		return;
	}
	else if(apartment_number == 0){
		printf("Apartment List is not Empty, but the given apartment number is 0.\n");
	}else;
	
	for(i = 0; i < apartment_number; i++)
	{
		printf("Apartment Name: %s\n", NAME(head));
		printf("\tMax Bandwidth: %d\n", MAX_BAND(head));
		printf("\tNext Apartment Name: %s\n", NAME(NEXT(head)));
		
		if(LIST(head) != NULL)
		{
			for(flat = LIST(head); flat; flat = NEXT(flat))
			{
				printf("\tFlat List: \n");
				printf("\t\tFlat ID: %d\n", ID(flat));
				printf("\t\tInitial Bandwidth: %d\n", INIT_BAND(flat));
				printf("\t\tIS Empty: %d\n", IS_EMPTY(flat));

				if(NEXT(flat))
					printf("\t\tNext: %d\n", ID(NEXT(flat)));
				else
					printf("\t\tNext: NULL\n");
					
				if(PREV(flat))
					printf("\t\tPrev: %d\n", ID(PREV(flat)));
				else
					printf("\t\tPrev: NULL\n");
					
			}
		}
		else
		{
			printf("\tFlat List: NULL\n");
		}

		head = NEXT(head);
	}

	printf("**************************\n");
}


void print_street_2(Apartment *head, int function_number, int case_number){
	Apartment *head_ptr;
	Flat *flat;
	FILE *fp;
	char command[64] = "Initial Command";

	fp = fopen("./temp_output", "w");

	if(head == NULL){
		fprintf(fp, "Apartment List is Empty.\n");
		fprintf(fp, "**************************\n");
	
		fclose(fp);
		sprintf(command, "mv ./temp_output ./manual_inputs/function_%d/case_output_%d", function_number, case_number);
		system(command);
		return;
	}
	else;

	head_ptr = head;

	do
	{
		fprintf(fp, "Apartment Name: %s\n", NAME(head));
		fprintf(fp, "\tMax Bandwidth: %d\n", MAX_BAND(head));
		fprintf(fp, "\tNext Apartment Name: %s\n", NAME(NEXT(head)));
		
		if(LIST(head) != NULL)
		{
			for(flat = LIST(head); flat; flat = NEXT(flat))
			{
				fprintf(fp, "\tFlat List: \n");
				fprintf(fp, "\t\tFlat ID: %d\n", ID(flat));
				fprintf(fp, "\t\tInitial Bandwidth: %d\n", INIT_BAND(flat));
				fprintf(fp, "\t\tIS Empty: %d\n", IS_EMPTY(flat));

				if(NEXT(flat))
					fprintf(fp, "\t\tNext: %d\n", ID(NEXT(flat)));
				else
					fprintf(fp, "\t\tNext: NULL\n");
					
				if(PREV(flat))
					fprintf(fp, "\t\tPrev: %d\n", ID(PREV(flat)));
				else
					fprintf(fp, "\t\tPrev: NULL\n");
					
			}
		}
		else
		{
			fprintf(fp, "\tFlat List: NULL\n");
		}		
		
		head = NEXT(head);
	} while (head != head_ptr);

	fprintf(fp, "**************************\n");
	
	fclose(fp);
	sprintf(command, "mv ./temp_output ./manual_inputs/function_%d/case_output_%d", function_number, case_number);
	system(command);
}


/* Input Functions */
char* str_input(int len_of_str){
	char *str;
	int i;
	
	str = malloc(sizeof(char) * (len_of_str+1));
	if(str == NULL){
		printf("MALLOC ERROR in function str_input()");
		return NULL;
	}
	
	for(i = 0; i < len_of_str; i++){
		scanf(" %c", &str[i]);
	}
	str[i] = '\0';

	return str;
}


Flat* input_flat_list(){
	Flat *head=NULL, *tail=NULL, *new_flat=NULL;
	int flat_number;

	scanf("%d", &flat_number);
	
	if(!flat_number) return head;

	while(flat_number--)
	{
		if(head == NULL)
		{
			tail = head = malloc(sizeof(Flat) * 1);
			if(head == NULL){
				printf("MALLOC ERROR in function input_flat_list() in head == NULL part");
				return NULL;
			}

			scanf("%d %d %d", &ID(head), &INIT_BAND(head), &IS_EMPTY(head)); /* Taking ID, Initial Bandwidth, Is Empty */

			PREV(head) = NULL;
			NEXT(head) = NULL;
		}
		else
		{
			new_flat = malloc(sizeof(Flat) * 1);
			if(new_flat == NULL){
				printf("MALLOC ERROR in function input_flat_list() in new_flat == NULL part");
				return NULL;
			}

			scanf("%d %d %d", &ID(new_flat), &INIT_BAND(new_flat), &IS_EMPTY(new_flat)); /* Taking ID, Initial Bandwidth, Is Empty */

			NEXT(new_flat) = NULL; /* Initially NEXT data of new_flat needs to be NULL */
			PREV(new_flat) = tail; /* Assigning PREV data of new_flat */
			tail = NEXT(tail) = new_flat; /* First assign new_flat to NEXT(tail), then assign new_flat to tail */
		}			
	}
	

	return head;
}


Apartment* input_apartment_list(int *apartment_number){
	int len_of_name, i;
	Apartment *head=NULL, *tail=NULL, *new_apart=NULL;

	scanf("%d", apartment_number);
	i = *apartment_number-1;

	if(!*apartment_number) return head;

	/* Taking the head apartment */
	tail = head = malloc(sizeof(Apartment) * 1);
	if(head == NULL){
		printf("MALLOC ERROR in function input_apartment_list() in head part");
		return NULL;
	}
	scanf("%d", &len_of_name);
	NAME(head) = str_input(len_of_name); /* name */
	scanf("%d", &MAX_BAND(head)); /* max_bandwidth */
	NEXT(head) = head;
	LIST(head) = input_flat_list(); /* flat_list initially empty */

	/* If there is other apartments, following while loop will take them */
	while(i--){
		new_apart = malloc(sizeof(Apartment) * 1);
		if(new_apart == NULL){
			printf("MALLOC ERROR in function input_apartment_list() in new_apart part");
			return NULL;
		}
		scanf("%d", &len_of_name);
		NAME(new_apart) = str_input(len_of_name); /* name */
		scanf("%d", &MAX_BAND(new_apart)); /* max_bandwidth */

		tail = NEXT(tail) = new_apart; /* First assign new_apart to NEXT(tail), then assign new_apart to tail */
		NEXT(new_apart) = head; /* new_apart needs to point head */

		LIST(new_apart) = input_flat_list(); /* flat_list initially empty */
	}

	return head;
}

/* 
int main(){
	Apartment *head;
	int apartment_number;

	head = input_apartment_list(&apartment_number);
 	print_street(head, apartment_number);

	return 0;
}
 */