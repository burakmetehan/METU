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
