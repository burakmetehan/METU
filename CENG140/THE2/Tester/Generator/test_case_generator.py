"""
	Burak Metehan Tunçel
	08.06.2021
	Test Case Generator for CENG 140: Take Home Exam 2 (2020-2021)
	Generator Version: 1.1
		An error in functions.c causes errors in results. functions.c is fixed.
		path.exists control and console printing for information is added.
"""
import random
import os


# Predetermined Values
n_sector = 3
pre_build_position_map = [1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 20, 22, 24, 27, 30, 33, 36, 40, 44, 48, 52, 56, 60]


# Helper Function
def race_to_driver_positions(matrix): # basically transpose of an matrix
	matrix_row = len(matrix)
	matrix_col = len(matrix[0])
	new_matrix = []
	for i in range(matrix_col):
		new_matrix.append([])
		for j in range(matrix_row):
			new_matrix[i].append(matrix[j][i])
	
	return new_matrix


# Checking cases and results directories
# cases
if os.path.exists("./cases"):
	os.system("rm -rf ./cases")
	os.system("mkdir cases")
else:
	os.system("mkdir cases")

# results
if os.path.exists("./results"):
	os.system("rm -rf ./results")
	os.system("mkdir results")
else:
	os.system("mkdir results")


while True:
	try:
		test_case_number = int(input("Case Number: "))
		break;
	except ValueError:
		print("Value Error is Occured. Enter an integer value.")
	except:
		print("An Error is Occured. Enter an integer value.")

# Saving Test Case Number into cases files
with open(f"./cases/test_case_number", "w") as case_number:
	case_number.write("Test Case Number:\n")
	case_number.write(f"{test_case_number}")

print("Creating Test Cases...")
# Generating Cases
for i in range(test_case_number):
	n_drivers = random.randint(1, 25)
	n_laps = random.randint(1, 25)
	p_drivers = n_drivers
	n_races = random.randint(1,25)
	with open(f"./cases/case{i}", "w") as case:
		
		""" n_drivers, n_laps and sector_times """
		case.write(f"{n_drivers} {n_laps} \n")
		
		for _ in range(n_drivers):
			for _ in range(n_laps):
				for sector in range(n_sector):
					case.write("{:.2f} ".format(random.uniform(15,45)))
				case.write("\n")

		""" p_drivers, n_races and positions """
		case.write(f"{p_drivers} {n_races} \n")
		
		# Need to create positions of races. Then, It will be rotated.
		race_positions = [] # positions of all races
		for _ in range(n_races):
			positions = list(range(1, p_drivers+1))
			t_list = [] # temp_list: positions in one race
			for _ in range(p_drivers):
				t = random.choice(positions) # temp variable
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
		for _ in range(25):
			for _ in range(25):
				case.write("{:.2f} ".format(random.uniform(1,100)))
			case.write("\n")

		""" position_point_map """
		pos_point_map = pre_build_position_map[0:p_drivers]
		pos_point_map.reverse()
		for j in range(len(pos_point_map)):
			case.write("{} ".format(pos_point_map[j]))

os.system("clear")
print("Creating Results...")
# Generating Results
for i in range(test_case_number):
	os.system(f"./result_generator < ./cases/case{i} > ./results/result{i}")

os.system("clear")
print("Test cases and results are generated.")