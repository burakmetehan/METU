/*
	Burak Metehan Tunçel/2468726
	2020-2021
	METU CENG  
	CENG 140: Take Home Exam 2	
*/
#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

/* THE2 Helper Funtions */
void modified_selection_sort(unsigned int* drivers_id, float* sum_lap_times, float n_drivers){
	int i, j;
	int min_index; /* While iterating, index of minimum value will be stored */
	
	for(i = 0; i < n_drivers; i++)
	{
		/* Searching for min index */
		for(min_index = i, j = i+1; j < n_drivers; j++)
		{
			if(sum_lap_times[j] < sum_lap_times[min_index])
			{
				min_index = j;
			}else;
		}

		/* Swapping */
		/*
		I need to swap both drivers IDs and sum_lap_times by using same index
		*/
		if(min_index != i)
		{
			float temp;
			
			/* Swapping lap times */
			temp = sum_lap_times[i];
			sum_lap_times[i] = sum_lap_times[min_index];
			sum_lap_times[min_index] = temp;

			/* Swapping Drivers' IDs */
			temp = drivers_id[i];
			drivers_id[i] = drivers_id[min_index];
			drivers_id[min_index] = temp;
		}else;
	}
	
	return;
}

/* THE2 Functions */
float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
	float ***sector_times;
	int i, j, k;

	scanf("%u %u", n_drivers, n_laps);

	/* Allocating necessary area to store the sector_times */
	sector_times = (float ***) malloc(sizeof(float **) * (*n_drivers));
	for(i = 0; i < *n_drivers; i++)
	{
		sector_times[i] = (float **) malloc(sizeof(float *) * (*n_laps));
		for(j = 0; j < *n_laps; j++)
		{
			sector_times[i][j] = (float *) malloc(sizeof(float) * n_sector);
		}
	}

	/* Reading the input */
	for(i = 0; i < *n_drivers; i++)
		for(j = 0; j < *n_laps; j++)
			for(k = 0; k < n_sector; k++)
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
	for(i = 0; i < *p_drivers; i++)
	{
		positions[i] = (unsigned int *) malloc(sizeof(unsigned int) * (*n_races));
	}

	/* Reading the input */
	for(i = 0; i < *p_drivers; i++)
		for(j = 0; j < *n_races; j++)
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
	for(i = 0; i < n_drivers; i++)
	{
		lap_times[i] = (float *) malloc(sizeof(float) * (n_laps));
	}

	/* Calculating the lap times */
	for(i = 0; i < n_drivers; i++)
	{
		for(j = 0; j < n_laps; j++)
		{
			/* Calculating sum */
			for(sum = 0, k = 0; k < n_sector; k++)
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
	for(i = 0; i < n_drivers; i++)
	{
		for(j = 0; j < n_laps; j++)
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


unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
	/* 
	I need to create and initiliaze the values of driver_fastest_lap and min_time because I will make comparison. 
	While comparing, I will compare the previous value wiith the current value.
	Therefore, it can be better to initiliaze these values with the first lap and its first lap time.
	*/
	unsigned int driver_fastest_lap=0;
	int i, j;
	/* Defining and Initializing the min_time */
	float min_time, sum;
	for(min_time = 0, i = 0; i < n_sector; i++)
	{
		min_time += sector_times_of_driver[0][i];
	}

	/* Calculating the lap time and comparing them */
	for(i = 0; i < n_laps; i++)
	{
		for(sum = 0, j = 0; j < n_sector; j++)
		{
			sum += sector_times_of_driver[i][j];
		}
		
		if(sum < min_time)
		{
			min_time = sum;
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
	for(i = 0; i < len; i++) sorted_arr[i]=arr[i];
	
	/* After copying, I use "selection sort" to sort the copy of the arr (sorted_arr) */
	if(ord == 'A')
	{
		int min_index; /* While iterating, index of minimum value will be stored */
		for(i = 0; i < len; i++)
		{
			/* Searching for min index */
			for(min_index = i, j = i+1; j < len; j++)
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
		for(i = 0; i < len; i++)
		{
			/* Searching for max index */
			for(max_index = i, j = i+1; j < len; j++)
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
	float *sum_of_lap_time;
	
	int i, j;
	float sum; /* Used for sum of lap times */

	/* Allocating finishing_positions array and filling it */
	finishing_positions = (unsigned int *) malloc(sizeof(unsigned int) * n_drivers);
	for(i = 0; i < n_drivers; i++) finishing_positions[i] = i;
	/* It is filled with numbers [0, n_drivers]. It will be changed according to lap times in modified sort function */

	/* 
	Allocating helper lap time sums array 
	This array's values will be the sum of the lap times
	They will fit with the indexes of finishing_positions
	*/
	sum_of_lap_time = (float *) malloc(sizeof(float) * n_drivers);
	for(i = 0; i < n_drivers; i++)
	{
		for(sum = 0, j = 0; j < n_laps; j++)
		{
			/* Calculating sum */
			sum += lap_times[i][j];
		}
		/* Assigning the sum */
		sum_of_lap_time[i] = sum;
	}

	/* 
	I have two additional arrays
		The finishing_positions array includes the drivers' id
		The sum_of_lap_time array includes the sum of the lap times
	sum_of_lap_time[index] has the total lap times of the finishing_positions[index] ('index'th driver)

	Therefore, I can use modified version of the selection sort that I have done coding above.
	The sorting will be done on sum_of_lap_time and at the same time I will change the finishing_positions array with same index.
	In the end, I will have finishing positions.	
	*/
	modified_selection_sort(finishing_positions, sum_of_lap_time, n_drivers);

	/* Freeing used memory that will not returned  */
	free(sum_of_lap_time);

	/* Returning */
	return finishing_positions;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1, unsigned int driver2){
	float *time_diff;
	int i;

	/* Allocating necessary memory to store the time differences */
	time_diff = (float *) malloc(sizeof(float) * n_laps);

	/* Since the differences are accumulated, it can be better initiliaze first difference by hand instead of if inside of for loop */
	time_diff[0] = lap_times[driver1][0] - lap_times[driver2][0];

	/* Calculating time differences accumulatively */
	for(i = 1; i < n_laps; i++)
	{
		time_diff[i] = time_diff[i-1] + (lap_times[driver1][i] - lap_times[driver2][i]);
	}

	/* Returning */
	return time_diff;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
	unsigned int *total_points;
	unsigned int *position_map;
	int i, j;

	/* Allocating necessary memory to store the position map and taking input */
	position_map = (unsigned int *) malloc(sizeof(unsigned int) * p_drivers);
	for(i = 0; i < p_drivers; i++)
	{
		scanf("%u", &position_map[i]);
	}

	/* Allocating necessary memory to store the total_points */
	total_points = (unsigned int *) malloc(sizeof(unsigned int) * p_drivers);

	/* Calculating and assigning the calculated value */
	for(i = 0; i < p_drivers; i++)
	{
		unsigned int sum;
		for(sum = 0, j = 0; j < n_races; j++)
		{
			sum += position_map[positions[i][j]-1];
		}
		total_points[i] = sum;
	}

	/* Freeing used memory that will not returned  */
	free(position_map);

	/* Returning */
	return total_points;
}


unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
	unsigned int season_rank;
	int i, point_of_id;

	/* 
	Initially, I think season rank of driver is 1. 
	If there is a higher points in total_points array, rank will increase 1.
	If there is same points I need to check the id number.
	*/
	point_of_id = total_points[id];
	for(season_rank = 1, i = 0; i < p_drivers; i++)
	{
		if(total_points[i] > point_of_id) season_rank++;
		else if(total_points[i] == point_of_id && i < id) season_rank++;
		else;		
	}

	/* Returning */
	return season_rank;
}
