#include <stdio.h>
#include <stdlib.h>

float* selection_sort(float* arr, unsigned int len, char ord){
	float *sorted_arr;
	int i, j;

	/* Allocating necessary area to store the copy of arr. Then copying the values of arr to new arr */
	sorted_arr = (float *) malloc(sizeof(float)*len);
	for(i=0; i<len; i++) sorted_arr[i]=arr[i];
	
	if(ord == 'A')
	{
		int min_index;
		for(i=0; i<len; i++)
		{
			for(min_index = i, j = i+1; j<len; j++)
			{
				if(sorted_arr[j] < sorted_arr[min_index])
				{
					min_index = j;
				}
			}
			float temp;
			temp = sorted_arr[i];
			sorted_arr[i] = sorted_arr[min_index];
			sorted_arr[min_index] = temp;
		}
	}
	else
	{
		int max_index;
		for(i=0; i<len; i++)
		{
			for(max_index = i, j = i+1; j<len; j++)
			{
				if(sorted_arr[j] > sorted_arr[max_index])
				{
					max_index = j;
				}
			}
			float temp;
			temp = sorted_arr[i];
			sorted_arr[i] = sorted_arr[max_index];
			sorted_arr[max_index] = temp;
		}
	}

	return sorted_arr;
}

int main(){
	int i, j, k;
	for(i=0; i < 3; i++)
		for(j=0; j < 3; j++)
			for(k=0; k < 3; k++)
				printf("%d,%d,%d ", i, j, k);
			printf("\n");
		printf("\n");

	return 0;
}
