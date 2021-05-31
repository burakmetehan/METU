#include "functions.h"

/*
You will not submit this file, just use for testing your code.
All your implementations should be in functions.c
*/

/*
To compile your code, use "make main"
Then "./main" to run.
If you want to compile again, you need to delete the previous executable.
You may do this by "make clean" or simply "rm main"
*/

void print_time_diff(float* time_diff, int len){
	int i;
	for(i=0; i<len; i++)
	{
		printf("%.2f ", time_diff[i]);
	}printf("\n");
}


int main(){
	/*
	Function calls here to test your code
	Example:
	float ***sector_times, **lap_times;
	unsigned int fastest_lap, **positions;
	sector_times = create_sector_times(...);
	positions = create_positions(...);
	lap_times = calculate_lap_times(...);
	fastest_lap = find_fastest_lap(lap_times, ...);
	printf("Printing fastest lap to check the answer: %d\n", fastest_lap);
	*/
	unsigned int **positions;
	unsigned int *total_points;
	unsigned int n_drivers, n_laps;
	unsigned int p_drivers, n_races;
	unsigned int i, j, k;
	
	positions = create_positions(&p_drivers, &n_races);
	total_points = calculate_total_points(positions, p_drivers, n_races);

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

	return 0;
}

/* Create Sector Times 

float ***sector_times;
int i, j, k;
unsigned int drivers, laps;

sector_times = create_sector_times(&drivers, &laps);

for(i=0; i<drivers; i++)
{
	for(j=0; j<laps; j++)
	{
		for(k=0; k<3; k++)
		{
			printf("%.2f ", sector_times[i][j][k]);
		}			
		printf("\n");
	}
}
printf("\n");

free(sector_times);
*/

/* Create Positions

unsigned int **positions;
int i,j;
unsigned int p_drivers, n_races;

positions = create_positions(&p_drivers, &n_races);

for(i=0; i<p_drivers; i++)
{
	for(j=0; j<n_races; j++)
	{
		printf("%u ", positions[i][j]);
	}
	printf("\n");
}

free(positions);
*/

/*  Lap Times
float ***sector_times, **lap_times;
unsigned int **positions;
int i,j;
unsigned int n_drivers, n_laps;
unsigned int p_drivers, n_races;

sector_times = create_sector_times(&n_drivers, &n_laps);
positions = create_positions(&p_drivers, &n_races);
lap_times = calculate_lap_times(sector_times, n_drivers, n_laps);

for(i=0; i<n_drivers; i++)
{
	for(j=0; j<n_laps; j++)
	{
		printf("%.2f ", lap_times[i][j]);
	}
	printf("\n");
}

free(sector_times);
free(positions);
free(lap_times);

// in file:
2 3
22.17 34.85 27.46
20.19 32.48 27.51
23.17 35.10 29.02
25.27 33.65 29.50
24.07 36.47 25.16
19.48 33.17 29.56
2 5
2 5 3 11 9
7 24 13 17 17

// out file:
84.479996 80.180000 87.289993 
88.419998 85.699997 82.209999 
*/

/* Fastest Lap

float ***sector_times, **lap_times;
unsigned int n_drivers, n_laps;

sector_times = create_sector_times(&n_drivers, &n_laps);
lap_times = calculate_lap_times(sector_times, n_drivers, n_laps);

printf("%u\n", find_fastest_lap(lap_times, n_drivers, n_laps));

free(sector_times);
free(lap_times);

// in file:
2 3
22.17 34.85 27.46
20.19 32.48 27.51
23.17 35.10 29.02
25.27 33.65 29.50
24.07 36.47 25.16
19.48 33.17 29.56
2 5
2 5 3 11 9
7 24 13 17 17

// out file:
0
*/

/* Find Driver Fastest Lap

float*** sector_times;
	unsigned int n_drivers, n_laps;
	int i;

	sector_times = create_sector_times(&n_drivers, &n_laps);

	for(i=0; i<n_drivers; i++)
	{
		printf("%u ", find_driver_fastest_lap(sector_times[i], n_laps));
	}
	printf("\n");
*/

/* Selection Sort

void print_arr(float* arr_copy, int arr_len){
	int i;
	for(i=0; i<arr_len; i++)
	{
		printf("%.2f ", arr_copy[i]);
	}
	printf("\n");
}

int arr_count = 15;
int arr_len = 15;
float *arr = (float *) malloc(sizeof(float) * arr_len);
float *arr_copy;
int i, j;

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
*/

/* Find Finishing Positions
float ***sector_times;
float **lap_times;
unsigned int *finishing_position;
unsigned int n_drivers, n_laps;
int i;

sector_times = create_sector_times(&n_drivers, &n_laps);
lap_times = calculate_lap_times(sector_times, n_drivers, n_laps);

finishing_position = find_finishing_positions(lap_times, n_drivers, n_laps);
for(i=0; i<n_drivers; i++)
{
	printf("%u ", finishing_position[i]);
}printf("\n");
*/

/* Find Time Differences
float ***sector_times;
	float **lap_times;
	float *time_diff;
	unsigned int n_drivers, n_laps;
	unsigned int i, j;

	sector_times = create_sector_times(&n_drivers, &n_laps);
	lap_times = calculate_lap_times(sector_times, n_drivers, n_laps);

 	for(i=0; i<n_drivers; i++)
	{
		for(j=i; j<n_drivers; j++)
		{
			if(i == j) continue;
			else
			{
				time_diff = find_time_diff(lap_times, n_drivers, n_laps, i, j);
				print_time_diff(time_diff, n_laps);
			}
		}
	}
	printf("\n");
*/

/* Calculate Total Points
unsigned int positions_arr[10][4] = {
	{1, 2, 2, 4},
	{3, 1, 5, 6},
	{1, 2, 2, 4},
	{3, 1, 5, 6},
	{1, 2, 2, 4},
	{3, 1, 5, 6},
	{1, 2, 2, 4},
	{3, 1, 5, 6},
	{1, 2, 2, 4},
	{3, 1, 5, 6}
};
unsigned int p_drivers=10, n_races=4;
int i, j;
unsigned int *total_points;
unsigned int **positions;
positions = (unsigned int **) malloc(sizeof(unsigned int *)*p_drivers);

for(i=0; i<p_drivers; i++)
{
	positions[i] = (unsigned int *) malloc(sizeof(unsigned int)*n_races);
	for (j=0; j < n_races; j++)
	{
		positions[i][j] = positions_arr[i][j];
	}		
}

total_points = calculate_total_points(positions, p_drivers, n_races);

for(i=0; i<p_drivers; i++)
{
	printf("%u ", total_points[i]);
}

// out file:
73 58 73 58 73 58 73 58 73 58 
*/

/* Find Season Ranking
int total_points[10] = {77, 92, 60, 55, 85, 94, 85, 66, 60, 59};
int i;
unsigned int p_drivers = 10;

for(i=0; i<p_drivers; i++)
{
	printf("%u ", find_season_ranking(total_points, p_drivers, i));
}
*/
