import os

passed_cases=1
error_list = []

for i in range(1): # 35 is the test case number
	expected_matrix=[]
	with open(f"./results/result{i}.txt", "r") as result_file:
		expected = result_file.readlines()
		expected_length = len(expected)
		if expected_length == 25: #Dimension of Matrix
			for j in range(expected_length):
				expected_matrix.append(expected[j].split())
		else:
			expected_count = 0
			for j in range(expected_length):
				expected_matrix.append(expected[j].split())
			expected_count = expected_matrix[-1]
			expected_matrix = expected_matrix[:-1]
	
	os.system(f"./e2468726_the1 < ./cases/case{i}.txt > output.txt")

	given_matrix=[]
	with open("output.txt", "r") as result:
		given = result.readlines()
		given_length = len(given)
		if given_length == 25:
			for j in range(given_length):
				given_matrix.append(given[j].split())
		else:
			given_count = 0
			for j in range(given_length):
				given_matrix.append(given[j].split())
			given_count = given_matrix[-1]
			given_matrix = given_matrix[:-1]
	
	if expected_length != given_length:
		print(f"Error in Length calculation in case{i}")
		break
	
	length = expected_length
	flag = False
	if length == 25:
		for row in range(length):
			if flag:
				break
			for col in range(length):
				if expected_matrix[row][col] != given_matrix[row][col]:
					passed_cases-=1
					error_list.append(f"error in case{i}")
					flag=True
					break
	else:
		for row in range(length-1):
			if flag:
				break
			for col in range(length-1):
				if expected_matrix[row][col] != given_matrix[row][col]:
					passed_cases-=1
					error_list.append(f"error in case{i}")
					flag=True
					break
		if (not flag) and (given_count != expected_count):
			passed_cases-=1
			error_number = i
			error_list.append(f"error in case{i}")
			flag=True
			break

if not error_list:
	print("All done!")
	print("Percentage is {}".format(passed_cases/35*100))
else:
	print("There is/are error(s).")
	print("Percentage is {}".format(passed_cases/35*100))
	print(error_list)
