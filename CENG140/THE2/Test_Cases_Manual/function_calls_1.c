#include <stdio.h>
#include "functions.h"

void print_time_diff(float* time_diff, int len){
	int i;
	for(i=0; i<len; i++)
	{
		printf("%.2f ", time_diff[i]);
	}printf("\n");
}


void print_arr(float* arr_copy, int arr_len){
	int i;
	for(i=0; i<arr_len; i++)
	{
		printf("%f ", arr_copy[i]);
	}
	printf("\n");
}


int main(){
	unsigned int n_drivers, n_laps;
	unsigned int p_drivers, n_races;
	int i, j, k;
	{/* First */
	unsigned int **positions;
	unsigned int *total_points;
	
	positions = create_positions(&p_drivers, &n_races);
	total_points = calculate_total_points(positions, p_drivers, n_races);
	
	/* create_positions */
	for(i=0; i < p_drivers; i++)
	{
		for(j=0; j < n_races; j++)
		{
			printf("%u ", positions[i][j]);
		}
		printf("\n");
	}

	/* calculate_total_points */
	for(i=0; i < p_drivers; i++)
	{
		printf("%u ", total_points[i]);
	}
	printf("\n");

	/* find_season_ranking */
	for(i=0; i < p_drivers; i++)
	{
		printf("%u ", find_season_ranking(total_points, p_drivers, i));
	}
	printf("\n");
	
	/* Freeing positions */
	for(i=0; i < p_drivers; i++)
	{
		free(positions[i]);
	}
	free(positions);
	
	/* Freeing total_points */
	free(total_points);
	}


	{/* Second */
	float ***sector_times;
	float **lap_times;
	float *time_diff;
	unsigned int *finishing_position;
	unsigned int driver1, driver2;

	sector_times = create_sector_times(&n_drivers, &n_laps);
	lap_times = calculate_lap_times(sector_times, n_drivers, n_laps);

	/* create_sector_times */
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
		printf("\n");
	}
	
	/* calculate_lap_times */
	for(i=0; i<n_drivers; i++)
	{
		for(j=0; j<n_laps; j++)
		{
			printf("%.2f ", lap_times[i][j]);
		}
		printf("\n");
	}

	/* find_fastest_lap */
	printf("%u\n", find_fastest_lap(lap_times, n_drivers, n_laps));

	/* find_finishing_positions */
	finishing_position = find_finishing_positions(lap_times, n_drivers, n_laps);
	for(i=0; i<n_drivers; i++)
	{
		printf("%u ", finishing_position[i]);
	}printf("\n");

	/* find_time_diff */
	for(i=0; i<n_drivers; i++)
	{
		for(j=i; j<n_drivers; j++)
		{
			if(i == j) continue;
			else
			{
				time_diff = find_time_diff(lap_times, n_drivers, n_laps, i, j);
				print_time_diff(time_diff, n_drivers);
			}
		}
		printf("\n");
	}
	printf("\n");

	/* Freeing sector_times */
	for(i=0; i<n_drivers; i++)
	{
		for(j=0; j<n_laps; j++)
		{
			free(sector_times[i][j]);
		}
		free(sector_times[i]);
	}
	free(sector_times);
	
	/* Freeing lap_times */
	for(i=0; i<n_drivers; i++)
	{
		free(lap_times[i]);
	}
	free(lap_times);

	/* Freeing finishing_positions */
	free(finishing_position);

	/* Freeing time_diff */
	free(time_diff);
	}

	
	{/* Third */
	
	{/* selection_sort */
	int arr_count = 15;
	int arr_len = 15;
	float *arr = (float *) malloc(sizeof(float) * arr_len);
	float *arr_copy;

	for(i=0; i<arr_count; i++)
	{
		for(j=0; j<arr_len; j++)
		{
			scanf("%f", &arr[j]);
		}

		arr_copy = selection_sort(arr, arr_len, 'A');
		print_arr(arr_copy, arr_len);

		arr_copy = selection_sort(arr, arr_len, 'D');
		print_arr(arr_copy, arr_len);
	}
	free(arr);
	}

	{/* find_driver_fastest_lap */
	float (*sector_times_of_driver)[3];
	sector_times_of_driver = (float (*)[3]) malloc(sizeof(float [3]) * n_laps);

	for(i=0; i<n_drivers; i++)
	{
		/* Taking Input for function call */
		for(j=0; j<n_laps; j++)
		{
			for(k=0; k<3; k++)
			{
				scanf("%f", &sector_times_of_driver[j][k]);
			}
		}

		/* Calling function and printing */
		printf("%u ", find_driver_fastest_lap(sector_times_of_driver, n_laps));
	}
	printf("\n");
	}

	}

	return 0;
}