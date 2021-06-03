"""
Inputs:
1. Number of Drivers (n_drivers) / Number of Laps (n_laps)
2. Sector Times (n_drivers*n_laps line. Each line has 3 sectors.
3. Number of Drivers (p_drivers) / Numebr of Races (n_races)
4. Positions: p_drivers lines. Each line has n_races.
5. Selection Sort input (The length needs to be adjust properly inside of print_functions)
6. Position-point map (the number of input needs to be p_drivers)

Sector Times are float. Selection Sort inputs are float. 
Others will be unsigned int (positive integers)
"""
import random

def race_to_driver_positions(matrix): # basically transpose of an matrix
	matrix_row = len(matrix)
	matrix_col = len(matrix[0])
	new_matrix = []
	for i in range(matrix_col):
		new_matrix.append([])
		for j in range(matrix_row):
			new_matrix[i].append(matrix[j][i])
	
	return new_matrix


n_sector = 3
test_case_number = 10000
pre_build_position_map = [1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 20, 22, 24, 27, 30, 33, 36, 40, 44, 48, 52, 56, 60]
for i in range(test_case_number):
	n_drivers = random.randint(1, 25)
	n_laps = random.randint(1, 25)
	p_drivers = n_drivers
	n_races = random.randint(1,25)
	with open(f"./cases/case{i}", "w") as case:
		
		""" n_drivers, n_laps and sector_times """
		case.write(f"{n_drivers} {n_laps} \n")
		
		for driver in range(n_drivers):
			for lap in range(n_laps):
				for sector in range(n_sector):
					case.write("{:.2f} ".format(random.uniform(15,45)))
				case.write("\n")

		""" p_drivers, n_races and positions """
		case.write(f"{p_drivers} {n_races} \n")
		
		# Need to create positions of races. Then, It will be rotated.
		race_positions = [] # positions of all races
		for race in range(n_races):
			positions = list(range(1, p_drivers+1))
			t_list = [] # positions in one race
			for driver in range(p_drivers):
				t = random.choice(positions)
				positions.remove(t)
				t_list.append(t)
			race_positions.append(t_list)
		
		# race_positions needs to be rotated because its 0th index represent 0th race result, not driver's result
		# When it is rotated, its 0th index will represent the position of racer 0
		driver_positions = race_to_driver_positions(race_positions)
		for driver in range(p_drivers):
			for race in range(n_races):
				case.write("{} ".format(driver_positions[driver][race]))
			case.write("\n")
		
		""" selection_sort """
		# Number of test cases and the length of array will be 25
		for i in range(25):
			for j in range(25):
				case.write("{:.2f} ".format(random.uniform(1,100)))
			case.write("\n")

		""" position_point_map """
		pos_point_map = pre_build_position_map[0:p_drivers]
		pos_point_map.reverse()
		for i in range(len(pos_point_map)):
			case.write("{} ".format(pos_point_map[i]))
			
"""
1, 2, 6, 3, 5, 4
6, 5, 4, 1, 3, 2
5, 3, 1, 4, 6, 2
5, 2, 4, 6, 1, 3
1, 3, 6, 4, 2, 5

1 6 5 5 1 
2 5 3 2 3 
6 4 1 4 6 
3 1 4 6 4 
5 3 6 1 2 
4 2 2 3 5 
"""