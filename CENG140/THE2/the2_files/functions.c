/*
	Burak Metehan Tunçel
*/
#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

/* THE2 Helper Funtions */


/* THE2 Functions */

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
	float ***sector_times;
	int i, j, k;

	scanf("%u %u", n_drivers, n_laps);

	/* Allocating necessary area to store the sector_times */
	sector_times = (float ***) malloc(sizeof(float **) * (*n_drivers));
	for(i=0; i<*n_drivers; i++)
	{
		sector_times[i] = (float **) malloc(sizeof(float *) * (*n_laps));
		for(j=0; j<*n_laps; j++)
			sector_times[i][j] = (float *) malloc(sizeof(float) * n_sector);
	}

	/* Reading the input */
	for(i=0; i<*n_drivers; i++)
		for(j=0; j<*n_laps; j++)
			for(k=0; k<n_sector; k++)
				scanf("%f", &sector_times[i][j][k]);

	/* Returning */
	return sector_times;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
	unsigned int **positions;
	int i, j;

	scanf("%u %u", p_drivers, n_races);

	/* Allocating necessary area to store the positions */
	positions = (unsigned int **) malloc(sizeof(unsigned int *) * (*p_drivers));
	for(i=0; i<*p_drivers; i++)
	{
		positions[i] = (unsigned int *) malloc(sizeof(unsigned int) * (*n_races));
	}

	/* Reading the input */
	for(i=0; i<*p_drivers; i++)
		for(j=0; j<*n_races; j++)
				scanf("%u", &positions[i][j]);

	/* Returning */
	return positions;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
	float **lap_times;
	int i, j, k;
	float sum;

	/* Allocating necessary area to store the lap_times */
	lap_times = (float **) malloc(sizeof(float *) * (n_drivers));
	for(i=0; i<n_drivers; i++)
	{
		lap_times[i] = (float *) malloc(sizeof(float) * (n_laps));
	}

	/* Calculating the lap times */
	for(i=0; i<n_drivers; i++)
	{
		for(j=0; j<n_laps; j++)
		{
			/* Calculating sum */
			for(sum=0, k=0; k<n_sector; k++)
			{
				sum += sector_times[i][j][k];
			}
			/* Assigning the sum */
			lap_times[i][j] = sum;
		}
	}
				
	/* Returning */
	return lap_times;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
	/* 
	I need to create and initiliaze the values of driver_id and min_time because I will make comparison. 
	While comparing, I will compare the previous value wiith the current value.
	Therefore, it can be better to initiliaze these values with the first driver's id and its first lap time.
	*/
	unsigned int driver_id=0;
	float min_time=lap_times[0][0];
	int i, j;

	/* Comparing the lap times of drivers */
	for(i=0; i<n_drivers; i++)
	{
		for(j=0; j<n_laps; j++)
		{
			if(lap_times[i][j] < min_time)
			{
				min_time = lap_times[i][j];
				driver_id = i;
			}else;
		}
	}

	/* Returning */
	return driver_id;
}


unsigned int find_driver_fastest_lap(float lap_times_of_driver[][3], unsigned int n_laps){
	/* 
	I need to create and initiliaze the values of driver_fastest_lap and min_time because I will make comparison. 
	While comparing, I will compare the previous value wiith the current value.
	Therefore, it can be better to initiliaze these values with the first lap and its first lap time.
	*/
	unsigned int driver_fastest_lap=0;
	int i, j;
	/* Defining and Initializing the min_time */
	float min_time, sum;
	for(min_time=0, i=0; i<3; i++)
	{
		min_time += lap_times_of_driver[0][i];
	}

	/* Calculating the lap time and comparing them */
	for(i=0; i<n_laps; i++)
	{
		for(sum=0, j=0; j<3; j++)
		{
			sum += lap_times_of_driver[i][j];
		}
		
		if(sum < min_time)
		{
			driver_fastest_lap = i;
		}else;
	}

	/* Returning */
	return driver_fastest_lap;
}


float* selection_sort(float* arr, unsigned int len, char ord){
	float *sorted_arr;
	int i, j;

	/* Allocating necessary area to store the copy of arr. Then copying the values of arr to new arr */
	sorted_arr = (float *) malloc(sizeof(float)*len);
	for(i=0; i<len; i++) sorted_arr[i]=arr[i];
	
	/* After copying, I use "selection sort" to sort the copy of the arr (sorted_arr) */
	if(ord == 'A')
	{
		int min_index; /* While iterating, index of minimum value will be stored */
		for(i=0; i<len; i++)
		{
			/* Searching for min index */
			for(min_index = i, j = i+1; j<len; j++)
			{
				if(sorted_arr[j] < sorted_arr[min_index])
				{
					min_index = j;
				}else;
			}
			/* Swapping */
			if(min_index != i)
			{
				float temp; /* While swapping, I will need a temporary variable */
				temp = sorted_arr[i];
				sorted_arr[i] = sorted_arr[min_index];
				sorted_arr[min_index] = temp;
			}else;
		}
	}
	else
	{
		int max_index; /* While iterating, index of maximum value will be stored */
		for(i=0; i<len; i++)
		{
			/* Searching for max index */
			for(max_index = i, j = i+1; j<len; j++)
			{
				if(sorted_arr[j] > sorted_arr[max_index])
				{
					max_index = j;
				}
			}
			/* Swapping */
			if(max_index != i)
			{
				float temp; /* While swapping, I will need a temporary variable */
				temp = sorted_arr[i];
				sorted_arr[i] = sorted_arr[max_index];
				sorted_arr[max_index] = temp;
			}else;
		}
	}

	/* Returning */
	return sorted_arr;
}


unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
	unsigned int *finishing_positions;
	unsigned int *drivers_id;
	float *sum_of_lap_time;
	
	int i, j;
	float sum; /* Used for sum of lap times */

	/* Allocating helper drivers' id array and filling it */
	drivers_id = (unsigned int *) malloc(sizeof(unsigned int) * n_drivers);
	for(i=0; i<n_drivers; i++) drivers_id[i] = i;

	/* 
	Allocating helper lap time sums array 
	This array's values will be the sum of the lap times
	They will fit with the indexes of drivers_id
	*/
	sum_of_lap_time = (float *) malloc(sizeof(float) * n_drivers);
	for(i=0; i<n_drivers; i++)
	{
		for(sum=0, j=0; j<n_laps; j++)
		{
			/* Calculating sum */
			sum += lap_times[i][j];			
		}
		/* Assigning the sum */
		sum_of_lap_time[i] = sum;
	}

	/* 
	I have two additional arrays
		The drivers_id array includes the drivers' id
		The sum_of_lap_time array includes the sum of the lap times
	sum_of_lap_time[index] has the total lap times of the drivers_id[index] ('index'th driver)

	Therefore, I can use modified version of the selection sort that I have done coding above.
	The sorting will be done on sum_of_lap_time and at the same time I will change the drivers_id array with same index.
	In the end, I will have finishing positions.	
	*/


	/* Freeing used memory that will not returned  */
	free(drivers_id);
	free(sum_of_lap_time);

	return finishing_positions;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
	unsigned int driver2){
	return NULL;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
	return NULL;
}


unsigned int find_season_ranking(int* total_points, unsigned int p_drivers, unsigned int id){
	return 0;
}
