import os

test_case_number = 10000
for i in range(test_case_number):
	os.system(f"./result_generator < ./cases/case{i} > ./results/result{i}")