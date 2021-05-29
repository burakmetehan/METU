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
	float ***sector_times, **laptimes;
	unsigned int fastest_lap, **positions;
	sector_times = create_sector_times(...);
	positions = create_positions(...);
	lap_times = calculate_lap_times(...);
	fastest_lap = find_fastest_lap(lap_times, ...);
	printf("Printing fastest lap to check the answer: %d\n", fastest_lap);
	*/
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

	return 0;
}

/* 
Create Sector Times 

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
