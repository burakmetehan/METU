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
	int total_points[10] = {77, 92, 60, 55, 85, 94, 85, 66, 60, 59};
	int i;
	unsigned int p_drivers = 10;

	for(i=0; i<p_drivers; i++)
	{
		printf("%u ", find_season_ranking(total_points, p_drivers, i));
	}
	
	return 0;
}

/* Create Sector Times 

float ***sector_times;
int i,j,k;
unsigned int drivers, laps;

sector_times = create_sector_times(&drivers, &laps);

printf("\n");
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
		printf("%f ", lap_times[i][j]);
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
unsigned int **positions;
unsigned int n_drivers, n_laps;
unsigned int p_drivers, n_races;
unsigned int fastest_lap;

sector_times = create_sector_times(&n_drivers, &n_laps);
positions = create_positions(&p_drivers, &n_races);
lap_times = calculate_lap_times(sector_times, n_drivers, n_laps);
fastest_lap = find_fastest_lap(lap_times, n_drivers, n_laps);

printf("%u\n", fastest_lap);

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
0
*/

/* Find Driver Fastest Lap

unsigned int n_drivers=2, n_laps=3;
unsigned int fastest_lap;
int i;
float sector_time[2][3][3] = {
	{{22.17, 34.85, 27.46}, {20.19, 32.48, 27.51}, {23.17, 35.10, 29.02}},
	{{25.27, 33.65, 29.50}, {24.07, 36.47, 25.16}, {19.48, 33.17, 29.56}}
};

for(i=0; i<n_drivers; i++)
{
	fastest_lap = find_driver_fastest_lap(sector_time[i], n_laps);
	printf("%u\n", fastest_lap);
}
// out file:
1
2
*/

/* Selection Sort

float *sorted;
float arr[] = {3.0, 2.0, 7.0, 9.0, 4.0};
int len=5;
int i;

sorted = selection_sort(arr, 5, 'A');
for(i=0; i<len; i++)
{
	printf("%f ", arr[i]);
}
printf("\n");
for(i=0; i<len; i++)
{
	printf("%f ", sorted[i]);
}
printf("\n");
free(sorted);

sorted = selection_sort(arr, 5, 'D');
for(i=0; i<len; i++)
{
	printf("%f ", arr[i]);
}
printf("\n");
for(i=0; i<len; i++)
{
	printf("%f ", sorted[i]);
}
printf("\n");
free(sorted);

// out file:
3.000000 2.000000 7.000000 9.000000 4.000000 
2.000000 3.000000 4.000000 7.000000 9.000000 
3.000000 2.000000 7.000000 9.000000 4.000000 
9.000000 7.000000 4.000000 3.000000 2.000000 
*/

/* Find Finishing Positions
float lap_times_arr[3][3] = {
	{88.419998, 85.699997, 82.209999}, // Driver_0 = 256.33
	{84.479996, 80.180000, 87.289993}, // Driver_1 = 251.95
	{89.419998, 86.699997, 83.209999}  // Driver_2 = 259.33
};
unsigned int n_drivers=3, n_laps=3;
int i, j;
unsigned int *finishing_positions;
float** lap_times;
lap_times = (float **) malloc(sizeof(float *)*n_drivers);

for(i=0; i<n_drivers; i++)
{
	lap_times[i] = (float *) malloc(sizeof(float)*n_laps);
	for (j=0; j < n_laps; j++)
	{
		lap_times[i][j] = lap_times_arr[i][j];
	}		
}

finishing_positions = find_finishing_positions(lap_times, n_drivers, n_laps);

for(i=0; i<n_drivers; i++)
{
	printf("%u ", finishing_positions[i]);
}

free(lap_times);
free(finishing_positions);

// out file:
1 0 2

*/

/* Find Time Differences
float lap_times_arr[3][3] = {
	{88.419998, 85.699997, 82.209999}, // Driver_0 = 256.33
	{84.479996, 80.180000, 87.289993}, // Driver_1 = 251.95
	{89.419998, 86.699997, 83.209999}  // Driver_2 = 259.33
};
unsigned int n_drivers=3, n_laps=3;
int i, j;
float *time_diff;
float** lap_times;
lap_times = (float **) malloc(sizeof(float *)*n_drivers);

for(i=0; i<n_drivers; i++)
{
	lap_times[i] = (float *) malloc(sizeof(float)*n_laps);
	for (j=0; j < n_laps; j++)
	{
		lap_times[i][j] = lap_times_arr[i][j];
	}		
}

time_diff = find_time_diff(lap_times, n_drivers, n_laps, 1, 2);

for(i=0; i<n_drivers; i++)
{
	printf("%f ", time_diff[i]);
}

free(lap_times);
free(time_diff);

// out file:
-4.940002 -11.459999 -7.380005 
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
