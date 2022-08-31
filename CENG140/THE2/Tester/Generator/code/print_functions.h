#ifndef print_functions
#define print_functions
#include <stdlib.h>
#include <stdio.h>

void print_sector_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps);

void print_positions(unsigned int** positions, unsigned int p_drivers, unsigned int n_races);

void print_lap_times(float** lap_times, unsigned int n_drivers, unsigned int n_laps);

void print_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps);

void print_driver_fastest_lap(float*** sector_times, unsigned int n_drivers, unsigned int n_laps);

void print_arr(float* arr_copy);

void test_print_selection_sort(void);

void print_finishing_position(unsigned int* finishing_position, unsigned int n_drivers);

void print_time_diff_arr(float* time_diff, int len);

void print_time_diff(float** lap_times, float* time_diff, unsigned int n_drivers, unsigned int n_laps);

void print_total_points(unsigned int* total_points, unsigned int p_drivers);

void print_season_ranking(unsigned int* total_points, unsigned int p_drivers);
#endif
