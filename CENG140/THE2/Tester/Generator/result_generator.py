import os

test_case_number = 100
for i in range(test_case_number):
	os.system(f"./function_test < ./cases/case{i} > ./results/result{i}")