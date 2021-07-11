#ifndef input_taker
#define input_taker
#include <stdio.h>
#include <stdlib.h>
#include "the3.h"


/* Functions */
void print_street(Apartment *head, int apartment_number);

void print_street_2(Apartment *head, int function_number, int case_number);

char* str_input(int len_of_str);

Flat* input_flat_list();

Apartment* input_apartment_list(int *apartment_number);

#endif