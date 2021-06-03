import os
from time import time

os.system("gcc -c functions.c -o functions.o")
os.system("gcc ./object_files/creator.o ./object_files/print.o functions.o -o creator")

passed_cases_first = 1000
passed_cases_second = 1000
test_case_number = 1000
test_case_counter = 0
error_list = []
total_time_code_exec = 0

os.system("clear")

total_time_init = time()
for i in range(test_case_number):
	code_time_in = time()
	os.system(f"./creator < ./cases/case{i} > ./temp_output")
	code_time_out = time()
	total_time_code_exec += (code_time_out-code_time_in)
	
	result = open(f"./results/result{i}", "r")
	function = open("./temp_output", "r")

	res = result.read().splitlines()
	func = function.read().splitlines()

	""" First Check """
	for i in range(len(res)):
		if res[i] == func[i]:
			continue
		else:
			passed_cases_first -= 1
			error_list.append("Line {} is False".format(i+1))


	""" Second Check: Detail Check """
	for i in range(len(res)):
		res_detail = res[i].split()
		func_detail = func[i].split()
		for j in range(len(res_detail)):
			if res_detail[j] == func_detail[j]:
				continue
			else:
				passed_cases_second -= 1
				error_list.append("Line {}/{} is False".format(i+1, j+1))

	test_case_counter += 1
	if not ((test_case_counter)%25):
		os.system("clear")
		print("Tester is running: %{:.2f}".format(test_case_counter/test_case_number*100))

	result.close()
	function.close()
total_time_out = time()

average_code_exec = total_time_code_exec/test_case_number
total_time = total_time_out-total_time_init

print("Cleaning")
os.system("rm ./functions.o")
os.system("rm ./creator")
os.system("rm ./temp_output")
os.system("clear")

if not error_list:
	print("Congratulations! There is no error in your outputs.")
	print("Correct result percentage rate for first check: %{}".format(format(passed_cases_first/test_case_number*100, ".2f")))
	print("Correct result percentage rate for second check: %{}".format(format(passed_cases_second/test_case_number*100, ".2f")))
	print(f"Tester's Total Execution Time: {total_time}")
	print(f"Your Code's Total Execution Time: {total_time_code_exec}")
	print(f"Your Code's Average Execution Time: {average_code_exec}")
else:
	print("There is/are error(s).")
	print("Correct result percentage rate for first check: %{}".format(format(passed_cases_first/test_case_number*100, ".2f")))
	print("Correct result percentage rate for second check: %{}".format(format(passed_cases_second/test_case_number*100, ".2f")))
	print(f"Tester's Total Execution Time: {total_time}")
	print(f"Your Code's Total Execution Time: {total_time_code_exec}")
	print(f"Your Code's Average Execution Time: {average_code_exec}")
	print("You can see which case is not correct in error.txt")
	with open("errors.txt", "w") as errors:
		errors.write("\n".join(error_list))
