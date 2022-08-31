#include <stdio.h>
#include "functions.h"
#include "print_functions.h"

int main(){
	/* Sector Times Variables */
	float ***sector_times;
	float **lap_times;
	float* time_diff;
	unsigned int *finishing_position;
	unsigned int n_drivers, n_laps;

	/* Positions Variables */
	unsigned int **positions;
	unsigned int *total_points;
	unsigned int p_drivers, n_races;

	/* General Variables */
	int i, j;


	/* Testing/Calling Functions*/

	/* Function 1: create_sector_times */
	sector_times = create_sector_times(&n_drivers, &n_laps);
	print_sector_times(sector_times, n_drivers, n_laps);

	/* Function 2: create_positions */
	positions = create_positions(&p_drivers, &n_races);
	print_positions(positions, p_drivers, n_races);

	/* Function 3: calculate_lap_times */
	lap_times = calculate_lap_times(sector_times, n_drivers, n_laps);
	print_lap_times(lap_times, n_drivers, n_laps);

	/* Function 4: find_fastest_lap */
	print_fastest_lap(lap_times, n_drivers, n_laps);

	/* Function 5:  find_driver_fastest_Lap */
	print_driver_fastest_lap(sector_times, n_drivers, n_laps);

	/* Function 6: selection_sort */
	/* Testing Selection Sort with pre-determined arrays */
	test_print_selection_sort();

	/* Function 7: find_finishing_positions */
	finishing_position = find_finishing_positions(lap_times, n_drivers, n_laps);
	print_finishing_position(finishing_position, n_drivers);

	/* Function 8: find_time_diff */
	time_diff = find_time_diff(lap_times, n_drivers, n_laps, 0, 0); /* Temp Value */
	print_time_diff(lap_times, time_diff, n_drivers, n_laps);

	/* Function 9: calculate_total_points */
	total_points = calculate_total_points(positions, p_drivers, n_races);
	print_total_points(total_points, p_drivers);

	/* Funtion 10: find_season_ranking */
	print_season_ranking(total_points, p_drivers);


	/* Freeing Memory */

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

	/* Freeing time_diff */
	free(time_diff);

	/* Freeing finishing_positions */
	free(finishing_position);

	/* Freeing positions */
	for(i=0; i < p_drivers; i++)
	{
		free(positions[i]);
	}
	free(positions);
	
	/* Freeing total_points */
	free(total_points);

	return 0;
}