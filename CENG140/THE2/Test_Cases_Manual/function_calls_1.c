#include <stdio.h>
#include "functions.h"

void print_time_diff(float* time_diff, int len){
	int i;
	for(i=0; i<len; i++)
	{
		printf("%f ", time_diff[i]);
	}printf("\n");
}

int main(){

	unsigned int n_drivers, n_laps;
	unsigned int p_drivers, n_races;
	int i, j, k;
	{
	/* First */
	unsigned int **positions;
	float **total_points;
	
	positions = create_positions(&p_drivers, &n_races);
	total_points = calculate_total_points(positions, p_drivers, n_races);
	
	/* find_season_ranking */
	for(i=0; i < p_drivers; i++)
	{
		printf("%u", find_season_ranking(total_points, p_drivers, i));
	}printf("\n");
	
	/* Freeing positions */
	for(i=0; i < p_drivers; i++)
	{
		free(positions[i]);
	}
	free(positions);
	
	/* Freeing total_points */
	free(total_points);
	}

	{
	/* Second */
	float ***sector_times;
	float **lap_times;
	float *time_diff;
	unsigned int *finishing_position;
	unsigned int driver1, driver2;

	sector_times = create_sector_times(&n_drivers, &n_laps);
	lap_times = calculate_lap_times(sector_times, n_drivers, n_laps);

	/* find_fastest_lap */
	for(i=0; i<n_drivers; i++)
	{
		printf("%u ", find_fastest_lap(lap_times, n_drivers, n_laps));
	}printf("\n");

	/* find_finishing_positions */
	finishing_position = find_finishing_positions(lap_times, n_drivers, n_laps);
	for(i=0; i<n_drivers; i++)
	{
		printf("%u ", finishing_position[i]);
	}printf("\n");

	/* find_time_diff */
	for(i=0; i<n_drivers; i++)
	{
		time_diff = find_time_diff(lap_times, n_drivers, n_laps, 0, 1);
		print_time_diff(time_diff, n_drivers);

		time_diff = find_time_diff(lap_times, n_drivers, n_laps, 2, 3);
		print_time_diff(time_diff, n_drivers);

		time_diff = find_time_diff(lap_times, n_drivers, n_laps, 4, 5);
		print_time_diff(time_diff, n_drivers);

		time_diff = find_time_diff(lap_times, n_drivers, n_laps, 1, 2);
		print_time_diff(time_diff, n_drivers);

		time_diff = find_time_diff(lap_times, n_drivers, n_laps, 3, 4);
		print_time_diff(time_diff, n_drivers);

		time_diff = find_time_diff(lap_times, n_drivers, n_laps, 0, 5);
		print_time_diff(time_diff, n_drivers);

		time_diff = find_time_diff(lap_times, n_drivers, n_laps, 3, 5);
		print_time_diff(time_diff, n_drivers);

		time_diff = find_time_diff(lap_times, n_drivers, n_laps, 0, 5);
		print_time_diff(time_diff, n_drivers);

		time_diff = find_time_diff(lap_times, n_drivers, n_laps, 2, 4);
		print_time_diff(time_diff, n_drivers);
	}printf("\n");

	/* find_driver_fastest_lap */
	for(i=0; i<n_drivers; i++)
	{
		printf("%u ", find_driver_fastest_lap(sector_times[i], n_laps));
	}printf("\n");


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

	{
	/* Third */
	int arr_1[15] = {64, 59, 62, 29, 18, 25, 57, 14, 26, 35, 53, 70, 80, 28, 60};
	}

}