import os

function_number = 7
case_number = [6, 16, 8, 6, 2, 8, 10]

for i in range(function_number):
	cases = open("./all_cases", "a")
	for j in range(case_number[i]):
		func_case = open(f"./function_{i+1}/case{j+1}", "r")

		copy_list = func_case.readlines()
		for k in range(len(copy_list)):
			cases.write(f"{copy_list[k]}")
		
		func_case.close()
	
	cases.close()
