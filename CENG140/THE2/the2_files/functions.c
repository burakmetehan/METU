/*
	Burak Metehan Tunçel
*/
#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

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
	return NULL;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
	return 0;
}


unsigned int find_driver_fastest_lap(float lap_times_of_driver[][3], unsigned int n_laps){
	return 0;
}


float* selection_sort(float* arr, unsigned int len, char ord){
	return NULL;
}


unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
	return NULL;
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
