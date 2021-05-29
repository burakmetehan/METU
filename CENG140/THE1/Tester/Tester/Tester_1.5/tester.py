"""
	Tester for 2020-2021 CENG 140 THE1
	Created by 
		Burak Metehan Tunçel (Tester, Test Cases, Case Generating)
		Emre Geçit (Test Cases, Case Generating)
	
	- Check the test cases number. It should be same with the file numbers in cases folder.
	- Check the passed cases number. It should be same with test cases.
	- Dimension refers to dimension of image. If you have different dimensional image change it.
	- Error List is for errors if there is any.

	Manual to use:
	- After necessary checking, go line 41 and change the program name "./the1" if it is necessary.
"""

import os
from pathlib import Path
from platform import system

if system()=="Windows":
	windows=True
	os.chdir(f"{Path(__file__).parent.absolute()}")
else:
	windows=False


test_cases = 750
passed_cases= 750
dimension = 25
error_list = []

the1_file_name = input("THE1 File Name:")
if not windows:
	the1_file_name = "./" + the1_file_name

for i in range(test_cases): # Test case number
	# Taking Expected Results
	with open(f"./results/result{i}.txt", "r") as result:
		expected = result.read().splitlines()
		if len(expected) == dimension+1:
			expected_count = expected[-1]
			expected = expected[:-1]
			count_flag = True
		elif len(expected) == dimension:
			continue
		else:
			print("Error: The result is not in proper format.")
	
	# Running The Code
	os.system(f"{the1_file_name} < ./cases/case{i}.txt > output.txt")

	# Taking Output Given by Code
	with open("output.txt", "r") as output:
		given = output.read().splitlines()
		if len(given) == dimension+1:
			given_count = given[-1]
			given = given[:-1]
		elif len(given) == dimension:
			continue
		else:
			print("Error: The output given by code is not in proper format.")

	# Comparing Expected Result with Given Result
	if len(expected) != len(given):
		print("Error: Length of expected and given result are not same. Check the output file.")
	for line in range(len(expected)):
		if expected[line] != given[line]:
			passed_cases -= 1
			error_list.append(f"Error in case{i} and Line {line}. The output and result are not same.")
			error_flag_matrix = False
			break
		else:
			error_flag_matrix = True
	
	if count_flag and error_flag_matrix:
		if expected_count != given_count:
			passed_cases -= 1
			error_list.append(f"Error in case{i}. Count integers are not same.")
	
	# Showing the percentage of process
	if windows:
		if not (i+1)%10:
			os.system("cls")
			print("The process is running: %","%.2f"%((i+1)/(test_cases/100)))
	else:
		if not (i+1)%10:
			os.system("clear")
			print("The process is running: %","%.2f"%((i+1)/(test_cases/100)))

if not error_list:
	print("Congratulations! There is no error in your outputs.")
	print("Correct result percentage rate: %{}".format(format(passed_cases/test_cases*100, ".2f")))
else:
	print("There is/are error(s).")
	print("Correct result percentage rate: %{}".format(format(passed_cases/test_cases*100, ".2f")))
	print("You can see which case is not correct in error.txt")
	with open("errors.txt", "w") as errors:
		errors.write("\n".join(error_list))
		
if windows:
	os.system("del /f output.txt")
else:
	os.system("rm -f output.txt")
