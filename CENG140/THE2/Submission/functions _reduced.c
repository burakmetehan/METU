#include <stdlib.h>
#include <stdio.h>
#define n_sector 3
/* THE2 Helper Funtions */
void modified_selection_sort(float* sum_lap_times, unsigned int* drivers_id, unsigned int n_drivers){
	int i, j, min_index;
	for(i = 0; i < n_drivers; i++){
		for(min_index = i, j = i+1; j < n_drivers; j++){
			if(sum_lap_times[j] < sum_lap_times[min_index]) min_index = j;
			else if(sum_lap_times[j] == sum_lap_times[min_index] && drivers_id[j] < drivers_id[min_index]) min_index = j;
		}
		if(min_index != i){
			float temp;
	
			temp = sum_lap_times[i];
			sum_lap_times[i] = sum_lap_times[min_index];
			sum_lap_times[min_index] = temp;
			
			temp = drivers_id[i];
			drivers_id[i] = drivers_id[min_index];
			drivers_id[min_index] = temp;
		}
	}
}

/* THE2 Functions */
float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
	float ***sector_times;
	int i, j, k;
	scanf("%u %u", n_drivers, n_laps);
	sector_times = malloc(sizeof(float **) * (*n_drivers));
	for(i = 0; i < *n_drivers; i++){
		sector_times[i] = malloc(sizeof(float *) * (*n_laps));
		for(j = 0; j < *n_laps; j++)
			sector_times[i][j] = malloc(sizeof(float) * n_sector);
	}
	for(i = 0; i < *n_drivers; i++)
		for(j = 0; j < *n_laps; j++)
			for(k = 0; k < n_sector; k++)
				scanf("%f", &sector_times[i][j][k]);
	return sector_times;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
	unsigned int **positions;
	int i, j;
	scanf("%u %u", p_drivers, n_races);
	positions = malloc(sizeof(unsigned int *) * (*p_drivers));
	for(i = 0; i < *p_drivers; i++) positions[i] = malloc(sizeof(unsigned int) * (*n_races));
	for(i = 0; i < *p_drivers; i++)
		for(j = 0; j < *n_races; j++)
			scanf("%u", &positions[i][j]);
	return positions;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
	float **lap_times, sum;
	int i, j, k;
	lap_times = (float **) malloc(sizeof(float *) * (n_drivers));
	for(i = 0; i < n_drivers; i++)
		lap_times[i] = (float *) malloc(sizeof(float) * (n_laps));
	for(i = 0; i < n_drivers; i++)
		for(j = 0; j < n_laps; j++){
			for(sum = 0, k = 0; k < n_sector; k++)
				sum += sector_times[i][j][k];
			lap_times[i][j] = sum;
		}
	return lap_times;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
	unsigned int driver_id=0;
	float min_time=lap_times[0][0];
	int i, j;
	for(i = 0; i < n_drivers; i++)
		for(j = 0; j < n_laps; j++){
			if(lap_times[i][j] < min_time){
				min_time = lap_times[i][j];
				driver_id = i;
			}else;
		}
	return driver_id;
}


unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
	unsigned int driver_fastest_lap=0;
	int i, j;
	float min_time, sum;
	for(min_time = 0, i = 0; i < n_sector; i++)
		min_time += sector_times_of_driver[0][i];

	for(i = 0; i < n_laps; i++){
		for(sum = 0, j = 0; j < n_sector; j++)
			sum += sector_times_of_driver[i][j];
		if(sum < min_time){
			min_time = sum;
			driver_fastest_lap = i;
		}else;
	}
	return driver_fastest_lap;
}


float* selection_sort(float* arr, unsigned int len, char ord){
	float *sorted_arr;
	int i, j;
	sorted_arr = malloc(sizeof(float)*len);
	for(i = 0; i < len; i++) sorted_arr[i] = arr[i];
	if(ord == 'A'){
		int min_index;
		for(i = 0; i < len; i++){
			for(min_index = i, j = i+1; j < len; j++)
				if(sorted_arr[j] < sorted_arr[min_index])
					min_index = j;
			if(min_index != i){
				float temp;
				temp = sorted_arr[i];
				sorted_arr[i] = sorted_arr[min_index];
				sorted_arr[min_index] = temp;
			}
		}
	}else{
		int max_index;
		for(i = 0; i < len; i++){
			for(max_index = i, j = i+1; j < len; j++)
				if(sorted_arr[j] > sorted_arr[max_index])
					max_index = j;
			if(max_index != i){
				float temp; /* While swapping, I will need a temporary variable */
				temp = sorted_arr[i];
				sorted_arr[i] = sorted_arr[max_index];
				sorted_arr[max_index] = temp;
			}else;
		}
	}
	return sorted_arr;
}


unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
	unsigned int *finishing_positions;
	float *sum_of_lap_time, sum;
	int i, j;
	finishing_positions = (unsigned int *) malloc(sizeof(unsigned int) * n_drivers);
	for(i = 0; i < n_drivers; i++) finishing_positions[i] = i;
	sum_of_lap_time = (float *) malloc(sizeof(float) * n_drivers);
	for(i = 0; i < n_drivers; i++){
		for(sum = 0, j = 0; j < n_laps; j++)
			sum += lap_times[i][j];
		sum_of_lap_time[i] = sum;
	}
	modified_selection_sort(sum_of_lap_time, finishing_positions, n_drivers);
	free(sum_of_lap_time);
	return finishing_positions;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1, unsigned int driver2){
	float *time_diff;
	int i;
	time_diff = (float *) malloc(sizeof(float) * n_laps);
	time_diff[0] = lap_times[driver1][0] - lap_times[driver2][0];
	for(i = 1; i < n_laps; i++)
		time_diff[i] = time_diff[i-1] + (lap_times[driver1][i] - lap_times[driver2][i]);
	return time_diff;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
	unsigned int *total_points, *position_map;
	int i, j;
	position_map = (unsigned int *) malloc(sizeof(unsigned int) * p_drivers);
	for(i = 0; i < p_drivers; i++)
		scanf("%u", &position_map[i]);
	total_points = (unsigned int *) malloc(sizeof(unsigned int) * p_drivers);
	for(i = 0; i < p_drivers; i++){
		unsigned int sum;
		for(sum = 0, j = 0; j < n_races; j++)
			sum += position_map[positions[i][j]-1];
		total_points[i] = sum;
	}
	free(position_map);
	return total_points;
}


unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
	unsigned int season_rank;
	int i, point_of_id;
	point_of_id = total_points[id];
	for(season_rank = 1, i = 0; i < p_drivers; i++){
		if(total_points[i] > point_of_id) season_rank++;
		else if(total_points[i] == point_of_id && i < id) season_rank++;
		else;		
	}
	return season_rank;
}
