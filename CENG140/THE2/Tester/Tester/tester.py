"""
	Burak Metehan Tunçel
	08.06.2021
	Tester for CENG 140: Take Home Exam 2 (2020-2021)
	Tester Version: 1.1
		Error list and errors.txt are more detailed.
"""
import os
from time import time


def print_result(cases, pass_case, tot_time, tot_code_time, aver_code_time):
	print(f"""
	Correct result percentage rate: %{format(pass_case/cases*100, ".2f")}

	Tester's Total Execution Time: {tot_time}

	Your Code's Total Execution Time: {tot_code_time}

	Your Code's Average Execution Time: {aver_code_time}
	""")


print("Preparing for Testing.")

# Error Catching
try:
	os.system("gcc -c functions.c -o functions.o")
	os.system("gcc ./object_files/creator.o ./object_files/print.o functions.o -o creator")
except:
	print("Error: gcc or functions.c or object_files is not found. Please")
	exit()

try:
	with open(f"./cases/test_case_number", "r") as case_number:
		number = case_number.read().splitlines()
		test_case_number = int(number[1])
except:
	print("Directory 'cases' is not found.")
	exit()


# output path creating for possible errors
if os.path.exists("./outputs"):
	os.system("rm -rf ./outputs")
	os.system("mkdir outputs")
else:
	os.system("mkdir outputs")


passed_cases = test_case_number
error_list = []
total_time_code_exec = 0

# Tester
total_time_init = time()
for i in range(test_case_number):
	case_error = 0

	code_time_in = time()
	os.system(f"./creator < ./cases/case{i} > ./temp_output")
	code_time_out = time()
	total_time_code_exec += (code_time_out-code_time_in)
	
	result = open(f"./results/result{i}", "r")
	function = open("./temp_output", "r")

	res = result.read().splitlines()
	func = function.read().splitlines()

	""" Checking """
	for j in range(len(res)):
		if res[j] == func[j]:
			continue
		else:
			case_error = 1			
			
			# Finding Differences
			res_line_elements = res[j].split()
			out_line_elements = func[j].split()
			
			for k in range(len(res_line_elements)):
				if res_line_elements[k] == out_line_elements[k]:
					continue
				else:
					error_list.append(f"Case: {i} | Line: {j+1} | Element: {k} | Result: {res_line_elements[k]} | Output: {out_line_elements[k]}\n")
			
	if case_error:
		passed_cases -= 1
		os.system(f"cp ./temp_output ./outputs/output{i}")
		os.system(f"cp ./cases/case{i} ./outputs/case{i}")
		os.system(f"cp ./results/result{i} ./outputs/result{i}")


	if not ((i+1)%25):
		#os.system("clear")
		print("Tester is running: %{:.2f}".format((i+1)/test_case_number*100), end="\r")

	result.close()
	function.close()
total_time_out = time()


average_code_exec = total_time_code_exec/test_case_number
total_time = total_time_out-total_time_init

# Cleaning Generated Files
os.system("rm ./functions.o")
os.system("rm ./creator")
os.system("rm ./temp_output")
print("\n")

# Result Printing
if not error_list:
	os.system("rm -rf ./outputs")
	print("Congratulations! There is no error in your outputs.")
	print_result(test_case_number, passed_cases, total_time, total_time_code_exec, average_code_exec)
else:
	with open("errors.txt", "w") as errors:
		errors.write("Case: Case Number | Line: Line Number | Element: Element Number in Line (Starts from 0) | Result: Expected Output | Output: Code Output\n")
		errors.write(f"{'-'*135}\n") # 135 is length of the previous string
		errors.write("\n".join(error_list))

	print("There is/are error(s).")
	print("You can see which case is not correct in errors.txt")
	print_result(test_case_number, passed_cases, total_time, total_time_code_exec, average_code_exec)
	