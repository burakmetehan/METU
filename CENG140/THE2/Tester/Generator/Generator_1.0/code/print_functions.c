#include <stdio.h>
#include "functions.h"

#define n_sector 3
#define arr_count 25
#define arr_len 25


void print_sector_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
	int i, j, k;
	for(i=0; i<n_drivers; i++)
	{
		for(j=0; j<n_laps; j++)
		{
			for(k=0; k<3; k++)
			{
				printf("%.2f ", sector_times[i][j][k]);
			}
			printf("\n");
		}
	}
}


void print_positions(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
	int i, j;
	for(i=0; i < p_drivers; i++)
	{
		for(j=0; j < n_races; j++)
		{
			printf("%u ", positions[i][j]);
		}
		printf("\n");
	}
}


void print_lap_times(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
	int i, j;
	for(i=0; i<n_drivers; i++)
	{
		for(j=0; j<n_laps; j++)
		{
			printf("%.2f ", lap_times[i][j]);
		}
		printf("\n");
	}
}


void print_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
	printf("%u \n", find_fastest_lap(lap_times, n_drivers, n_laps));
}


void print_driver_fastest_lap(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
	int i;
	for(i=0; i<n_drivers; i++)
		printf("%u ", find_driver_fastest_lap(sector_times[i], n_laps));
	printf("\n");
}


void print_arr(float* arr_copy){
	int i;
	for(i=0; i<arr_len; i++)
	{
		printf("%.2f ", arr_copy[i]);
	}
	printf("\n");
}

void test_print_selection_sort(void){
	int i, j;
	float *arr = (float *) malloc(sizeof(float) * arr_len);
	float *arr_copy;

	for(i=0; i<arr_count; i++)
	{
		for(j=0; j<arr_len; j++)
		{
			scanf("%f", &arr[j]);
		}

		arr_copy = selection_sort(arr, arr_len, 'A');
		print_arr(arr_copy);

		arr_copy = selection_sort(arr, arr_len, 'D');
		print_arr(arr_copy);
	}
	free(arr);
}


void print_finishing_position(unsigned int* finishing_position, unsigned int n_drivers){
	int i;
	for(i=0; i<n_drivers; i++)
	{
		printf("%u ", finishing_position[i]);
	}printf("\n");
}


void print_time_diff_arr(float* time_diff, int len){
	int i;
	for(i=0; i<len; i++)
	{
		printf("%.2f ", time_diff[i]);
	}
	printf("\n");
}

void print_time_diff(float** lap_times, float* time_diff, unsigned int n_drivers, unsigned int n_laps){
	unsigned int i, j;
	for(i=0; i<n_drivers; i++)
	{
		for(j=i; j<n_drivers; j++)
		{
			if(i == j) continue;
			else
			{
				time_diff = find_time_diff(lap_times, n_drivers, n_laps, i, j);
				print_time_diff_arr(time_diff, n_laps);
			}
		}
	}
}


void print_total_points(unsigned int* total_points, unsigned int p_drivers){
	int i;
	for(i=0; i < p_drivers; i++)
	{
		printf("%u ", total_points[i]);
	}
	printf("\n");
}


void print_season_ranking(unsigned int* total_points, unsigned int p_drivers){
	unsigned int i;
	for(i=0; i < p_drivers; i++)
	{
		printf("%u ", find_season_ranking(total_points, p_drivers, i));
	}
	printf("\n");
}
