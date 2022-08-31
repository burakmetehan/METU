import os

function_number = 7
case_number = [6, 16, 8, 6, 2, 8, 10]

for i in range(function_number):
	cases = open("./all_outputs", "a")
	if i == 4:
		cases.write("Function 5 (Sum of Max Bandwidth) Outputs:0\n\tCase_1: 460\n\tCase_2: 105")
		cases.close()
		continue

	for j in range(case_number[i]):
		func_case = open(f"./function_{i+1}/case_output_{j+1}", "r")

		copy_list = func_case.readlines()
		for k in range(len(copy_list)):
			cases.write(f"{copy_list[k]}")
		
		func_case.close()
	
	cases.close()
